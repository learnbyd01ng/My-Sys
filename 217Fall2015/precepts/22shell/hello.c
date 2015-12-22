/*--------------------------------------------------------------------*/
/* hello.c                                                            */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

/*--------------------------------------------------------------------*/

/* Demonstrate the getpid() system call. Return 0. */

int main(void)
{
   pid_t iPid;
   iPid = getpid();
   printf("hello process (%d)\n", (int)iPid);
   return 0;
}

/*--------------------------------------------------------------------*/

/* Sample executions:

$ gcc217 hello.c -o hello

$ hello
hello process (22386)

$ hello
hello process (22387)

*/
