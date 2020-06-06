#ifndef EXCERCISES_P1_H
#define EXCERCISES_P1_H

typedef struct Tnode TNode;
typedef TNode* TList;

struct Tdata {
    int data;
};

struct Tnode {
    int data;
    TNode* next;
};

void create_list(TList* ptr_list);
void show_list(TList ptr_list);
void append_node(TList* ptr_list, int data);
void recorrido(int, TList[], int, int, int*);
void reverse(TList* ptr_list);
void print_and_remove_first(TList *ptr_list);
void print_and_remove_last(TList *ptr_list);
int list_size(TList ptr_list);


#endif //EXCERCISES_P1_H
