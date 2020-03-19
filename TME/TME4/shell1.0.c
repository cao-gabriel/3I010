#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {

  char buffer[250];
  char dernierChar;

  while( printf("> ") && fgets(buffer, sizeof(buffer), stdin) != NULL)
  {
    //define the end of the string
    buffer[strlen(buffer) - 1] = 0;

    //checking if the user want to quit
    if(strcmp(buffer, "quit") == 0) return 1;

    //saving the last character in case of &
    dernierChar = buffer[strlen(buffer) - 1];

    //keeping only the first word as a command
    int len = strlen(buffer);
    for (int i = 0; i < len; i++) {
      if((buffer[i] == '&') || (buffer[i] == ' ')){
        buffer[i] = 0;
      }
    }


    // create a new process running the command stored in the buffer
    if(fork() == 0)
    {
      execlp(buffer, buffer, NULL);
      return EXIT_FAILURE;
    } else {
      //if the last character wasn't a & then wait until the process created finished
        if(dernierChar != '&')
        {
          wait(NULL);
        }
      }
  }

   return EXIT_SUCCESS;
}
