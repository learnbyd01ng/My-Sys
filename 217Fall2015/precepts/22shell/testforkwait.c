/*--------------------------------------------------------------------*/
/* testforkwait.c                                                     */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*--------------------------------------------------------------------*/

/* Demonstrate the fork() and wait() system calls. Return 0.
   As usual, argc is the command-line argument count, and argv contains
   the command-line arguments. */

int main(int argc, char *argv[])
{
   pid_t iPid;
   int iRet;
   int i = 0;
   int iStatus;

   printf("Parent process (%d)\n", (int)getpid());

   iRet = fflush(NULL);
   if (iRet == EOF) {perror(argv[0]); exit(EXIT_FAILURE); }

   iPid = fork();
   if (iPid == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   if (iPid == 0)
   {
      /* This code is executed by only the child process. */
      for (i = 0; i < 10; i++)
      {
         printf("Child process (%d):  %d\n", (int)getpid(), i);
         sleep(1);
      }
      exit(0);
   }

   /* This code is executed by only the parent process. */

   /* Wait for the child process to terminate. */
   iPid = wait(&iStatus);
   if (iPid == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   printf("Child process terminated with status %d.\n",
      WEXITSTATUS(iStatus));

   for (i = 0; i < 10; i++)
   {
      printf("Parent process (%d):  %d\n", (int)getpid(), i);
      sleep(1);
   }

   return 0;
}

/*--------------------------------------------------------------------*/

/* Sample execution:

$ gcc217 testforkwait.c -o testforkwait

$ testforkwait
Parent process (25784)
Child process (25785):  0
Child process (25785):  1
Child process (25785):  2
Child process (25785):  3
Child process (25785):  4
Child process (25785):  5
Child process (25785):  6
Child process (25785):  7
Child process (25785):  8
Child process (25785):  9
Child process terminated with status 0.
Parent process (25784):  0
Parent process (25784):  1
Parent process (25784):  2
Parent process (25784):  3
Parent process (25784):  4
Parent process (25784):  5
Parent process (25784):  6
Parent process (25784):  7
Parent process (25784):  8
Parent process (25784):  9

*/
