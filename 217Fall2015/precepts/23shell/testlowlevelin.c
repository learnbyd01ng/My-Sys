/*--------------------------------------------------------------------*/
/* testlowlevelin.c                                                   */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*--------------------------------------------------------------------*/

/* Demonstrate the open(), read(), and close() system calls.
   Return 0.
   As usual, argc is the command-line argument count, and argv contains
   the command-line arguments. */

int main(int argc, char *argv[])
{
   int iFd;
   int iRet;
   ssize_t iBytesRead;
   ssize_t iTotalBytesRead;
   char acBuffer[9];
   int i;

   /* Read "somedata\n" from a file named tempfile. */

   iFd = open("tempfile", O_RDONLY);
   if (iFd == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   iTotalBytesRead = 0;
   while (iTotalBytesRead < 9)
   {
      iBytesRead =
         read(iFd, acBuffer + iTotalBytesRead,
              (size_t)(9 - iTotalBytesRead));
      if (iBytesRead == -1) {perror(argv[0]); exit(EXIT_FAILURE);}
      iTotalBytesRead += iBytesRead;
   }

   iRet = close(iFd);
   if (iRet == -1) {perror(argv[0]); exit(EXIT_FAILURE); }

   /* Print the data to verify that the previous worked. */

   for (i = 0; i < 9; i++)
      putchar(acBuffer[i]);

   return 0;
}

/*--------------------------------------------------------------------*/

/* Sample execution:

$ gcc217 testlowlevelin.c -o testlowlevelin

$ testlowlevelin
somedata

*/
