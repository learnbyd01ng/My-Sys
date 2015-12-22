/*------------------------------------------------------------------*/
/* testalarm.c                                                      */
/* Author: Bob Dondero                                              */
/*------------------------------------------------------------------*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/*------------------------------------------------------------------*/

/* This function is intended to be a handler for signals of type
   SIGALRM.  Print iSig to stdout, and reset the alarm. */

static void myHandler(int iSig)
{
   printf("In myHandler with argument %d\n", iSig);

   /* Reset the alarm. */
   alarm(2);
}

/*------------------------------------------------------------------*/

/* Demonstrate the alarm() function.  Return 0.
   As usual, argc is the command-line argument count, and argv contains
   the command-line arguments. */

int main(int argc, char *argv[])
{
   void (*pfRet)(int);
   sigset_t sSet;
   int iRet;

   /* Make sure SIGALRM signals are not blocked. */
   iRet = sigemptyset(&sSet);
   if (iRet == -1) {perror(argv[0]); exit(EXIT_FAILURE); }   
   iRet = sigaddset(&sSet, SIGALRM);
   if (iRet == -1) {perror(argv[0]); exit(EXIT_FAILURE); }
   iRet = sigprocmask(SIG_UNBLOCK, &sSet, NULL);
   if (iRet == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   /* Install myHandler as the handler for SIGALRM signals. */
   pfRet = signal(SIGALRM, myHandler);
   if (pfRet == SIG_ERR) {perror(argv[0]); exit(EXIT_FAILURE); }

   /* Set a 2 second alarm.  After 2 seconds of real time, send a
   SIGALRM signal to this process. */
   alarm(2);

   /* Enter an infinite loop. */
   printf("Entering an infinite loop\n");
   for (;;)
      ;

   return 0;
}

/*------------------------------------------------------------------*/

/* Sample execution:

$ gcc217 testalarm.c -o testalarm

$ testalarm
Entering an infinite loop
In myHandler with argument 14
In myHandler with argument 14
In myHandler with argument 14
In myHandler with argument 14
^C

*/
