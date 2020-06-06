#ifndef EXCERCISES_P2_H
#define EXCERCISES_P2_H

typedef struct Tnode TNode;
typedef TNode* TList;

struct Tnode {
    int peso;
    TNode* next;
};

void int_to_bin(unsigned int num, int size, int* out);
void maximizar_pesos(TList*, int[4][3], int);
void cargar_lista(TList* ptr_list, int num_cajas);
void create_list(TList* ptr_list);
void append_node(TList* ptr_list, int data);
void order_list(TList* ptr_list);
void swap_nodes(TNode*,TNode*);
void show_matrix(int[4][3]);
TNode* get_node(TList* ptr_list, int index);


#endif
