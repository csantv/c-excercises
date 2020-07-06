#include <stdio.h>
#include <gc/gc.h>

#include "p4.h"

int main()
{
    TBinaryTree* tree;
    create_binary_tree(&tree);

    insert(&tree, 0, 0, 10, 12);
    insert(&tree, 1, 0, 12, 15);
    insert(&tree, 2, 1, 10, 13);
    insert(&tree, 3, 2, 15, 18);
    //insert(&tree, 2, 1, 8, 10);
    //insert(&tree, 0, 0, 7, 10);

    preorder_it(tree);

    return 0;
}

void create_binary_tree(TBinaryTree** tree)
{
    *tree = GC_malloc(sizeof(TBinaryTree));
    (*tree)->root = NULL;
}

void insert(TBinaryTree** tree, int prof, int dia, int ini, int fin)
{
    if (hay_cruce(*tree, prof, dia, ini, fin)) {
        printf("Hay cruce en el horario del dia %s de %d:00 a %d:00.\n", dias[dia], ini, fin);
        return;
    }

    TNode * father = NULL;
    TNode * runner = (*tree)->root;

    while (runner) {
        father = runner;
        if (dia < runner->dia ||
                (dia == runner->dia && fin <= runner->ini)) {
            runner = runner->left;
        } else {
            runner = runner->right;
        }
    }

    TNode * node = GC_malloc(sizeof(TNode));
    node->prof = prof;
    node->dia = dia;
    node->ini = ini;
    node->fin = fin;

    if (!father) {
        (*tree)->root = node;
    } else {
        if (dia < father->dia ||
            (dia == father->dia && fin <= father->ini)) {
            father->left = node;
        } else {
            father->right = node;
        }
    }
}

bool hay_cruce(TBinaryTree* tree, int prof, int dia, int ini, int fin)
{
    return false;
}

void preorder_it(TBinaryTree* tree)
{
    TStack * stack = NULL;
    push(&stack, tree->root);

    while (stack) {
        TNode * node = pop(&stack);
        printf("%-12s%-12s%d:00\t%d:00\n", profesores[node->prof], dias[node->dia], node->ini, node->fin);
        if (node->right)
            push(&stack, node->right);
        if (node->left)
            push(&stack, node->left);
    }
}

void push(TStack** stack, TNode* node)
{
    TStack * new_stack = GC_malloc(sizeof(TStack));
    new_stack->node = node;
    new_stack->next = *stack;
    *stack = new_stack;
}

TNode* pop(TStack** stack)
{
    TStack * tmp = NULL;
    TNode * node = NULL;

    if (*stack) {
        tmp = *stack;
        node = tmp->node;
        (*stack) = (*stack)->next;
    }

    return node;
}