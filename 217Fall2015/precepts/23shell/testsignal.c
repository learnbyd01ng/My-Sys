/*--------------------------------------------------------------------*/
/* testsignal.c                                                       */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

/*--------------------------------------------------------------------*/

/* Print a message to stdout. iSignal is the number of the signal that
   caused this function to execute. */

static void myHandler(int iSignal)
{
   printf("In myHandler with argument %d\n", iSignal);
}

/*--------------------------------------------------------------------*/

/* Demonstrate the signal() function and the sigprocmask() system
   call. Return 0.
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

   /* Install myHandler as the handler for SIGINT signals. */
   pfRet = signal(SIGINT, myHandler);
   if (pfRet == SIG_ERR) {perror(argv[0]); exit(EXIT_FAILURE); }

   printf("Entering an infinite loop\n");
   for (;;)
      ;

   /* Never should reach this point. */
}

/*--------------------------------------------------------------------*/

/* Sample execution:

$ gcc217 testsignal.c -o testsignal

$ testsignal
Entering an infinite loop
^CIn myHandler with argument 2
^CIn myHandler with argument 2
^CIn myHandler with argument 2

*/

/* Note:  Can use kill command or Ctrl-\ to stop process. */
