#include <stdio.h>
#define M 30



int mezclar_sumas(int A[], int ini, int mid, int fin){
    int i,B[M];
    B[mid] = A[mid];

    //Calculamos la acumulacion de valores desde la mitad hacia la izquierda
    for(i = mid-1; i >=ini ; i--)
        B[i] = B[i+1] + A[i];
    
    //Calculamos la acumulación de valores desde la mitad hacia la derecha
    B[mid+1] = A[mid+1];
    for(i = mid+2; i <=fin; i++)
        B[i] = B[i-1] + A[i];

    //Las acumulaciones ya tienen la suma de elementos desde la mitad, 
	//entonces si encontramos
    // el maximo de cada acumulacion, ese seria el mejor valor de renta 
	//que podra ser compartido
    int max1 = B[mid];
    int max2 = B[mid+1];

    //Encontramos la mayor acumulacion de la izquierda
    for(i = mid-1; i >=ini ; i--){
        if(B[i] > max1)
            max1 = B[i];
    }
    //Encontramos la mayor acumulacion de la derecha
    for(i = mid+2; i <=fin; i++)
       if(B[i] > max2)
            max2 = B[i];
 
    //Retornamos la suma de los maximos, ya que son los maximos 
	//que pueden ser compartidos
    return (max1 + max2);
    
}

int suma_maxima(int A[], int ini, int fin){
    if(ini == fin)
        return A[ini];
    
    int mid = (ini+fin)/2;
   
    int max1 = suma_maxima(A, ini, mid);
    int max2 = suma_maxima(A, mid+1, fin);
    int max3 = mezclar_sumas(A, ini, mid, fin);

    
    int max = max1;
    if(max2 > max)  max = max2;
    if(max3 > max)  max = max3;
	
	
    return max;
}

int main(){
    int A[] = {-2, -5, 6, -2, -3, 1, 5, -6};
	int n = 8;

    int max = suma_maxima(A, 0, n-1);

    printf("\n\nLa suma maxima es %d\n", max);
    return 0;
}