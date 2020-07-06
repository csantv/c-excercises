#ifndef EXCERCISES_P1_H
#define EXCERCISES_P1_H

typedef enum {false, true} bool;

static const char * dias[] = {
        "Lunes", "Martes", "Miercoles", "Jueves", "Viernes"
};

static const char * estados[] = {
        "A tiempo", "Retraso", "No llego"
};

typedef struct Node TNode;
typedef struct Tree TBinaryTree;

struct Node {
    int cod;
    int dia;
    int hora;
    int est;
    TNode * left;
    TNode * right;
};

struct Tree {
    TNode * root;
};

void print_reporte(TNode*);
void create_binary_tree(TBinaryTree**);
bool insert(TBinaryTree**, int, int, int);
void free_tree(TNode**);
void get_node(TBinaryTree*, TNode**, int, int, int);
bool hay_cruce(TBinaryTree*, int, int);
void registro_estado(TBinaryTree**);

#endif //EXCERCISES_P1_H
