#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#define L 3

int main()
{
  for (unsigned int i = 0 ; i < L ; i++)
    {
      if(fork() != 0)
        {
          if(fork() != 0)
            {
              break;
            }
        }
    }
  sleep(30);
  return EXIT_SUCCESS;
}
