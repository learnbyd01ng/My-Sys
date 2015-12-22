/*--------------------------------------------------------------------*/
/* sumarray.c                                                         */
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

   for (lIndex = 0; lIndex < lCount; lIndex++)
      scanf("%ld", &alNumbers[lIndex]);   /* Should validate. */

   lSum = 0;
   for (lIndex = 0; lIndex < lCount; lIndex++)
      lSum += alNumbers[lIndex];

   printf("The sum is %ld.\n", lSum);

   return 0;
}
