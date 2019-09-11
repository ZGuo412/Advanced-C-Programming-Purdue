#include <stdio.h>
#include <stdlib.h>
typedef struct _Tree{
	int fre;
    char ch;
	struct _Tree *left;
    struct _Tree *right;
}Tree;
typedef struct _Node {
   Tree *ptr;
   struct _Node *next;
} Node;
long long* read_from_file(FILE *fp);
void write_to_out_1(FILE *fp,long long *arr);
Node* write_to_out_2(FILE *fp,long long *arr);
Node *pq_enqueue(Node **pq, Tree*node);
Tree* get_the_tree(Node* huff);
void write_to_out_3(Tree* f_tree, char* list,FILE* fp);
void Free_tree(Tree*tree);

                       
Node *pq_dequeue(Node **pq);
