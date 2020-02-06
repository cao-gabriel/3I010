#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>
/** FIRST VERSION
void lance_commande(char *commande)
{
  struct timeval ty;
  gettimeofday(&ty, NULL);
  time_t time_1 = ty.tv_sec;
  suseconds_t times_1 = ty.tv_usec;
  if (system(commande))
  {
    fprintf(stderr, "La commande n'a pas pu être executée correctement");
  }
  gettimeofday(&ty, NULL);
  time_t time_2 = ty.tv_sec;
  suseconds_t times_2 = ty.tv_usec;
  printf("La commande a mis %ld secondes et %ld microseconds pour s'executer\n", time_2 - time_2, times_2 - times_1);
}
*/

void lance_commande(char *command)
{
  system(command);
  struct tms buf;
  times(&buf);

  printf("Statistiques de %s\n", command);
  printf("Temps total : %Lf\n", (long double)(buf.tms_utime + buf.tms_stime + buf.tms_cstime + buf.tms_cutime) / sysconf(_SC_CLK_TCK));
  printf("Temps utilisateur : %Lf\n", (long double)(buf.tms_utime) / sysconf(_SC_CLK_TCK));
  printf("Temps système : %Lf\n", (long double)(buf.tms_stime) / sysconf(_SC_CLK_TCK));
  printf("Temps utilisateur fils : %Lf\n", (long double)(buf.tms_cutime) / sysconf(_SC_CLK_TCK));
  printf("Temps système fils : %Lf\n", (long double)(buf.tms_cstime) / sysconf(_SC_CLK_TCK));
}

int main(int argc, char *argv[])
{
  for (int i = 1; i < argc; i++)
  {
    lance_commande(argv[i]);
  }

  return 0;
}