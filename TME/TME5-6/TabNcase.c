/* Diffusion tampon N case */

  #include <stdio.h>
  #include <unistd.h>
  #include <signal.h>
  #include <libipc.h>

/************************************************************/

/* definition des parametres */

  #define NE          2     /*  Nombre d'emetteurs         */
  #define NR          5     /*  Nombre de recepteurs       */
  #define NMAX        3     /*  Taille du tampon           */

/************************************************************/

/* definition des semaphores */
/* sémaphore des récepteurs */
  int srec[NR];
  #define SREC srec
  #define SMUTEXR NR
/* sémaphores des emetteurs */
  #define SEMET (NR + 1)
  #define SMUTEXE (NR + 2)

/************************************************************/

/* definition de la memoire partagee */
typedef struct {
  /* compteur de nombre de récepteurs pour chaque case du tampon */
  int nb_recepteurs[NMAX];
  /* indice de la case pour les émetteurs */
  int id;
  /* le buffer pour les messages */
  int buffer[NMAX];

} t_segpart;

t_segpart *sp;


/************************************************************/

/* variables globales */
  int emet_pid[NE], recep_pid[NR];

/************************************************************/

/* traitement de Ctrl-C */

  void handle_sigint(int sig)
  { int i;
  	for (i = 0; i < NE; i++) kill(emet_pid[i], SIGKILL);
	for (i = 0; i < NR; i++) kill(recep_pid[i], SIGKILL);
	det_sem();
	det_shm((char *)sp);

  }

/************************************************************/

/* fonction EMETTEUR */
void emet(int i) {

  int indice;
  P(SEMET);
  P(SMUTEXE);
  indice = sp -> id;
  sp -> buffer[indice] = i;
  printf("l'émetteur %d envoie un message sur la case %d du tampon\n",i, indice);
  sp -> id = (indice + 1) % NMAX;
  /* signale aux récepteurs qu'ils peuvent prendre le message*/
  for (int j = 0; j < NR; j++) {
    V(SREC[j]);
  }
  V(SMUTEXE);


}


/************************************************************/

/* fonction RECEPTEUR */
void recoit(int i, int *indice_r) {
  /* Prend un ticket parmi son stock de ticket */
  P(SREC[i]);
  P(SMUTEXR);
  int nb_r = sp -> nb_recepteurs[*indice_r];
  /* signale qu'il a pris le message à l'indice indiquée */
  sp -> nb_recepteurs[*indice_r] = nb_r + 1;
  /* Récupération du message */
  int message = sp -> buffer[*indice_r];

  printf("Le récepteur %d a reçu le message à la case %d :\n%d\n",
  i, *indice_r, message);
  /* Si le récepteur est le dernier à prendre le message*/
  if(nb_r + 1 == NR){
    sp -> nb_recepteurs[*indice_r] = 0;
    printf("Le récepteur %d est le dernier à la case %d\n", i, *indice_r);
    V(SEMET);
  }
  V(SMUTEXR);
  /* change de case de reception*/
  *indice_r = (*indice_r + 1)%NMAX;

}

/************************************************************/

int main() {
    struct sigaction action;
    /* indice de la case pour un récepteur */
    int ir;
    /* pid des processus fils */
    int pid;
    int i;
    setbuf(stdout, NULL);

/* Creation du segment de memoire partagee */
sp = (t_segpart *)init_shm(sizeof(t_segpart));
if(sp == NULL) {
  perror("init_shm");
  exit(1);
}

/* initialisation des champs de la structure */
sp -> id = 0;
for (i = 0; i < NMAX; i++) {
  sp -> nb_recepteurs[i] = 0;
}


/* creation des semaphores */
if(creer_sem(NR + 3) == -1){
  perror("creer_sem");
  exit(1);
}

/* initialisation des semaphores */

/* les récepteurs ne peuvent pas recevoir à l'initialisation */
for ( i= 0; i < NR; i++) {
  init_un_sem(SREC[i], 0);
}
/* sémaphore d'exclusion mutuelle */
init_un_sem(SMUTEXR, 1);

/* les émetteurs peuvent produire NMAX messages car le tampon est vide */
init_un_sem(SEMET, NMAX);

/* sémaphore d'exclusion mutuelle pour les émetteur */
init_un_sem(SMUTEXE, 1);

/* creation des processus emetteurs */
for ( i = 0; i < NE; i++) {
  pid = fork();
  if(pid == 0){
    printf("émetteur %d a été crée\n",i );
    while(1){
      emet(i);


    }
    return EXIT_SUCCESS;
  }
  emet_pid[i] = pid;
}

/* creation des processus recepteurs */
for ( i = 0; i < NR; i++) {
  pid = fork();
  if(pid == 0){
    printf("récepteur %d a été crée\n",i );

    while(1){
      recoit(i, &ir);

    }
    return EXIT_SUCCESS;
  }
  recep_pid[i] = pid;
}

/* redefinition du traitement de Ctrl-C pour arreter le programme */

    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    action.sa_handler = handle_sigint;
    sigaction(SIGINT, &action, 0);

    pause();                     /* attente du Ctrl-C */
    return EXIT_SUCCESS;
}
