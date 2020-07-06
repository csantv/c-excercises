#ifndef EXCERCISES_P1_H
#define EXCERCISES_P1_H

typedef struct Tnode TNode;
typedef TNode* TList;


struct Tnode {
    int data;
    TNode* next;
    TNode* prev;
};

void create_list(TList* ptr_list);
void append_node(TList* ptr_list, int data);
void show_list(TList ptr_list);
void biotonic_sort(TList* ptr_list);
void reverse(TList* ptr_list);
TList merge_list(TNode*,TNode*);
void insert_begin(TList *ptr_list, int data);

#endif
