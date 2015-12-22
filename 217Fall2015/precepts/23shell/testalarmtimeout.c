/*-------------------------------------------------------------------*/
/* testalarmtimeout.c                                                */
/* Author: Bob Dondero                                               */
/*-------------------------------------------------------------------*/

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/*-------------------------------------------------------------------*/

/* This function is intended to be a handler for signals of type
   SIGALRM.  Print a timeout message to stdout, and exit. iSignal is
   number of the signal that caused this handler to execute. */

static void myHandler(int iSignal)
{
   printf("\nSorry.  You took too long.\n");
   exit(EXIT_FAILURE);
}

/*-------------------------------------------------------------------*/

/* Demonstrate using an alarm to cause a timeout. Return 0.
   As usual, argc is the command-line argument count, and argv contains
   the command-line arguments. */

int main(int argc, char *argv[])
{
   int i;
   void (*pfRet)(int);
   sigset_t sSigSet;
   int iRet;

   enum {ALARM_DURATION_SECONDS = 5};

   /* Make sure that SIGALRM is not blocked. */
   iRet = sigemptyset(&sSigSet);
   if (iRet == -1) {perror(argv[0]); exit(EXIT_FAILURE); }   
   iRet = sigaddset(&sSigSet, SIGALRM);
   if (iRet == -1) {perror(argv[0]); exit(EXIT_FAILURE); }   
   iRet = sigprocmask(SIG_UNBLOCK, &sSigSet, NULL);
   if (iRet == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   /* Install myHandler as the handler for SIGALRM signals. */
   pfRet = signal(SIGALRM, myHandler);
   if (pfRet == SIG_ERR) {perror(argv[0]); exit(EXIT_FAILURE); }

   printf("Enter a number:  ");
   alarm(ALARM_DURATION_SECONDS);
   scanf("%d", &i);
   alarm(0);

   printf("You entered the number %d.\n", i);
   return 0;
}

/*-------------------------------------------------------------------*/

/* Sample execution:

$ gcc217 testalarmtimeout.c -o testalarmtimeout
$ testalarmtimeout
Enter a number:  123
You entered the number 123.
$ testalarmtimeout
Enter a number:
Sorry.  You took too long.

*/
