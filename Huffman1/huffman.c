#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

Node *pq_enqueue(Node **pq, const void *new_object, 
                  int (*cmp_fn)(const void *, const void *))
{
   if (new_object == NULL)
   {
	   return NULL;
   }
   Node *new_pq = malloc(sizeof(*new_pq));
   Node *copy_pq = *pq;
   if (new_pq == NULL)
   {
	   return NULL;
   }
   new_pq->ptr = (void*)new_object;
   new_pq->next = NULL;
   if (*pq == NULL)
   {
	   *pq = new_pq;
	   return *pq;
   }
   if (cmp_fn(new_pq->ptr, copy_pq->ptr)< 0)
   {
      new_pq->next = copy_pq;
	  *pq = new_pq;
	  return new_pq;
   }
   if (copy_pq->next == NULL)
   {
	   new_pq->next = NULL;
	   copy_pq->next = new_pq;
	   return new_pq;
   }
   while(cmp_fn(new_pq->ptr,copy_pq->next->ptr)> 0)
   {
	   	copy_pq = copy_pq->next;
		if (copy_pq->next == NULL)
		{
			new_pq->next = NULL;
			copy_pq->next = new_pq;
			return new_pq;
		}

   }

	   	new_pq->next = copy_pq->next;
		copy_pq->next = new_pq;
		return new_pq;
}

                   
Node *pq_dequeue(Node **pq)
{
   if (*pq == NULL)
   {
	   return NULL;
   }
   Node *head_p = *pq;
   *pq = (*pq)->next;
   head_p->next = NULL;
   
   return head_p;
}


Node *stack_push(Node **stack, const void *new_object)
{
   if (new_object == NULL)
   {
   return NULL;
   }
   Node *new_n = malloc(sizeof(*new_n));
   if (new_n == NULL)
   {
	   return NULL;
   }
   new_n->ptr =(void*)new_object;
   new_n->next = *stack;
   *stack = new_n;
   return new_n;
}

                       
Node *stack_pop(Node **stack)
{
   if (*stack == NULL)
   {
	   return NULL;
   }
   Node *head_N = *stack;
   *stack = (*stack)->next;
   head_N->next = NULL;
   
   return head_N;
}


Node *remove_last_node(Node **list)
{
   if (*list == NULL)
   {
	   return NULL;
   }
   Node* tail = *list;
   Node* before = *list;
   if (before->next == NULL)
   {
	   *list = NULL;
	   return before;
   }
   while(tail->next != NULL)
   {
	   before = tail;
	   tail = tail->next;
   }
   before->next = NULL;
   
   return tail;
}


void destroy_node(Node *list, void (*destroy_fn)(void *))

{
   while (list!= NULL)
   {
	   destroy_fn(list->ptr);
	   Node* now = list;
	   list = list->next;
	   free(now);
   }
   return;
}

/* print an entire linked list                                           */
/* pq is the address of the first Node in the linked list               */
/* print_fn is the address of the function to print the generic object,  */
/* of which the address is stored in the ptr field of an Node in the    */
/* linked list                                                           */
/*                                                                       */
/* DO NOT CHANGE THIS FUNCTION, OTHERWISE YOUR OUTPUT WILL BE DIFFERENT  */
/* AND YOU WILL NOT RECEIVE CREDIT                                       */
 
void print_node(const Node *list, void (*print_fn)(const void *))
{
   while (list != NULL) {
      // print the memory associated with list->ptr
      print_fn(list->ptr);
      // print an arrow
      fprintf(stdout, "->");
      list = list->next;
   } 
   // print NULL and a newline after that 
   fprintf(stdout, "NULL\n");
}



