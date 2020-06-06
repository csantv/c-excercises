#ifndef EXCERCISES_P1_H
#define EXCERCISES_P1_H

typedef struct StackNode TStackNode;
typedef TStackNode* TStack;
typedef struct Dia dia_t;

struct Dia {
    int precio;
    int intervalos;
};

struct StackNode {
    dia_t data;
    TStackNode * next;
};

void create_stack(TStack*);
void push(TStack*,int);
void show_stack_elems(TStack);
void set_intervalos(TStack*);

#endif
