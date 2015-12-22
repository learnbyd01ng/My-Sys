/*--------------------------------------------------------------------*/
/* testdupforkexec.c                                                  */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

/*--------------------------------------------------------------------*/

/* Demonstrate the fork(), creat(), close(), and dup() system calls.
   Return 0.
   As usual, argc is the command-line argument count, and argv contains
   the command-line arguments. */

int main(int argc, char *argv[])
{
   /* The Unix permissions that a newly created file should have. */
   enum {PERMISSIONS = 0600};

   pid_t iPid;
   int iRet;

   printf("Parent process (%d)\n", (int)getpid());

   iRet = fflush(NULL);
   if (iRet == EOF) {perror(argv[0]); exit(EXIT_FAILURE); }

   iPid = fork();
   if (iPid == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   if (iPid == 0)
   {
      char *apcArgv[2];
      int iFd;
      int iRet;

      iFd = creat("tempfile", PERMISSIONS);
      if (iFd == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

      iRet = close(1);
      if (iRet == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

      iRet = dup(iFd);
      if (iRet == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

      iRet = close(iFd);
      if (iRet == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

      apcArgv[0] = "date";
      apcArgv[1] = NULL;
      execvp("date", apcArgv);
      perror(argv[0]);
      exit(EXIT_FAILURE);
   }

   iPid = wait(NULL);
   if (iPid == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   /* This code is executed by only the parent process. */
   printf("Parent process (%d)\n", (int)getpid());

   return 0;
}

/*--------------------------------------------------------------------*/

/* Sample execution:

$ gcc217 testdupforkexec.c -o testdupforkexec

$ testdupforkexec
Parent process (1140)
Parent process (1140)

$ cat tempfile
Sun Dec 13 20:37:36 EST 2015

*/
