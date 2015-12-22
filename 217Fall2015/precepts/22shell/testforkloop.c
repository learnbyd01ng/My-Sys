/*--------------------------------------------------------------------*/
/* testforkloop.c                                                     */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/*--------------------------------------------------------------------*/

/* Demonstrate context switching among concurrent processes. Return 0.
   As usual, argc is the command-line argument count, and argv contains
   the command-line arguments. */

int main(int argc, char *argv[])
{
   pid_t iPid;
   int iRet;
   int i = 0;

   printf("Parent process (%d)\n", (int)getpid());

   iRet = fflush(NULL);
   if (iRet == EOF) {perror(argv[0]); exit(EXIT_FAILURE); }

   iPid = fork();
   if (iPid == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   if (iPid == 0)
   {
      /* This code is executed by only the child process. */
      for (i = 0; i < 10 ; i++)
      {
         printf("Child process (%d):  %d\n", (int)getpid(), i);
         sleep(1);
      }
      exit(0);
   }

   /* This code is executed by only the parent process. */
   for (i = 0; i < 10; i++)
   {
      printf("Parent process (%d):  %d\n", (int)getpid(), i);
      sleep(1);
   }
   return 0;
}

/*--------------------------------------------------------------------*/

/* Sample execution:

$ gcc217 testforkloop.c -o testforkloop

$ testforkloop
Parent process (25667)
Parent process (25667):  0
Child process (25668):  0
Parent process (25667):  1
Child process (25668):  1
Parent process (25667):  2
Child process (25668):  2
Parent process (25667):  3
Child process (25668):  3
Parent process (25667):  4
Child process (25668):  4
Parent process (25667):  5
Child process (25668):  5
Child process (25668):  6
Parent process (25667):  6
Child process (25668):  7
Parent process (25667):  7
Child process (25668):  8
Parent process (25667):  8
Child process (25668):  9
Parent process (25667):  9

*/
