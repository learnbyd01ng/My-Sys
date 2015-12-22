/*--------------------------------------------------------------------*/
/* stack.c (Version 1)                                                */
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

/* Increase the physical length of *psStack.  Return 1 (TRUE) if
   successful, or 0 (FALSE) if insufficient memory is available. */

static int Stack_grow(struct Stack *psStack)
{
   int iNewPhysLength;
   double *pdNewArray;

   assert(psStack != NULL);

   iNewPhysLength = psStack->iPhysLength * GROWTH_FACTOR;

   pdNewArray = (double*)
      realloc(psStack->pdArray, sizeof(double) * iNewPhysLength);
   if (pdNewArray == NULL)
      return 0;

   psStack->iPhysLength = iNewPhysLength;
   psStack->pdArray = pdNewArray;

   return 1;
}

/*--------------------------------------------------------------------*/

/* Return the address of a new Stack object, or NULL if insufficient
   memory is available. */

struct Stack *Stack_new(void)
{
   struct Stack *psStack;

   psStack = (struct Stack*)malloc(sizeof(struct Stack));
   if (psStack == NULL)
      return NULL;

   psStack->pdArray =
      (double*)calloc(INITIAL_PHYS_LENGTH, sizeof(double));
   if (psStack->pdArray == NULL)
   {
      free(psStack);
      return NULL;
   }

   psStack->iTop = 0;
   psStack->iPhysLength = INITIAL_PHYS_LENGTH;
   return psStack;
}

/*--------------------------------------------------------------------*/

/* Free psStack. */

void Stack_free(struct Stack *psStack)
{
   assert(psStack != NULL);

   free(psStack->pdArray);
   free(psStack);
}

/*--------------------------------------------------------------------*/

/* Push dItem onto *psStack.  Return 1 (TRUE) if successful, or 0
   (FALSE) if insufficient memory is available. */

int Stack_push(struct Stack *psStack, double dItem)
{
   assert(psStack != NULL);

   if (psStack->iTop == psStack->iPhysLength)
      if (! Stack_grow(psStack))
         return 0;

   (psStack->pdArray)[psStack->iTop] = dItem;
   (psStack->iTop)++;
   return 1;
}

/*--------------------------------------------------------------------*/

/* Pop and return the top item of *psStack. */

double Stack_pop(struct Stack *psStack)
{
   assert(psStack != NULL);
   assert(psStack->iTop > 0);

   (psStack->iTop)--;
   return (psStack->pdArray)[psStack->iTop];
}

/*--------------------------------------------------------------------*/

/* Return 1 (TRUE) if *psStack is empty, or 0 (FALSE) otherwise.  */

int Stack_isEmpty(struct Stack *psStack)
{
   assert(psStack != NULL);

   return psStack->iTop == 0;
}
