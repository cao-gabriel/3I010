#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NB_ARGS 10

int main(int argc, char const *argv[]) {

   char buffer[255];
   char** args = (char**)(malloc(sizeof(char*)*NB_ARGS));
   int cpt = 0;
   char dernierChar ;
   printf("%d\n", cpt);

   while(printf(">") && fgets(buffer, sizeof(buffer), stdin) != NULL)
   {
     //define the end of the string
     buffer[strlen(buffer) - 1] = 0;

     //checking if the user want to quit
     if(strcmp(buffer, "quit") == 0) return 1;

     //saving the last character in case of &
     dernierChar = buffer[strlen(buffer) - 1];

     if(dernierChar == '&') buffer[strlen(buffer) - 1] = 0;

     // get the first word in the buffer splitted by space
     char* token = strtok(buffer, " ");

     // retrives all words in the buffer and putting in an array
     while(token != NULL)
     {
       args[cpt] = token;
       token = strtok(NULL, " ");
       cpt++;
     }

     // the array should contain NULL to signal the end for the exec
     args[cpt] = NULL;

     // create a new process running the command stored in the buffer
     if(fork() == 0)
     {
       execvp(args[0], args);
       return EXIT_FAILURE;
     } else {
       //if the last character wasn't a & then wait until the process created finished
         if(dernierChar != '&')
         {
           wait(NULL);
         }
       }
       cpt = 0;
    }

    for (int i = 0; i < NB_ARGS; i++) {
      free(args[i]);
    }
   free(args);
   return EXIT_SUCCESS;
}
