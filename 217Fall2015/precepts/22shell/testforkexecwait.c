/*--------------------------------------------------------------------*/
/* textforkexecwait.c                                                 */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*--------------------------------------------------------------------*/

/* Demonstrate the common way of using the fork(), exec(), and wait()
   system calls.  Return 0.
   As usual, argc is the command-line argument count, and argv contains
   the command-line arguments. */

int main(int argc, char *argv[])
{
   pid_t iPid;
   int iRet;

   for (;;)
   {
      iRet = fflush(NULL);
      if (iRet == EOF) {perror(argv[0]); exit(EXIT_FAILURE); }

      iPid = fork();
      if (iPid == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

      if (iPid == 0)
      {
         /* This code is executed by only the child process. */
         char *apcArgv[2];

         apcArgv[0] = "date";
         apcArgv[1] = NULL;

         execvp("date", apcArgv);
         perror(argv[0]);
         exit(EXIT_FAILURE);
      }

      /* This code is executed by only the parent process. */

      /* Wait for the child process to finish. */
      iPid = wait(NULL);
      if (iPid == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

      /* Pause for a while. */
      sleep(3);
   }

   /* Never should reach this point. */
}

/*--------------------------------------------------------------------*/

/* Sample execution:

$ gcc217 testforkexecwait.c -o testforkexecwait

$ testforkexecwait
Tue Dec  8 23:03:33 EST 2015
Tue Dec  8 23:03:36 EST 2015
Tue Dec  8 23:03:39 EST 2015
Tue Dec  8 23:03:42 EST 2015
Tue Dec  8 23:03:45 EST 2015
Tue Dec  8 23:03:48 EST 2015
Tue Dec  8 23:03:51 EST 2015
^C

*/
