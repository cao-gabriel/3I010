#include "tab.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
void PrintMem()
{
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  printf("Memory : %d\n", usage.ru_maxrss);
}

int main(int argc, char *argv[])
{
  srand(time(NULL));
  /*Initialisation d'un tableau sur la pile*/
  int tab[NMAX];
  /*Initalisation d'un tableau sur le tas*/
  int *tabMalloc = (int *)(malloc(sizeof(int) * NMAX));
  PrintMem();
  InitTab(tab, NMAX);
  InitTab(tabMalloc, NMAX);

  /*Affichage des tableaux*/
  PrintTab(tab, NMAX);
  printf("\n");
  PrintTab(tabMalloc, NMAX);
  printf("\n");

  /*Test de la fonction SumTab*/
  printf("La somme des éléments de tab est : %d\n", SumTab(tab, NMAX));
  printf("La somme des éléments de tabMalloc est : %d\n", SumTab(tabMalloc, NMAX));

  /*Test de la fonction MinSumTab*/
  int min;
  MinSumTab(&min, tab, NMAX);
  printf("Le minimum de tab est : %d : \n", min);
  MinSumTab(&min, tabMalloc, NMAX);
  printf("Le minimum de tabMalloc est : %d : \n", min);
}