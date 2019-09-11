#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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
void Free_tree(Tree* tree);
void print_node(Node* pq,FILE*fp);
Node* pq_dequeue(Node** pq);
Node* pq_enqueue(Node **pq,Tree *node);
long long* read_from_file(FILE *fp);
Tree* get_the_tree(Node* arr);
Node *get_list(long long *arr);
void write_to_out_1(Tree* f_tree,char* list,FILE* fp);
void add_zero(Tree* tree, FILE* fp);
void write_to_out_2(Tree* f_tree, FILE* fp);
void write_to_out3(FILE* fp, FILE* fp_w);

