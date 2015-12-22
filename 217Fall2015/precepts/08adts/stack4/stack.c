/*--------------------------------------------------------------------*/
/* stack.c (Version 4)                                                */
/* Author: Bob Dondero                                                */
/*--------------------------------------------------------------------*/

#include <assert.h>
#include <stdlib.h>
#include "stack.h"

/*--------------------------------------------------------------------*/

/* Each item is stored in a StackNode.  StackNodes are linked to
   form a list.  */

struct StackNode
{
   /* The item. */
   double dItem;

   /* The address of the next StackNode. */
   struct StackNode *psNextNode;
};

/*--------------------------------------------------------------------*/

/* A Stack is a structure that points to the first StackNode. */

struct Stack
{
   /* The address of the first StackNode. */
   struct StackNode *psFirstNode;
};

/*--------------------------------------------------------------------*/

/* Return a new Stack_T object, or NULL if insufficient memory is
   available. */

Stack_T Stack_new(void)
{
   Stack_T oStack;

   oStack = (Stack_T)malloc(sizeof(struct Stack));
   if (oStack == NULL)
      return NULL;

   oStack->psFirstNode = NULL;
   return oStack;
}

/*--------------------------------------------------------------------*/

/* Free oStack. */

void Stack_free(Stack_T oStack)
{
   struct StackNode *psCurrentNode;
   struct StackNode *psNextNode;

   assert(oStack != NULL);

   for (psCurrentNode = oStack->psFirstNode;
        psCurrentNode != NULL;
        psCurrentNode = psNextNode)
   {
      psNextNode = psCurrentNode->psNextNode;
      free(psCurrentNode);
   }

   free(oStack);
}

/*--------------------------------------------------------------------*/

/* Push dItem onto oStack.  Return 1 (TRUE) if successful, or 0
   (FALSE) if insufficient memory is available. */

int Stack_push(Stack_T oStack, double dItem)
{
   struct StackNode *psNewNode;

   assert(oStack != NULL);

   psNewNode = (struct StackNode*)malloc(sizeof(struct StackNode));
   if (psNewNode == NULL)
      return 0;

   psNewNode->dItem = dItem;
   psNewNode->psNextNode = oStack->psFirstNode;
   oStack->psFirstNode = psNewNode;
   return 1;
}

/*--------------------------------------------------------------------*/

/* Pop and return the top item of oStack. */

double Stack_pop(Stack_T oStack)
{
   double dItem;
   struct StackNode *psNextNode;
   
   assert(oStack != NULL);
   assert(oStack->psFirstNode != NULL);
   
   dItem = oStack->psFirstNode->dItem;
   psNextNode = oStack->psFirstNode->psNextNode;
   free(oStack->psFirstNode);
   oStack->psFirstNode = psNextNode;
   return dItem;
}

/*--------------------------------------------------------------------*/

/* Return 1 (TRUE) if oStack is empty, or 0 (FALSE) otherwise. */

int Stack_isEmpty(Stack_T oStack)
{
   assert(oStack != NULL);

   return oStack->psFirstNode == NULL;
}
