#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct nodo Lista;

Lista *lista = NULL; // apunta al inicio de la lista
Lista *ultimo = NULL; // apunta al final de la lista
int puntos = 0; // número de puntos
int tam = 4; // tamaño inicial del punto
GLboolean modo = GL_TRUE; // mostrar o no los puntos
int colors[3] = {150, 150, 150}; // color inicial

// Estructura de la lista
struct nodo{
    int x, y;
    int colors[3];
    struct nodo *sig;
    int tam;
};

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
    ultimo = nuevo; // apunta al último nodo de la lista
    if (lista == NULL){
        lista = nuevo;
    }else{
        Lista *aux = lista; // aux apunta al inicio de la lista
        while (aux->sig != NULL){ // recorre la lista hasta el final
            aux = aux->sig;
        }
        aux->sig = nuevo; // inserta el nuevo nodo al final de la lista
    }
    puntos++;
    printf("Se ha insertado un punto en la posición (%d, %d)\n", x, y);
    printf("el número de puntos es %d\n", puntos);
}

// Función que se ejecuta para redimensionar e inicializar la ventana
void ajusta(int ancho, int alto){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

// función que se ejecuta cuando se arrastra el ratón (activa o inactivamente)
void arrastrarse(int x, int y){
    int altoVentana = 480;
    insertarALista(x, altoVentana - y, colors, tam);
    glutPostRedisplay(); // Redibuja la ventana
}

// Función que se ejecuta cuando se pulsa una tecla normal
void teclado(unsigned char tecla, int x, int y){ // tecla normal
    switch (tecla){
        case 'm': 
            modo = !modo;
            if (modo == GL_TRUE)
                printf("Se dibujará cuando el mouse se presione y arrastre\n");
            else
                printf("Se dibujará cuando el mouse pase por la pantalla\n");
            glutMotionFunc(modo?arrastrarse:NULL); // función de arrastre del ratón
            glutPassiveMotionFunc(!modo?arrastrarse:NULL); // función de movimiento del ratón
            break;
        default:
            break;
    }
    glutPostRedisplay(); // Redibuja la ventana
}

void dibuja(void){ // función de dibujo
    glClear(GL_COLOR_BUFFER_BIT); // borra la pantalla

    // Dibuja los puntos
    Lista *aux = lista;
    while (aux != NULL){
        glColor3i(aux->colors[0], aux->colors[1], aux->colors[2]);
        glPointSize(aux->tam);
        glBegin(GL_POINTS);
            glVertex2i(aux->x, aux->y);
        glEnd();
        aux = aux->sig;
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
    glutKeyboardFunc(teclado); // función de tecla normal
    glutMotionFunc(arrastrarse); // función de arrastre del ratón
    glutReshapeFunc(ajusta); // función de ajuste de ventana
    glutMainLoop(); // Bucle de eventos
    return 0;
}