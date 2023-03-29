#include <stdio.h>
#include <math.h>
#define PI 3.14159265

char plano[13][49];

void iniciarPlano()
{
    // Columnas
    for (int x = 0; x < 13; x++)
    {
        // Renglones
        for (int y = 0; y < 49; y++)
        {
            plano[x][y] = ' ';
        }
    }
    // Columnas
    for (int i = 0; i < 49; i++)
        plano[6][i] = '-';
    // Renglones
    for (int j = 0; j < 13; j++)
        plano[j][24] = '|';
    plano[6][24] = '+';
}

void evaluaFuncion(double (*funcion)(double), char *caracter)
{
    int amplitud = 6, periodo = 49, f;
    for (int i = 0; i <= periodo; i++)
    {
        f = roundf(amplitud * ((*funcion)(((2 * PI) / periodo) * i)));
        f += roundf(amplitud);
        // if (i % 2 != 0)
        plano[f][i] = *caracter;
    }
}

void imprimePlano()
{
    // Columnas
    for (int x = 0; x < 13; x++)
    {
        // Renglones
        for (int y = 0; y < 49; y++)
        {
            printf("%c", plano[x][y]);
        }
        printf("\n");
    }
}

int main()
{
    // arreglo con puntos y líneas correspondientes
    iniciarPlano();
    printf("Funcion Seno\n");
    evaluaFuncion(sin, "*");
    imprimePlano();

    // arreglo con puntos y líneas correspondientes
    iniciarPlano();
    printf("Funcion Coseno\n");
    evaluaFuncion(cos, "*");
    imprimePlano();
}