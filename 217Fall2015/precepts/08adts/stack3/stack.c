/*--------------------------------------------------------------------*/
/* stack.c (Version 3)                                                */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include "stack.h"
#include <stdlib.h>
#include <assert.h>

/*--------------------------------------------------------------------*/

/* The initial number of elements in the array that underlies a
   Stack object. */
enum {INITIAL_PHYS_LENGTH = 2};

/* The factor by which the array should grow. */
enum {GROWTH_FACTOR = 2};

/*--------------------------------------------------------------------*/

/* A Stack object consists of an array of items, and related data. */
struct Stack
{
   /* The array in which items are stored. */
   double *pdArray;

   /* The index one beyond the top element. */
   int iTop;

   /* The number of elements in the array. */
   int iPhysLength;
};

/*--------------------------------------------------------------------*/

/* Double the physical length of oStack.  Return 1 (TRUE) if
   successful, or 0 (FALSE) if insufficient memory is available. */

static int Stack_grow(Stack_T oStack)
{
   int iNewPhysLength;
   double *pdNewArray;
   assert(oStack != NULL);
   iNewPhysLength = oStack->iPhysLength * GROWTH_FACTOR;
   pdNewArray = (double*)
      realloc(oStack->pdArray, sizeof(double) * iNewPhysLength);
   if (pdNewArray == NULL)
      return 0;
   oStack->iPhysLength = iNewPhysLength;
   oStack->pdArray = pdNewArray;

   return 1;
}

/*--------------------------------------------------------------------*/

/* Return a new Stack_T object, or NULL if insufficient memory is
   available. */

Stack_T Stack_new(void)
{
   Stack_T oStack;

   oStack = (Stack_T)malloc(sizeof(struct Stack));
   if (oStack == NULL)
      return NULL;

   oStack->pdArray =
      (double*)calloc(INITIAL_PHYS_LENGTH, sizeof(double));
   if (oStack->pdArray == NULL)
   {
      free(oStack);
      return NULL;
   }

   oStack->iTop = 0;
   oStack->iPhysLength = INITIAL_PHYS_LENGTH;
   return oStack;
}

/*--------------------------------------------------------------------*/

/* Free oStack. */

void Stack_free(Stack_T oStack)
{
   assert(oStack != NULL);
   free(oStack->pdArray);
   free(oStack);
}

/*--------------------------------------------------------------------*/

/* Push dItem onto oStack.  Return 1 (TRUE) if successful, or 0
   (FALSE) if insufficient memory is available. */

int Stack_push(Stack_T oStack, double dItem)
{
   assert(oStack != NULL);
   if (oStack->iTop == oStack->iPhysLength)
      if (! Stack_grow(oStack))
         return 0;
   (oStack->pdArray)[oStack->iTop] = dItem;
   (oStack->iTop)++;
   return 1;
}

/*--------------------------------------------------------------------*/

/* Pop and return the top item of oStack. */

double Stack_pop(Stack_T oStack)
{
   assert(oStack != NULL);
   assert(oStack->iTop > 0);
   (oStack->iTop)--;
   return (oStack->pdArray)[oStack->iTop];
}

/*--------------------------------------------------------------------*/

/* Return 1 (TRUE) if oStack is empty, or 0 (FALSE) otherwise. */

int Stack_isEmpty(Stack_T oStack)
{
   assert(oStack != NULL);
   return oStack->iTop == 0;
}
