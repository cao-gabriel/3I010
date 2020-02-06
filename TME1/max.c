#include <stdio.h>
#include <stdlib.h>

/*Cette fonction calculte le maximum d'une liste d'entiers
  passés par la ligne de commande*/
int main(int argc, char *argv[])
{
  int max;
  if (argc == 1)
  {
    printf("Pas d'entiers en paramètre\n");
    return 0;
  }
  for (int i = 1; i < argc; i++)
  {
    if (atoi(argv[i]) > max)
    {
      max = atoi(argv[i]);
    }
  }
  printf("Le maximum de la liste d'entiers est : %d\n", max);
}