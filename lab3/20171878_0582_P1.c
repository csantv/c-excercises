#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char MAX[33] = "99999999999990000000999999999000\0";

// 0 - 12 : GTIN
// 13 - 19 : precio
// 20 - 24 : stock
// 25 - 28 : stock_minimo
// 29 - 31 : descuento

// devuelve el stock de la cadena de informacion
int get_stock(char* str)
{
    // copiar substr
    char buff[6];
    for (int i = 0; i < 5; ++i) {
        buff[i] = str[i + 20];
    }
    buff[5] = '\0';
    return atoi(buff);
}

// devuelve el stock minimo de la cadena de informacion
int get_stock_minimo(char* str)
{
    // copiar substr
    char buff[5];
    for (int i = 0; i < 4; ++i) {
        buff[i] = str[i + 25];
    }
    buff[4] = '\0';
    return atoi(buff);
}

// obtener el precio de la cadena de informacion
float get_precio(char* str)
{
    char buff_ent[6]; // parte entera
    char buff_dec[3]; // parte decimal
    // copiar substr
    for (int i = 0; i < 5; ++i) {
        buff_ent[i] = str[i + 13];
    }
    // copiar substr
    for (int i = 0; i < 2; ++i) {
        buff_dec[i] = str[i + 17];
    }
    buff_ent[5] = '\0';
    buff_dec[2] = '\0';
    float num;
    num = atof(buff_ent);
    num += atof(buff_dec) / 100;
    return num;
}

// obtener el descuento
int get_descuento(char* str)
{
    // copiar substr
    char buff[4];
    for (int i = 0; i < 3; ++i) {
        buff[i] = str[i + 29];
    }
    buff[3] = '\0';
    return atoi(buff);
}

// obtener precio final
float get_precio_final(char* str)
{
    float precio = get_precio(str);
    int descuento = get_descuento(str);
    return precio * (float)(100 - descuento) / 100;
}

// obtener gtin
void set_gtin(char* str, char gtin[14])
{
    for (int i = 0; i < 13; ++i) {
        gtin[i] = str[i];
    }
    gtin[13] = '\0';
}

// ordenar usando merge sort descendentemente
void merge_precio_final(int num_prod, char arr[num_prod][33], int begin, int mid, int end)
{
    int n1 = mid - begin + 1;
    int n2 = end - mid;

    char arr1[n1 + 1][33];
    char arr2[n2 + 1][33];

    // copy arrays
    for (int i = begin, j = 0; i <= mid; i++) {
        strcpy(arr1[j], arr[i]);
        j++;
    }

    for (int i = mid + 1, j = 0; i <= end; i++) {
        strcpy(arr2[j], arr[i]);
        j++;
    }

    strcpy(arr1[n1], MAX);
    strcpy(arr2[n2], MAX);

    int i = begin, k = 0, m = 0;
    while (i <= end) {
        if (get_precio_final(arr1[k]) > get_precio_final(arr2[m])) {
            strcpy(arr[i], arr1[k]);
            k++;
        } else {
            strcpy(arr[i], arr2[m]);
            m++;
        }
        i++;
    }
}

// ordenar usando merge sort descendentemente
void merge_descuento(int num_prod, char arr[num_prod][33], int begin, int mid, int end)
{
    int n1 = mid - begin + 1;
    int n2 = end - mid;

    char arr1[n1 + 1][33];
    char arr2[n2 + 1][33];

    // copy arrays
    for (int i = begin, j = 0; i <= mid; i++) {
        strcpy(arr1[j], arr[i]);
        j++;
    }

    for (int i = mid + 1, j = 0; i <= end; i++) {
        strcpy(arr2[j], arr[i]);
        j++;
    }

    strcpy(arr1[n1], MAX);
    strcpy(arr2[n2], MAX);

    int i = begin, k = 0, m = 0;
    while (i <= end) {
        if (get_descuento(arr1[k]) > get_descuento(arr2[m])) {
            strcpy(arr[i], arr1[k]);
            k++;
        } else {
            strcpy(arr[i], arr2[m]);
            m++;
        }
        i++;
    }
}

void merge_sort(int num_prod, char prod[num_prod][33], int begin, int end, int flag)
{
    if (begin == end) return;

    int mid = (begin + end) / 2;
    merge_sort(num_prod, prod, begin, mid, flag);
    merge_sort(num_prod, prod, mid + 1, end, flag);
    // ordenar descendentemente de acuerdo a un flag
    // 1 -> de acuerdo al precio final
    // 0 -> de acuerdo al descuento
    if (flag) {
        merge_precio_final(num_prod, prod, begin, mid , end);
    } else {
        merge_descuento(num_prod, prod, begin, mid , end);
    }
}

// agrupar los productos, tipo merge sort
void agrupar_productos(int num_prod, char orig[num_prod][33], char ord[num_prod][33], int begin, int end, int* num_ofertas, int* index)
{
    // caso base
    if (begin == end) {
        char* str = orig[begin];
        if (get_stock(str) < get_stock_minimo(str)) {
            // copiar la cadena al principio
            strcpy(ord[(*num_ofertas)++], str);
        } else {
            // copiar la cadena desde el final
            strcpy(ord[--(*index)], str);
        }
        return;
    }

    int mid = (begin + end) / 2;
    agrupar_productos(num_prod, orig, ord, begin, mid, num_ofertas, index);
    agrupar_productos(num_prod, orig, ord, mid + 1, end, num_ofertas, index);
}

// obtener el descuento maximo
void get_max_descuento(int num_prod, char orig[num_prod][33], int* desc_max)
{
    // copiar el array de ofertas
    char prod_oferta[num_prod][33];
    for (int i = 0; i < num_prod; ++i) {
        strcpy(prod_oferta[i], orig[i]);
    }
    // ordenar el nuevo array de acuerdo a su descuento descendentemente
    // el maximo descuento se encuentra en el primer elemento
    merge_sort(num_prod, prod_oferta, 0, num_prod - 1, 0);
    *desc_max = get_descuento(prod_oferta[0]);
}

// imprimir datos
void imprimir_ofertas(int max_desc, int num_oferta, char prod[num_oferta][33])
{
    printf("Hasta %d%% de descuento\n", max_desc);
    printf("Los productos del pasillo de ofertas son:\n");
    for (int i = 0; i < num_oferta; ++i) {
        char* str = prod[i];
        char gtin[14];
        set_gtin(str, gtin);
        printf("      %s | %d%% descuento | P.F: S/. %.2lf\n", gtin, get_descuento(str), get_precio_final(str));
    }
}

int main()
{
    // Ingreso de datos
    int num_prod;
    printf("Ingrese la cantidad de productos: ");
    scanf("%d", &num_prod);
    char productos[num_prod][33];
    printf("Ingrese la informacion de los productos:\n");
    for (int i = 0; i < num_prod; ++i) {
        scanf("%s", productos[i]);
    }
    // variables para agrupar productos
    int num_ofertas = 0;
    char productos_ord[num_prod][33];
    int index = num_prod;
    agrupar_productos(num_prod, productos, productos_ord, 0, num_prod - 1, &num_ofertas, &index);
    // copiar productos en oferta a un nuevo array para facilitar el ordenamiento
    char prod_oferta[num_ofertas][33];
    for (int i = 0; i < num_ofertas; ++i) {
        strcpy(prod_oferta[i], productos_ord[i]);
    }
    // ordenar productos usando merge sort
    merge_sort(num_ofertas, prod_oferta, 0, num_ofertas - 1, 1);
    // obtener descuento maximo
    int max_desc = 0;
    get_max_descuento(num_ofertas, prod_oferta, &max_desc);
    // impresion final
    imprimir_ofertas(max_desc, num_ofertas, prod_oferta);
    return 0;
}