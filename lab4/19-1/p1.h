#ifndef EXCERCISES_P1_H
#define EXCERCISES_P1_H

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
void oldest(TBinaryTree*, TNode**);
void print_inorder(TNode*);
void dispatch(int, TBinaryTree**);
void remove_node(TBinaryTree**, int);

#endif
