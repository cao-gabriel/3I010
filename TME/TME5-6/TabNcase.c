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
  #define SATTENTE (NMAX + 4)
  #define SCONS (NMAX + 3)
  #define SPROD (NMAX + 2)
  #define MUTEXP (NMAX + 1)
  #define MUTEXC (NMAX)
  int sc[NMAX];
  #define SC sc

/************************************************************/

/* definition de la memoire partagee */
typedef struct {
  int nb_recepteurs;
  int id;
  int ir;

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

	void deposer(int number){
    P(SPROD);
    int i;
    P(MUTEXP);
    i = sp->id;
    sp->id++;
    sp->id %= NMAX;
    P(SC[i]);
    V(MUTEXP);
    printf("L'émetteur %d a déposé le message à la case %d\n", number, i);
    V(SC[i]);
    for(int j = 0; j < NR; j++){

      V(SCONS);
    }


  }

/************************************************************/

/* fonction RECEPTEUR */

void retirer(int number){
  P(SCONS);
  int i;
  P(MUTEXC);
  sp->nb_recepteurs++;

  i = sp->ir;/*
  sp->ir++;
  sp->ir %= NMAX;
  */
  P(SC[i]);

  printf("Le recepteur %d a reçu le message à la case %d\n", number, i);
  V(SC[i]);

  if(sp->nb_recepteurs == NR){
    sp->nb_recepteurs = 0;
    sp->ir++;
    sp->ir %= NMAX;
    V(SPROD);
  }
  V(MUTEXC);
}
/************************************************************/

int main() {
    struct sigaction action;
    /* autres variables (a completer) */
    for (int i = 0; i < NMAX; i++) {
      SC[i] = i;
    }
    setbuf(stdout, NULL);

/* Creation du segment de memoire partagee */

if ( (sp = (t_segpart *)init_shm(sizeof(t_segpart) ))== NULL) {
  perror("init_shm");
  exit(1);
}
sp->nb_recepteurs = 0;
sp->id = 0;
sp->ir = 0;

/* creation des semaphores */

if ( creer_sem(NR + 5) == -1) {
        perror("creer_sem");
        exit(1);
}

/* initialisation des semaphores */

for (int i = 0; i < NMAX; i++) {
  init_un_sem(SC[i], 1);
}

init_un_sem(MUTEXC, 1);
init_un_sem(MUTEXP, 1);
init_un_sem(SPROD, NMAX);
init_un_sem(SCONS, 0);
init_un_sem(SATTENTE, 0);




/* creation des processus emetteurs */
for (int i = 0; i < NE; i++) {
   int p = fork();
   if(p == 0){
     while (1) {
       /*Attend la consommation d'un ticket producteur par un consommateur*/
       /*Le nombre de ticket producteur est initialisé à NMAX car l'entrepôt
         peut contenir NMAX message*/

       /*Dépose un message à une case id puis incrémente id pour signaler
         aux autres producteurs de mettre le message à la case suivante*/
       deposer(i);
       /*Quand un producteur finit de déposer un message, il crée NR tickets
         pour que chaque récepteurs consomme le message*/

       /*Pour voir le déroulement*/
      // sleep(3);
     }
     exit(EXIT_SUCCESS);
   }
   emet_pid[i] = p;
}

/* creation des processus recepteurs */

for (int i = 0; i < NR; i++) {
   int p = fork();
   if(p == 0){
     while (1) {
       /*Attend la création d'un ticket consommateur*/
       /*Le nombre de ticket consommateur est initialisé à 0 car l'entrepôt
         est vide au départ*/
       /*Consomme le message à la case ir, incrémente nb_recepteurs puis
         se bloque si le recepteur courant n'est pas le dernier ayant consomme
         sinon (si c'est le dernier) rénitialise nb_recepteurs, */
       retirer(i);


      // sleep(3);
     }
     exit(EXIT_SUCCESS);
   }
   recep_pid[i] = p;
}
/* redefinition du traitement de Ctrl-C pour arreter le programme */

    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    action.sa_handler = handle_sigint;
    sigaction(SIGINT, &action, 0);

    pause();                     /* attente du Ctrl-C */
    return EXIT_SUCCESS;
}
