#ifndef EXCERCISES_P2_H
#define EXCERCISES_P2_H

typedef struct Node TNode;
typedef struct Tree TBinaryTree ;

struct Node {
    int lote;
    int cant;
    TNode * left;
    TNode * right;
};

struct Tree {
    TNode * root;
};

void create_binary_tree(TBinaryTree**);
void insert(TNode**, int, int);
void print_inorder(TNode*);
void print_preorder(TNode*);
void combine_util(TBinaryTree**, TNode**);
void free_tree(TNode**);
void combine(TBinaryTree**, TBinaryTree**);
void get_node(TBinaryTree*, TNode**, int);
int weight(TNode*);

#endif
