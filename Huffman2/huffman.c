#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
void Free_tree(Tree* tree)
{
	if (tree == NULL)
	{
		return;
	}
    Free_tree(tree->left);
    Free_tree(tree->right);
	free(tree);
}


void print_node(Node *pq,FILE* fp)
{
     while(pq != NULL)
	 {
		 fprintf(fp,"%c:%d->",pq->ptr->ch,pq->ptr->fre);
		 pq = pq->next;
	 }
	 fprintf(fp,"NULL\n");
	 return;
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
Node *pq_enqueue(Node **pq, Tree* node)
{
   Node *new_pq = malloc(sizeof(*new_pq));
   Node *copy_pq = *pq;
   if (new_pq == NULL)
   {
	   return NULL;
   }
   new_pq->ptr = node;
   new_pq->next = NULL;
   if (*pq == NULL)
   {
	   *pq = new_pq;
	   return *pq;
   }
   if ((new_pq->ptr->fre < copy_pq->ptr->fre) ||
		   (new_pq->ptr->fre == copy_pq->ptr->fre && new_pq->ptr->ch < copy_pq->ptr->ch
		   && new_pq->ptr->ch != '\0'))
   {
      new_pq->next = copy_pq;
	  *pq = new_pq;
	  return new_pq;
   }
   while(copy_pq -> next != NULL)// && 
   {
	   if(new_pq -> ptr -> fre < copy_pq -> next -> ptr -> fre)
	   {
		   break;
	   }
	   if(new_pq -> ptr -> fre == copy_pq -> next -> ptr -> fre
			   && new_pq -> ptr -> ch < copy_pq -> ptr -> ch
			   && new_pq -> ptr -> ch != '\0')
	   {
		   break;
	   }
	   	copy_pq = copy_pq->next;	
   }
	
	new_pq->next = copy_pq->next;
	copy_pq->next = new_pq;
	return new_pq;
}

                   
long long* read_from_file(FILE *fp)
{
	if (fp == NULL)
	{
		return NULL;
	}
	long long *arr = calloc(256,sizeof(*arr));
	
	while (true)
	{
    	int c = fgetc(fp);
		if (feof(fp))
		{
			break;
		}
		arr[c]++;
	}
    return arr;
}

void write_to_out_1(FILE *fp,long long *arr)
{
	if (fp == NULL)
	{
		return;
	}
    for (int i = 0; i < 256; i++)
	{
		fprintf(fp,"%lld\n",arr[i]);
	}
	return;
}

Node* write_to_out_2(FILE *fp,long long *arr)
{
	if (fp == NULL)
	{
		return NULL;
	}
	Node* list = NULL;
	for (int i = 0; i < 256; i++)
    {
		if (arr[i] != 0)
		{
			Tree* node = malloc(sizeof(*node));
			node->fre = arr[i];
			node->ch = i;
			node->left = NULL;
			node->right = NULL;
			pq_enqueue(&list,node);
		}
	}
	print_node(list,fp);
   return list;
}
Tree *get_the_tree(Node* huff)
{
	while(huff->next != NULL)
	{
		Tree *copy = malloc(sizeof(*copy));
	    Node* tail_1 = pq_dequeue(&huff);
		copy->left = tail_1->ptr;
		Node* tail_2 = pq_dequeue(&huff);
		copy->right = tail_2->ptr;
		copy->fre = tail_1->ptr->fre + tail_2->ptr->fre;
		copy->ch = '\0';
		pq_enqueue(&huff,copy);
		free(tail_1);
		free(tail_2);
	}
	Tree* f_tree = huff->ptr;
	free(huff);
	return f_tree;
}
        

void write_to_out_3(Tree* f_tree, char* list,FILE* fp)
{
	int len = strlen(list);
	if (f_tree->left != NULL)
	{
		list[len] = '0';
		write_to_out_3(f_tree->left,list,fp);
        list[len] = '1';
		write_to_out_3(f_tree->right,list,fp);
		list[len] = '\0';
	}
	else
	{
		fprintf(fp,"%c:%s\n",f_tree->ch,list);
	}
	return;
}
