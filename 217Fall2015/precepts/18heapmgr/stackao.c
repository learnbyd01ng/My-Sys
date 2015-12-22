/*--------------------------------------------------------------------*/
/* stackao.c                                                          */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include "stackao.h"
#include <stdlib.h>
#include <assert.h>

/*--------------------------------------------------------------------*/

/* The initial number of elements in the array that underlies the
   Stack object. */
enum {INITIAL_PHYS_LENGTH = 2};

/* The factor by which the array should grow. */
enum {GROWTH_FACTOR = 2};

/* In lieu of a boolean data type. */
enum {FALSE, TRUE};

/*--------------------------------------------------------------------*/

/* The state of the Stack object. */

/* The array in which items are stored. */
static double *pdArray;

/* The index one beyond the top element. */
static int iTop;

/* The number of elements in the array. */
static int iPhysLength;

/* Is the Stack initialized? */
static int iInitialized = FALSE;

/*--------------------------------------------------------------------*/

/* Increase the physical length of the Stack object.  Return 1 (TRUE) if
   successful, or 0 (FALSE) if insufficient memory is available. */

static int Stack_grow(void)
{
   int iNewPhysLength;
   double *pdNewArray;
   assert(iInitialized);
   iNewPhysLength = iPhysLength * GROWTH_FACTOR;
   pdNewArray = (double*)
      realloc(pdArray, sizeof(double) * iNewPhysLength);
   if (pdNewArray == NULL)
      return 0;

   iPhysLength = iNewPhysLength;
   pdArray = pdNewArray;

   return 1;
}

/*--------------------------------------------------------------------*/

/* Initialize the Stack object.  Return 1 (TRUE) if successful, or
   0 (FALSE) if insufficient memory is available. */

int Stack_init(void)
{
   assert(! iInitialized);

   pdArray = (double*)calloc(INITIAL_PHYS_LENGTH, sizeof(double));
   if (pdArray == NULL)
      return 0;

   iTop = 0;
   iPhysLength = INITIAL_PHYS_LENGTH;
   iInitialized = TRUE;
   return 1;
}

/*--------------------------------------------------------------------*/

/* Free the resources consumed by the Stack object, and uninitialize
   it. */

void Stack_free(void)
{
   assert(iInitialized);
   free(pdArray);
   iInitialized = FALSE;
}

/*--------------------------------------------------------------------*/

/* Push dItem onto the Stack object.  Return 1 (TRUE) if successful,
   or 0 (FALSE) if insufficient memory is available. */

int Stack_push(double dItem)
{
   assert(iInitialized);
   if (iTop == iPhysLength)
      if (! Stack_grow())
         return 0;

   pdArray[iTop] = dItem;
   iTop++;
   return 1;
}

/*--------------------------------------------------------------------*/

/* Pop and return the top item of the Stack object. */

double Stack_pop(void)
{
   assert(iInitialized);
   assert(iTop > 0);
   iTop--;
   return pdArray[iTop];
}

/*--------------------------------------------------------------------*/

/* Return 1 (TRUE) if the Stack object is empty, or 0 (FALSE)
   otherwise. */

int Stack_isEmpty(void)
{
   assert(iInitialized);
   return iTop == 0;
}
