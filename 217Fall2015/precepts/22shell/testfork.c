/*--------------------------------------------------------------------*/
/* testfork.c                                                         */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/*--------------------------------------------------------------------*/

/* Demonstrate the fork() system call and the fflush() function.
   Return 0.
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

   printf("Parent and child processes (%d)\n", (int)getpid());

   return 0;
}

/*--------------------------------------------------------------------*/

/* Sample executions:

$ gcc217 testfork.c -o testfork

$ testfork
Parent process (29285)
Parent and child processes (29285)
Parent and child processes (29286)

$ testfork
Parent process (29287)
Parent and child processes (29287)
Parent and child processes (29288)

*/
