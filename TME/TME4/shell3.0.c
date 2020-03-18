#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include<fcntl.h>
#define NB_ARGS 10

int main(int argc, char const *argv[]) {

   char buffer[255];
   char** args = (char**)(malloc(sizeof(char*)*NB_ARGS));
   int cpt = 0;
   char dernierChar ;
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



     //start the time
     struct timeval temps_avant, temps_apres;
     gettimeofday (&temps_avant, NULL);

     // create a new process running the command stored in the buffer
     if(fork() == 0)
     {
       if(args[0] == NULL) return EXIT_SUCCESS;

       //if the user use the command times, don't print the result
       if(strcmp(args[0], "times") == 0){
         int file_desc = open("/dev/null",O_WRONLY | O_APPEND);
         dup2(file_desc, 1);
         execvp(args[1], args + 1);
       }
       //Otherwise just do the usual
       else {
         execvp(args[0], args);
       }
       return EXIT_FAILURE;
     } else {
       //if the last character wasn't a & then wait until the process created finished
         if(dernierChar != '&')
         {
           wait(NULL);

           if(args[0] != NULL && strcmp(args[0], "times") == 0)
           {
             //Stopping the chrono and evaluate time
             gettimeofday (&temps_apres, NULL);
             printf("temps en us: %ld us\n", ((temps_apres.tv_sec - temps_avant.tv_sec) * 1000000 + temps_apres.tv_usec) - temps_avant.tv_usec);
           }
         }
       }
       //restart the arguments of the command each time
       cpt = 0;
    }

    //return the allocated memory
   for (int i = 0; i < NB_ARGS; i++) {
     free(args[i]);
   }
   free(args);
   return EXIT_SUCCESS;
}
