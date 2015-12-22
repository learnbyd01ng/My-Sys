/*--------------------------------------------------------------------*/
/* sort5.c                                                            */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*--------------------------------------------------------------------*/

/* The initial number of elements in the array. */
enum {INITIAL_ARRAY_LENGTH = 2};

/* The factor by which the array should grow. */
enum {ARRAY_GROWTH_FACTOR = 2};

/*--------------------------------------------------------------------*/

/* Grow the memory chunk pointed to by pdChunk so it can store
   iArrayLength elements of type double.  Return the address of the new
   memory chunk.  */

static double *grow(double *pdChunk, int iArrayLength)
{
   size_t uNewSize;
   double *pdNewChunk;

   assert(pdChunk != NULL);

   uNewSize = (size_t)iArrayLength * sizeof(double);
   pdNewChunk = (double*)realloc(pdChunk, uNewSize);
   if (pdNewChunk == NULL)
   {
      fprintf(stderr, "Cannot allocate memory\n");
      exit(EXIT_FAILURE);
   }
      
   return pdNewChunk;
}

/*--------------------------------------------------------------------*/

/* Return -1, 0, or 1 depending upon whether double *pvItem1 is less
   than, equal to, or greater than double *pvItem2, respectively. */

static int compareDouble(const void *pvItem1, const void *pvItem2)
{
   assert(pvItem1 != NULL);
   assert(pvItem2 != NULL);

   if (*(double*)pvItem1 < *(double*)pvItem2) return -1;
   if (*(double*)pvItem1 > *(double*)pvItem2) return 1;
   return 0;
}

/*--------------------------------------------------------------------*/

/* Read numbers from stdin, and write them in ascending order to
   stdout.  Return 0 if successful, or EXIT_FAILURE if stdin contains
   a non-number. */

int main(void)
{
   double *pdNumbers;
   int iCount;
   int iArrayLength;
   double dNumber;
   int i;
   int iScanfRet;

   /* Create a small array. */
   iArrayLength = INITIAL_ARRAY_LENGTH;
   pdNumbers = (double*)calloc((size_t)iArrayLength, sizeof(double));
   if (pdNumbers == NULL)
   {
      fprintf(stderr, "Cannot allocate memory\n");
      exit(EXIT_FAILURE);
   }

   /* Read the numbers into the array, expanding the size of the
      array as necessary. */
   for (iCount = 0; ; iCount++)
   {
      iScanfRet = scanf("%lf", &dNumber);
      if (iScanfRet == 0)
      {
         fprintf(stderr, "Non-number in stdin\n");
         exit(EXIT_FAILURE);
      } 
      if (iScanfRet == EOF)
         break;
      if (iCount == iArrayLength)
      {
         iArrayLength *= ARRAY_GROWTH_FACTOR;
         pdNumbers = grow(pdNumbers, iArrayLength);

      }
      pdNumbers[iCount] = dNumber;
   }

   /* Sort the array. */
   qsort(pdNumbers, (size_t)iCount, sizeof(double), compareDouble);

   /* Write the numbers from the array. */
   for (i = 0; i < iCount; i++)
      printf("%g\n", pdNumbers[i]);

   /* Free the array. */
   free(pdNumbers);

   return 0;
}
