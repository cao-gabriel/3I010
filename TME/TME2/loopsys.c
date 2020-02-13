#include <sys/types.h>
#include <unistd.h>

#define NB_LOOP 5E7
int main()
{
  for (long i = 0; i < NB_LOOP; i++)
  {
    getpid();
  }
  return 0;
}
