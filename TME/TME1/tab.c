#include "tab.h"
#include <stdio.h>
#include <stdlib.h>

void InitTab(int *tab, int size)
{

  for (int i = 0; i < size; i++)
  {
    tab[i] = rand() % 10;
  }
}

void PrintTab(int *tab, int size)
{
  for (int i = 0; i < size; i++)
  {
    printf("%d ;", tab[i]);
  }
}

int SumTab(int *tab, int size)
{
  int sum = 0;
  for (int i = 0; i < size; i++)
  {
    sum += tab[i];
  }
  return sum;
}

int MinSumTab(int *min, int *tab, int size)
{
  int local_min = tab[0];
  int sum = 0;
  for (int i = 0; i < size; i++)
  {
    sum += tab[i];
    if (local_min > tab[i])
    {
      local_min = tab[i];
    }
  }
  *min = local_min;
  return sum;
}
