#include <stdio.h>
#include <stdlib.h>
#include "affiche_tas.h"
#include <string.h>


int first_fit(int taille, int *pred){
  int tmp = libre;
  while(tmp != -1){
    //Récupération de la taille du premier bloc libre
    int size = tas[tmp];
    // Test si taille suffisante
    if(size> tmp){
      return libre;
    }
    // Si taille non suffisante test zone libre suivante
    tmp = tas[tmp + 1];

  }
  return tmp;
}



char *tas_malloc (unsigned int taille){
  int pred = 0;
  int search = first_fit(taille, &pred);
  //Mise à jour des zones libres
  //Si c'était la dernière zone libre
  if(tas[search+1] == -1){
    //S'il reste de la  place
    if(libre + taille +1 < TAILTAS){
      tas[libre + taille + 1] = tas[search] - taille - 1;
      tas[libre + taille + 2] = -1;
      libre = libre + taille + 1;
    }
  }
  //Si ce n'est pas la dernière zone libre
  else {
    libre = tas[search + 1];
  }

  //Allocation
  tas[search] = taille;

  return &tas[search+1];
}

int tas_free(char *ptr){
  ptr[1] = libre;
  libre = ptr - tas;
  return 0;
}

int main(int argc, char const *argv[]) {
  printf("%s\n", "begin mymalloc");
  tas_init();
  char *p1, *p2, *p3, *p4;
  p1 = (char *) tas_malloc(10);


  p2 = (char *) tas_malloc(9);
  p3 = (char *) tas_malloc(5);

  strcpy(p1, "tp 1");
  strcpy(p2, "tp 2");
  strcpy(p3, "tp 3");
  tas_free(p2);
  printf("%d\n", libre);

  p4 = (char *) tas_malloc(8);
  strcpy( p4, "systeme");

  afficher_tas();
  printf("%s\n", "end mymalloc");
  return 0;
}
