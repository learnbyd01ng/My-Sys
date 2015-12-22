/*--------------------------------------------------------------------*/
/* sumarrayflat.c                                                     */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>

/*--------------------------------------------------------------------*/

enum {ARRAY_LENGTH = 100};

static long alNumbers[ARRAY_LENGTH];  /* Bad style. */
static long lIndex;                   /* Bad style. */
static long lCount;                   /* Bad style. */
static long lSum;                     /* Bad style. */

/*--------------------------------------------------------------------*/

/* Read up to ARRAY_LENGTH integers from stdin, and write to stdout the
   sum of those integers.  Return 0. */

int main(void)
{
   printf("How many integers?  ");
   scanf("%ld", &lCount);   /* Should validate. */

   lIndex = 0;
loop1:
   if (lIndex >= lCount) goto loopend1;
   scanf("%ld", &alNumbers[lIndex]);   /* Should validate. */
   lIndex++;
   goto loop1;
loopend1:

   lSum = 0;

   lIndex = 0;
loop2:
   if (lIndex >= lCount) goto loopend2;
   lSum += alNumbers[lIndex];
   lIndex++;
   goto loop2;
loopend2:

   printf("The sum is %ld.\n", lSum);

   return 0;
}
