// C-Excercises , algoritmos en C que uso
// Copyright (C) 2020   Carlos Toro
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <stdio.h>
#include <stdlib.h>
#include <gc/gc.h>

#include "p1.h"

int main()
{
    TBinaryTree* tree;
    create_binary_tree(&tree);

    insert(&tree->root, 20170810, 20);
    insert(&tree->root, 20170620, 20);
    insert(&tree->root, 20180211, 20);
    insert(&tree->root, 20180409, 20);

    print_inorder(tree->root);
    printf("\n");
    dispatch(35, &tree);
    print_inorder(tree->root);
    printf("\n");

    return 0;
}

void dispatch(int cant, TBinaryTree** tree)
{
    while (cant) {
        TNode * node = NULL;
        oldest(*tree, &node);
        node->cant--;
        if (!node->cant) {
            remove_node(tree, node->lote);
        }
        cant--;
    }
}

void remove_node(TBinaryTree** tree, int lote)
{
    TNode * aux = (*tree)->root;
    TNode * p = NULL;

    // avanzar hasta el nodo con el valor requerido
    while (aux) {
        if (aux->lote == lote) break;

        p = aux;
        if (lote < aux->lote) {
            aux = aux->left;
        } else {
            aux = aux->right;
        }
    }

    if (!aux) return; // no hacer nada si no se encontro

    // primer caso, el nodo es una hoja
    if (!aux->left && !aux->right) {
        // el nodo es la raiz
        if (!p) {
            (*tree)->root = NULL;
        } else {
            if (p->left == aux) {
                p->left = NULL;
            } else if (p->right == aux) {
                p->right = NULL;
            }
        }
        return;
    }

    // el nodo tiene 1 solo hijo por la izquierda
    if (aux->left && !aux->right) {
        // el nodo es la raiz
        if (!p) {
            (*tree)->root = aux->left;
        } else {
            if (p->left == aux) {
                p->left = aux->left;
            } else if (p->right == aux) {
                p->right = aux->left;
            }
        }
        return;
    }

    // el nodo tiene 1 solo hijo por la derecha
    if (!aux->left && aux->right) {
        // el nodo es la raiz
        if (!p) {
            (*tree)->root = aux->right;
        } else {
            if (p->left == aux) {
                p->left = aux->right;
            } else if (p->right == aux) {
                p->right = aux->right;
            }
        }
        return;
    }

    // en el caso que el nodo a eliminar tenga 2 hijos
    TNode * q = aux->left;
    while (q->right)
        q = q->right;

    int data = q->lote;
    remove_node(tree, data);

    aux->lote = data;
}

void print_inorder(TNode* node)
{
    if (!node) return;
    print_inorder(node->left);
    printf("(%d - %d) ", node->lote, node->cant);
    print_inorder(node->right);
}

void oldest(TBinaryTree* tree, TNode** node)
{
    TNode * runner = tree->root;

    while (runner->left) {
        runner = runner->left;
    }

    *node = runner;
}

void create_binary_tree(TBinaryTree** tree)
{
    *tree = GC_malloc(sizeof(TBinaryTree));
    (*tree)->root = NULL;
}

void insert(TNode** root, int lote, int cant)
{
    TNode * node = *root;

    if (!node) {
        node = GC_malloc(sizeof(TNode));
        node->left = NULL;
        node->right = NULL;
        node->lote = lote;
        node->cant = cant;
        *root = node;
        return;
    }

    if (lote > node->lote) {
        insert(&node->right, lote, cant);
    } else {
        insert(&node->left, lote, cant);
    }
}