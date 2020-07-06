#ifndef EXCERCISES_P4_H
#define EXCERCISES_P4_H

typedef enum {false, true} bool;

static const char * dias[] = {
    "Lunes", "Martes", "Miercoles", "Jueves", "Viernes"
};

static const char * profesores[] = {
    "Guanira", "Cueva", "Sipiran", "Aguilera"
};

typedef struct Node TNode;
typedef struct Tree TBinaryTree;
typedef struct Stack TStack;

struct Node {
    int prof;
    int dia;
    int ini;
    int fin;
    TNode * left;
    TNode * right;
};

struct Tree {
    TNode * root;
};

void create_binary_tree(TBinaryTree**);
void insert(TBinaryTree**, int, int, int, int);
bool hay_cruce(TBinaryTree*, int, int, int, int);
void preorder_it(TBinaryTree*);

struct Stack {
    TNode * node;
    TStack * next;
};

TNode* pop(TStack**);
void push(TStack**, TNode*);
void create_stack(TStack*);

#endif //EXCERCISES_P4_H
