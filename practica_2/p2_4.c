#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct nodo Lista;

Lista *lista = NULL; // apunta al inicio de la lista
int puntos = 0; // número de elementos en la lista
int tam = 2; // tamaño inicial del punto
int colors[3] = {0, 0, 0};  // color inicial
int L=3;
int I = 400;

// Estructura de la lista
struct nodo{
    int x, y;
    int colors[3];
    struct nodo *sig;
    int tam;
};

// Función que se ejecuta para redimensionar e inicializar la ventana
void ajusta(int ancho, int alto){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

// Función que inserta un nodo al final de la lista
void insertarALista(int x, int y, int colors[3], int tam){
    Lista *nuevo = (Lista *)malloc(sizeof(Lista));
    nuevo->x = x;
    nuevo->y = y;
    nuevo->colors[0] = colors[0];
    nuevo->colors[1] = colors[1];
    nuevo->colors[2] = colors[2];
    nuevo->tam = tam;
    nuevo->sig = NULL;
    // si la lista está vacía el nuevo nodo es el primero
    if (lista == NULL){
        lista = nuevo;
    }else{ // si la lista no está vacía se inserta al final
        Lista *aux = lista; // aux apunta al inicio de la lista
        while (aux->sig != NULL){ // recorre la lista hasta el final
            aux = aux->sig;
        }
        aux->sig = nuevo; // inserta el nuevo nodo al final de la lista
    }
}

// Función que se ejecuta cuando se pulsa un botón del ratón
void raton(int boton, int estado, int x, int y){ // botón del ratón
    int altoVentana = 480;
    colors[0] = rand() % 255;
    colors[1] = rand() % 255;
    colors[2] = rand() % 255;
    if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN){ // botón izquierdo del mouse
        insertarALista(x, altoVentana - y, colors,tam); // inserta el punto en la lista
        puntos++; // incrementa el número de puntos
    }
    glutPostRedisplay(); // Redibuja la ventana
}

// obtener el valor absoluto de un número
int abs(int n){
    if (n < 0){
        return -n;
    }else{
        return n;
    }
}

void dibuja(void){ // función de dibujo
    glClear(GL_COLOR_BUFFER_BIT); // borra la pantalla

    Lista *aux = lista; // aux apunta al inicio de la lista
    while (aux != NULL){ // recorre la lista hasta el final
        glColor3ub(aux->colors[0], aux->colors[1], aux->colors[2]); // color del punto
        glPointSize(aux->tam); // tamaño del punto

        int x1 = aux->x;
        int y1 = aux->y;
        glBegin(GL_POINTS);
        for (int i = 0; i < I; i++){
            int xm1=40*(1+2*L)-y1+abs(x1-120);
            int ym1=x1;
            glVertex2i(xm1, ym1);
            x1=xm1;
            y1=ym1;
        }
        glEnd();

        aux = aux->sig; // avanza al siguiente nodo
    }

    glFlush();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Dibujando puntos");
    // Registro de funciones
    glutDisplayFunc(dibuja); 
    glutMouseFunc(raton); // función de ratón
    glutReshapeFunc(ajusta); // función de ajuste de ventana
    glutMainLoop(); // Bucle de eventos
    return 0;
}