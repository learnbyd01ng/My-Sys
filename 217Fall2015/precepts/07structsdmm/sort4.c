/*--------------------------------------------------------------------*/
/* sort4.c                                                            */
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

/* Sort pdNumbers[0..iCount-1] in ascending order. */

static void insertionSort(double *pdNumbers, int iCount)
{
   int i1;
   int i2;
   double dTemp;

   assert(pdNumbers != NULL);
   assert(iCount >= 0);

   for (i1 = 1; i1 < iCount; i1++)
      for (i2 = i1; i2 > 0; i2--)
         if (pdNumbers[i2] < pdNumbers[i2-1])
         {
            dTemp = pdNumbers[i2];
            pdNumbers[i2] = pdNumbers[i2-1];
            pdNumbers[i2-1] = dTemp;
         }
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
   insertionSort(pdNumbers, iCount);

   /* Write the numbers from the array. */
   for (i = 0; i < iCount; i++)
      printf("%g\n", pdNumbers[i]);

   /* Free the array. */
   free(pdNumbers);

   return 0;
}
