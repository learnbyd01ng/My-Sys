/*--------------------------------------------------------------------*/
/* teststack.c                                                        */
/* Author: Bob Dondero                                                */
/* A client of a generic Stack ADT                                    */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/*--------------------------------------------------------------------*/

/* Write an error message to stderr indicating that not enough memory
   is available.  Then exit with status EXIT_FAILURE. */

static void handleMemoryError(void)
{
   fprintf(stderr, "Insufficient memory\n");
   exit(EXIT_FAILURE);
}

/*--------------------------------------------------------------------*/

/* Test the Stack ADT.  Return 0, or EXIT_FAILURE if not enough memory
   is available. */

int main(void)
{
   Stack_T oStack1;
   Stack_T oStack2;
   double *pd;
   int iSuccessful;

   /* Create and use a Stack of strings. */

   oStack1 = Stack_new();
   if (oStack1 == NULL) handleMemoryError();

   iSuccessful = Stack_push(oStack1, "Ruth");
   if (! iSuccessful) handleMemoryError();

   iSuccessful = Stack_push(oStack1, "Gehrig");
   if (! iSuccessful) handleMemoryError();

   iSuccessful = Stack_push(oStack1, "Mantle");
   if (! iSuccessful) handleMemoryError();

   iSuccessful = Stack_push(oStack1, "Jeter");
   if (! iSuccessful) handleMemoryError();

   while (! Stack_isEmpty(oStack1))
      printf("%s\n", (char*)Stack_pop(oStack1));

   Stack_free(oStack1);

   /* Create and use a Stack of doubles. */

   oStack2 = Stack_new();
   if (oStack2 == NULL) handleMemoryError();

   pd = (double*)malloc(sizeof(double));
   if (pd == NULL) handleMemoryError();
   *pd = 1.1;
   iSuccessful = Stack_push(oStack2, pd);
   if (! iSuccessful) handleMemoryError();

   pd = (double*)malloc(sizeof(double));
   if (pd == NULL) handleMemoryError();
   *pd = 2.2;
   iSuccessful = Stack_push(oStack2, pd);
   if (! iSuccessful) handleMemoryError();

   pd = (double*)malloc(sizeof(double));
   if (pd == NULL) handleMemoryError();
   *pd = 3.3;
   iSuccessful = Stack_push(oStack2, pd);
   if (! iSuccessful) handleMemoryError();

   while (! Stack_isEmpty(oStack2))
   {
      pd = (double*)Stack_pop(oStack2);
      printf("%g\n", *pd);
      free(pd);
   }

   Stack_free(oStack2);

   return 0;
}
