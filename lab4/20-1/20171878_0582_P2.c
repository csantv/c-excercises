/*
 *  Estrategia:
 *
 *  Las estructuras son las mismas a las vistas en clase, con modificacion
 *  para adaptar a la cantidad de datos que se tiene
 *
 *  Para combinar los arboles se crea una funcion
 *  combinar y una funcion combinar_util, combinar decide que
 *  arbol es el emisor y cual es el destino, para finalmente
 *  ejecutar la funcion combinar_util el cual se va a encargar
 *  de combinar ambos arboles.
 *
 *  Para imprimir en orden y preorden se utilizan funciones
 *  recursivas
 *
 *  Para obtener datos se tiene un bucle el cual obtiene el lote
 *  y la cantidad de cada producto, y decide a cual arbol insertar
 *  los datos
 */

#include <stdlib.h>
#include <stdio.h>

// Estructuras necesarias para el programa
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

// prototypes de las funciones
void create_binary_tree(TBinaryTree**);
void insert(TNode**, int, int);
void print_inorder(TNode*);
void print_preorder(TNode*);
void combine_util(TBinaryTree**, TNode**);
void free_tree(TNode**);
void combine(TBinaryTree**, TBinaryTree**);
void get_node(TBinaryTree*, TNode**, int);
int weight(TNode*);

int main()
{
    // Ingreso de cantidad de almacenes
    int num_alm = 0;
    printf("Ingres el numero de almacenes: ");
    scanf("%d", &num_alm);

    // Inicializar todos los almacenes
    TBinaryTree* almacenes[num_alm];
    for (int i = 0; i < num_alm; ++i) {
        create_binary_tree(&almacenes[i]);
    }

    // Ingreso de datos de los almacenes
    int num, lote, cantidad;
    for (int i = 0; i < num_alm; ++i) {
        printf("Ingrese cantidad de productos en el almacen %d: ", i + 1);
        TBinaryTree * tree = almacenes[i];
        scanf("%d", &num);
        for (int j = 0; j < num; ++j) {
            printf("Lote: ");
            scanf("%d", &lote);
            printf("Cantidad: ");
            scanf("%d", &cantidad);
            insert(&tree->root, lote, cantidad);
        }
    }

    // Que arboles se van a combinar
    int n1 = 0, n2 = 0;
    // verificar errores de input
    while (!((1 <= n1 && n1 <= num_alm) && (1 <= n2 && n2 <= num_alm))) {
        printf("Que almacenes desea combinar:\nAlmacenes disponibles:\n");
        for (int i = 0; i < num_alm; ++i) {
            printf("%d ", i + 1);
        }
        printf("\n");
        scanf("%d %d", &n1, &n2);
    }

    // obtener los arboles que se van a combinar
    TBinaryTree * tree1 = almacenes[n1 - 1];
    TBinaryTree * tree2 = almacenes[n2 - 1];

    // Antes de la union
    printf("Arbol 1 antes de combinar:\n");
    printf("En orden: ");
    print_inorder(tree1->root);
    printf("\n");
    printf("Preorden: ");
    print_preorder(tree1->root);
    printf("\n");
    printf("Arbol 2 antes de combinar:\n");
    printf("En orden: ");
    print_inorder(tree2->root);
    printf("\n");
    printf("Preorden: ");
    print_preorder(tree2->root);
    printf("\n");
    // Combinar los arboles
    combine(&tree1, &tree2);
    // Despues de la union
    printf("Arbol 1 despues de combinar:\n");
    printf("En orden: ");
    print_inorder(tree1->root);
    printf("\n");
    printf("Preorden: ");
    print_preorder(tree1->root);
    printf("\n");
    printf("Arbol 2 despues de combinar:\n");
    printf("En orden: ");
    print_inorder(tree2->root);
    printf("\n");
    printf("Preorden: ");
    print_preorder(tree2->root);

    // Liberar memoria
    if (tree1)
        free_tree(&tree1->root);

    if (tree2)
        free_tree(&tree2->root);

    return 0;
}

// funcion para liberar memoria de un arbol binario
// utilizando recorrido en preorden
void free_tree(TNode** root)
{
    TNode * node = *root;

    if (!node) return;

    free_tree(&node->left);
    free_tree(&node->right);

    free(*root);
    *root = NULL;
}

// Esta funcion decide que arbol es el destino y
// cual es el emisor
void combine(TBinaryTree** tree2, TBinaryTree** tree1)
{
    int w1 = weight((*tree1)->root);
    int w2 = weight((*tree2)->root);

    if (w1 <= w2) {
        combine_util(tree2, &(*tree1)->root);
    } else {
        combine_util(tree1, &(*tree2)->root);
    }
}

// funcion principal que combina 2 arboles
// recursivamente
void combine_util(TBinaryTree** destino, TNode** emisor)
{
    TNode * src = *emisor;

    if (!src) return;

    // utilizar el recorrido en postorden
    combine_util(destino, &src->left);
    combine_util(destino, &src->right);

    TNode * tmp = NULL; // funcion nodo auxiliar
    // obtener el nodo de acuerdo lote del emisor
    get_node(*destino, &tmp, src->lote);

    // si se encontro un nodo, sumar la cantidad al mismo
    // de lo contrario, insertar al arbol como nuevo nodo
    if (tmp) {
        tmp->cant += src->cant;
    } else {
        insert(&(*destino)->root, src->lote, src->cant);
    }

    // al final siempre liberar la memoria del nodo emisor
    free(*emisor);
    *emisor = NULL;
}

// funcion auxiliar el cual obtiene una referencia
// a un nodo en un arbol de acuerdo al lote
void get_node(TBinaryTree* tree, TNode** node, int lote)
{
    TNode * runner = tree->root;

    while (runner) {
        if (runner->lote == lote) break;

        if (runner->lote > lote) {
            runner = runner->left;
        } else {
            runner = runner->right;
        }
    }

    *node = runner;
}

// obtener cantidad de nodos de un arbol
int weight(TNode* node)
{
    if (!node) return 0;

    return 1 + weight(node->left) + weight(node->right);
}

// insertar un nuevo nodo en el arbol recursivamente
void insert(TNode** root, int lote, int cant)
{
    TNode * node = *root;

    if (!node) {
        node = malloc(sizeof(TNode));
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

// inicializar un arbol asignando memoria suficiente
void create_binary_tree(TBinaryTree** tree)
{
    *tree = malloc(sizeof(TBinaryTree));
    (*tree)->root = NULL;
}

// Impresion en orden
void print_inorder(TNode* node)
{
    if (!node) return;
    print_inorder(node->left);
    printf("(%d - %d) ", node->lote, node->cant);
    print_inorder(node->right);
}

// Impresion en pre-orden
void print_preorder(TNode* node)
{
    if (!node) return;
    printf("(%d - %d) ", node->lote, node->cant);
    print_preorder(node->left);
    print_preorder(node->right);
}