/* Diffusion tampon 1 case */

  #include <stdio.h>
  #include <unistd.h>
  #include <stdlib.h>
  #include <signal.h>
  #include <libipc.h>

/************************************************************/

/* definition des parametres */

  #define NE          2     /*  Nombre d'emetteurs         */
  #define NR          5     /*  Nombre de recepteurs       */

/************************************************************/

/* definition des semaphores */

	   #define EMET  0
     int recep[NR];
     #define RECEP recep
     #define MUTEX 6

/************************************************************/

/* definition de la memoire partagee */
typedef struct {
  int nb_recepteurs;
} t_segpart;

t_segpart *sp;


/************************************************************/

/* variables globales */
    int emet_pid[NE], recep_pid[NR];

/************************************************************/

/* traitement de Ctrl-C */

  void handle_sigint(int sig) {
      int i;
      for (i = 0; i < NE; i++) kill(emet_pid[i], SIGKILL);
      for (i = 0; i < NR; i++) kill(recep_pid[i], SIGKILL);
      det_sem();
      det_shm((char *)sp);
  }

/************************************************************/

/* fonction EMETTEUR */
void emet(int i){
  //Prise du verrou
  P(EMET);
  printf("L'emetteur %d a bien emis un message\n", i);

  //Signal à tous les recepteurs la presence du message
  for(int i = 0; i < NR; i++){
    V(RECEP[i]);
  }
}
	// A completer - contient les instructions executees
        // par un emetteur

/************************************************************/

/* fonction RECEPTEUR */
void recoit(int i){
  P(RECEP[i]);

  P(MUTEX);
  sp -> nb_recepteurs ++;

  printf("Le recepteur %d a bien reçue le message\n", i);
  printf("Le nombre de recepteur ayant consommé le message est de %d \n", sp -> nb_recepteurs);
  if(sp -> nb_recepteurs == NR){
    V(EMET);
    sp -> nb_recepteurs = 0;
  }
  V(MUTEX);
}
	// A completer - contient les instructions executees
        // par un recepteur

/************************************************************/

int main() {
    struct sigaction action;
    /* autres variables (a completer) */
    for (int i = 0; i < NR; i++) {
      recep[i] = i + 1;
    }
    setbuf(stdout, NULL);

/* Creation du segment de memoire partagee */
if ( (sp = (t_segpart *)init_shm(sizeof(t_segpart) ))== NULL) {
  perror("init_shm");
  exit(1);
}
//Aucun recepteur n'a consomme
sp -> nb_recepteurs = 0;

/* creation des semaphores */
if ( creer_sem(NR + 2) == -1) {
        perror("creer_sem");
        exit(1);
}


/* initialisation des semaphores */
//Emetteur non bloque
init_un_sem(EMET,1);
//recepteurs bloques
for (int i = 0; i < NR; i++) {
  init_un_sem(RECEP[i],0);
}
init_un_sem(MUTEX,1);


/* creation des processus emetteurs */
for (int i = 0; i < NE; i++) {
   int p = fork();
   if(p == 0){
     while (1) {
       emet(i);
     }
     exit(EXIT_SUCCESS);
   }
   emet_pid[i] = p;
}
	// A completer - les pid des processus crees doivent
        // etre stockes dans le tableau emet_pid

/* creation des processus recepteurs */
for (int i = 0; i < NR; i++) {
   int p = fork();
   if(p == 0){
     while (1) {
       recoit(i);
     }
     exit(EXIT_SUCCESS);
   }
   recep_pid[i] = p;
}
	// A completer - les pid des processus crees doivent
        // etre stockes dans le tableau recep_pid

/* redefinition du traitement de Ctrl-C pour arreter le programme */

    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    action.sa_handler = handle_sigint;
    sigaction(SIGINT, &action, 0);

    pause();                    /* attente du Ctrl-C  */
    return EXIT_SUCCESS;
}
