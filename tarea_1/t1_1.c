#include <stdio.h>
int main(){
    int x,y;
    int tam_tab=8; // tamaño del tablero
    int nums_validos=0;
    do {
        printf("Dame la coordenada de x:\n");
        scanf("%d",&x);
        printf("Dame la coordenada de y:\n");
        scanf("%d",&y);
        printf("\nx:%d, y:%d\n",x,y);

        if(x>=tam_tab || y>=tam_tab || x<0 || y<0){
            printf("Coordenadas no validas, intenta de nuevo.\n\n");
        }else{
            nums_validos=1;
        }
    }while(nums_validos==0);

    for (int i = 0; i < tam_tab; ++i) {
        int pos_y=tam_tab-1-i; // posición en y
        printf("%d ",pos_y); // digitos de la izquierda
        for (int j = 0; j < tam_tab; ++j) { // impresión en cada línea
            int pos_x=j;

            if(pos_y==y && j==x){ // posición del alfil
                printf("A ");
            // posición de las x
            } else if( (pos_x-pos_y==x-y) || (pos_x+pos_y==x+y) ) {
                printf("x ");
            } else { // relleno
                printf("- ");
            }
        }
        printf("\n");
    }

    // numeración inferior
    printf("  ");
    for (int i = 0; i < tam_tab; ++i) {
        printf("%d ",i);
    }

    printf("\n");
    return 0;
}