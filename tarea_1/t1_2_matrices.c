#include <stdlib.h>
#include <stdio.h>
#include "t1_2_matrices.h"

const int dim = 100;
int i, j, fil, col = 3;
float matA[3][3] = {{1, 2, 3},
                    {4, 5, 6},
                    {7, 8, 9}};

float matB[3][3] = {{1, 2, 3},
                    {4, 5, 6},
                    {7, 8, 9}};
float matR[3][3];
float matR2[3][3];
float v[3] = {1, 2, 3};
float matR3[3][3];

int main(void){
    // crear e imprimir matriz
    printf("\nMatriz A\n");
    imprime(3, 3, matA);

    // crear e imprimir matriz
    printf("\nMatriz B\n");
    imprime(3, 3, matB);

    // suma de matrices A y B y resultado en matriz R
    suma(3, 3, matA, matB, matR);
    printf("\nResultado Suma\nMatriz R\n");
    imprime(3, 3, matR);

    // multiplicacion de matrices A y B y resultado en matriz R2
    printf("\nResultado Multiplicacion\nMatriz R2\n");
    multiplicacion(3, 3, matA, matB, matR2);
    imprime(3, 3, matR2);

    // crear matriz diagonal a partir de vector v
    creaS(3, v, matR3);
    printf("\nResultado Vector a Matriz\nMatriz R3\n");
    imprime(3, 3, matR3);
}