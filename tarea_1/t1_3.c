#include <stdio.h>

int main()
{
    FILE *poli;
    char nombre[] = "./files/polyline.dat";
    int n_lineas, n_vertices, x, y;
    poli = fopen(nombre, "r");
    if (poli == NULL){
        printf("No se puede abrir el archivo %s\n", nombre);
        return 1;
    }
    fscanf(poli, "%d", &n_lineas);
    printf("Numero de lineas: %d\n", n_lineas);
    for (int i = 0; i < n_lineas; ++i){
        fscanf(poli, "%d", &n_vertices);
        printf("Linea %d: %d vertices -> ", i + 1, n_vertices);
        for (int j = 0; j < n_vertices; ++j){
            fscanf(poli, "%d %d", &x, &y);
            printf("(%d,%d)", x, y);
        }
        printf("\n");
    }
    fclose(poli);
    return 0;
}