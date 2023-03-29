#include <stdio.h>
#include <stdlib.h>

struct fraccion{
    int numerador;
    int denominador;
    struct fraccion *sig;
};

typedef struct fraccion Fraccion;

Fraccion *lista=NULL;

Fraccion *creaNodoLista(int num, int den){
    Fraccion *p;
    p=(Fraccion*)malloc(sizeof(Fraccion));
    p->numerador=num;
    p->denominador=den;
    p->sig=NULL;
    return p;
}

void insertaLista(int num, int den){
    Fraccion *aux=lista;
    if(lista == NULL)
        lista = creaNodoLista(num, den);
    else{
        while(aux->sig != NULL)
            aux = aux->sig;
        aux->sig = creaNodoLista(num, den);
    }
}

void simplifica(int num,int den){
    // si hay unidades enteras se deben imprimir
    if(num > den){
        printf("%d", num / den);
        // se quitan las unidades que se imprimieron a x
        num= num % den;
        if(num!=0){
            printf(", ");
        }else{
            printf("\n");
        }
    }
    // numeros que sirven como temporales para cambiar continuamente
    int num_actual=num;
    int den_actual=den;

    int indivisible=0;

    // si ya no hay nada por simplificar
    if(num_actual<=1){
        indivisible=1;
    }

    // mientras los números sean aun divisibles
    int i;
    while ( indivisible == 0) {
        i=2;
        while ( i <= num_actual ) {
            // si divide a los 2 de forma entera
            if(num_actual%i==0){
                if(den_actual%i==0){
                    // se hace la conversión de ambos numeros
                    num_actual=num_actual/i;
                    den_actual=den_actual/i;
                    break;
                }
            }
            i=i+1;
        }
        // si llegue al final sin divisores o si num actual ya es 1
        if(i-1==num_actual || num_actual==1){
            indivisible=1;
        }
    }
    if(num_actual!=0){
        printf("%d/%d\n",num_actual,den_actual);
    }
}

void imprimeLista(){
    Fraccion *aux=lista;
    while(aux != NULL) {
        printf("%d/%d\t=>\t",aux->numerador,aux->denominador);
        simplifica(aux->numerador,aux->denominador);
        aux = aux->sig;
    }
}

int main(){
    int numerador,denominador;
    do{
        printf("Escribe numerador denominador, denominador 0 para terminar:\n");
        scanf("%d",&numerador);
        scanf("%d",&denominador);

        if(denominador!=0){
            insertaLista(numerador,denominador);
        }
    } while (denominador!=0);

    imprimeLista();

    return 0;
}
