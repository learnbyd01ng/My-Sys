/*--------------------------------------------------------------------*/
/* testforkret.c                                                      */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/*--------------------------------------------------------------------*/

/* Demonstrate how to use the fork() system call's return value.
   Return 0;
   As usual, argc is the command-line argument count, and argv contains
   the command-line arguments. */

int main(int argc, char *argv[])
{
   pid_t iPid;
   int iRet;

   printf("Parent process (%d)\n", (int)getpid());

   iRet = fflush(NULL);
   if (iRet == EOF) {perror(argv[0]); exit(EXIT_FAILURE); }

   iPid = fork();
   if (iPid == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   if (iPid == 0)
   {
      /* This code is executed by only the child process. */
      printf("Child process (%d)\n", (int)getpid());
   }
   else
   {
      /* This code is executed by only the parent process. */
      printf("Parent process (%d)\n", (int)getpid());
   }

   /* This code is executed by both the parent and child processes. */
   printf("Parent and child process (%d)\n", (int)getpid());

   return 0;
}

/*--------------------------------------------------------------------*/

/* Sample executions:

$ gcc217 testforkret.c -o testforkret

$ testforkret
Parent process (29409)
Parent process (29409)
Parent and child process (29409)
Child process (29410)
Parent and child process (29410)

$ testforkret
Parent process (29413)
Parent process (29413)
Parent and child process (29413)
Child process (29414)
Parent and child process (29414)

*/
