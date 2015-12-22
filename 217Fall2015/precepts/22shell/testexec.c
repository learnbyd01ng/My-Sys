/*--------------------------------------------------------------------*/
/* textexec.c                                                         */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*--------------------------------------------------------------------*/

/* Demonstrate the execvp() system call and the perror() function.
   As usual, argc is the command-line argument count, and argv contains
   the command-line arguments. */

int main(int argc, char *argv[])
{
   char *apcArgv[2];

   printf("testexec process (%d)\n", (int)getpid());

   apcArgv[0] = "hello";
   apcArgv[1] = NULL;

   execvp("hello", apcArgv);

   perror(argv[0]);
   /* Alternative:
      fprintf(stderr, "%s: %s\n", argv[0], strerror(errno)); */

   exit(EXIT_FAILURE);
}

/*--------------------------------------------------------------------*/

/* Sample executions:

$ gcc217 hello.c -o hello

$ gcc217 testexec.c -o testexec

$ testexec
testexec process (22440)
hello process (22440)

$ mv hello nothello

$ testexec
testexec process (22454)
testexec: No such file or directory

$ mv nothello hello

$ testexec
testexec process (22463)
hello process (22463)

*/
