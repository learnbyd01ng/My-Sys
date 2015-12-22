/*--------------------------------------------------------------------*/
/* testforkexit.c                                                     */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/*--------------------------------------------------------------------*/

/* Demonstrate the common way of using the fork() system call and
   the exit() function. Return 0.
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
      exit(0);
   }

   /* This code is executed by only the parent process. */
   printf("Parent process (%d)\n", (int)getpid());

   return 0;
}

/*--------------------------------------------------------------------*/

/* Sample executions:

$ gcc217 testforkexit.c -o testforkexit

$ testforkexit
Parent process (29595)
Parent process (29595)
Child process (29596)

$ testforkexit
Parent process (29600)
Parent process (29600)
Child process (29601)

*/
