/*--------------------------------------------------------------------*/
/* testlowlevelout.c                                                  */
/* Author: Bob Dondero                                                */
/* The creat, write, and close system calls.                          */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*--------------------------------------------------------------------*/

/* Demonstrate the creat(), write(), and close() system calls.
   Return 0.
   As usual, argc is the command-line argument count, and argv contains
   the command-line arguments. */

int main(int argc, char *argv[])
{
   int iFd;
   int iRet;
   ssize_t iBytesWritten;
   ssize_t iTotalBytesWritten;
   char acBuffer[] = "somedata\n";

   /* The permissions of the newly-created file. */
   enum {PERMISSIONS = 0600};

   /* Write "somedata\n" to a file named tempfile. */

   iFd = creat("tempfile", PERMISSIONS);
   if (iFd == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   iTotalBytesWritten = 0;
   while (iTotalBytesWritten < 9)
   {
      iBytesWritten =
         write(iFd, acBuffer + iTotalBytesWritten,
               (size_t)(9 - iTotalBytesWritten));
      if (iBytesWritten == -1)
         {perror(argv[0]); exit(EXIT_FAILURE); }
      iTotalBytesWritten += iBytesWritten;
   }

   iRet = close(iFd);
   if (iRet == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   return 0;
}

/*--------------------------------------------------------------------*/

/* Sample execution:

$ gcc217 testlowlevelout.c -o testlowlevelout

$ testlowlevelout

$ cat tempfile
somedata

*/
