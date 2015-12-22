/*--------------------------------------------------------------------*/
/* testsignalignore.c                                                 */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

/*--------------------------------------------------------------------*/

/* Demonstrate ignoring signals.
   As usual, argc is the command-line argument count, and argv contains
   the command-line arguments. */

int main(int argc, char *argv[])
{
   void (*pfRet)(int);
   sigset_t sSet;
   int iRet;

   /* Make sure SIGINT signals are not blocked. */
   iRet = sigemptyset(&sSet);
   if (iRet == -1) {perror(argv[0]); exit(EXIT_FAILURE); }
   iRet = sigaddset(&sSet, SIGINT);
   if (iRet == -1) {perror(argv[0]); exit(EXIT_FAILURE); }   
   iRet = sigprocmask(SIG_UNBLOCK, &sSet, NULL);
   if (iRet == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   /* Ignore SIGINT signals. */
   pfRet = signal(SIGINT, SIG_IGN);
   if (pfRet == SIG_ERR) {perror(argv[0]); exit(EXIT_FAILURE); }

   /* Enter an infinite loop. */
   printf("Entering an infinite loop\n");
   for (;;)
      ;

   /* Never should reach this point. */
}

/*--------------------------------------------------------------------*/

/* Sample execution:

$ gcc217 testsignalignore.c -o testsignalignore

$ testsignalignore
Entering an infinite loop
^C^C^C

*/

/* Note:  Can use kill command or Ctrl-\ to stop process. */
