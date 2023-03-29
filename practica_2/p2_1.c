#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct nodo Lista;

Lista *lista = NULL; // apunta al inicio de la lista
Lista *ultimo = NULL; // apunta al final de la lista
int puntos = 0; // número de puntos
int tam = 8;                 // tamaño inicial del punto
GLboolean mostrar = GL_TRUE; // mostrar o no los puntos
GLboolean modoEdicion = GL_FALSE; // modo edición
int colors[3] = {0, 1, 0};  // color inicial

// Estructura de la lista
struct nodo{
    int x, y;
    int colors[3];
    struct nodo *sig;
    int tam;
};

// Función que inserta un nodo al final de la lista
void insertarALista(int x, int y, int colors[3], int tam){
    if(modoEdicion==GL_TRUE){
        modoEdicion = !modoEdicion;
        printf("Modo edición desactivado\n");
    }
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
}

// Función que se ejecuta para redimensionar e inicializar la ventana
void ajusta(int ancho, int alto){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

// Función que se ejecuta cuando se pulsa un botón del ratón
void raton(int boton, int estado, int x, int y){ // botón del ratón
    int altoVentana = 480;
    if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN){ // botón izquierdo del mouse
        insertarALista(x, altoVentana - y, colors,tam); // inserta el punto en la lista
        puntos++; // incrementa el número de puntos
    }
    glutPostRedisplay(); // Redibuja la ventana
}

// Función que se ejecuta cuando se pulsa una tecla especial
void pageUp_Down(int tecla, int x, int y){
    switch (tecla){
        case 27:
            exit(0); // Esc =>Salir del programa
        case GLUT_KEY_UP: // PageUp (flecha arriba) => aumenta el tamaño del punto
            if (modoEdicion == GL_TRUE){
                ultimo->tam++;
                printf("El tamaño del último punto cambio a %d\n", ultimo->tam);
            }else{
                tam++;
                printf("Tamaño = %d\n", tam);
            }
            break;
        case GLUT_KEY_DOWN: // PageDown (flecha abajo) => disminuye el tamaño del punto
            if (modoEdicion == GL_TRUE){
                if (ultimo->tam > 1){
                    ultimo->tam--;
                    printf("El tamaño del último punto cambio a %d\n", ultimo->tam);
                }
            }else{
                if (tam > 1){
                    tam--;
                    printf("Tamaño = %d\n", tam);
                }
            }
            break;
        case GLUT_KEY_LEFT: // Home (flecha izquierda) => borra todos los puntos
            puntos = 0;
            Lista *aux = lista; // aux apunta al inicio de la lista
            while (aux != NULL){
                Lista *aux2 = aux; // aux2 apunta al nodo a borrar
                aux = aux->sig;
                free(aux2); // libera el nodo
                lista = NULL;
                ultimo = NULL;
            }
            printf("se borraron todos los puntos\n");
            break;
        default:
            break;
    }
    glutPostRedisplay(); // Redibuja la ventana
}

// Función que se ejecuta cuando se pulsa una tecla normal
void teclado(unsigned char tecla, int x, int y){ // tecla normal
    switch (tecla){
    case 27:
        exit(0); // Esc =>Salir del programa
    case 'r': // r => cambia el color del punto a rojo
        if (modoEdicion == GL_TRUE){
            ultimo->colors[0] = 1;
            ultimo->colors[1] = 0;
            ultimo->colors[2] = 0;
            printf("El color del último punto cambio a rojo\n");
        }else{
            colors[0] = 1;
            colors[1] = 0;
            colors[2] = 0;
            printf("El color cambio a rojo\n");
        }
        break;
    case 'g': // g => cambia el color del punto a verde
        if (modoEdicion == GL_TRUE){
            ultimo->colors[0] = 0;
            ultimo->colors[1] = 1;
            ultimo->colors[2] = 0;
            printf("El color del último punto cambio a verde\n");
        }else{
            colors[0] = 0;
            colors[1] = 1;
            colors[2] = 0;
            printf("El color cambio a verde\n");
        }
        break;
    case 'b': // b => cambia el color del punto a azul
        if (modoEdicion == GL_TRUE){
            ultimo->colors[0] = 0;
            ultimo->colors[1] = 0;
            ultimo->colors[2] = 1;
            printf("El color del último punto cambio a azul\n");
        }else{
            colors[0] = 0;
            colors[1] = 0;
            colors[2] = 1;
            printf("El color cambio a azul\n");
        }
        break;
    case 'y': // y => cambia el color del punto a amarillo
        if (modoEdicion == GL_TRUE){
            ultimo->colors[0] = 1;
            ultimo->colors[1] = 1;
            ultimo->colors[2] = 0;
            printf("El color del último punto cambio a amarillo\n");
        }else{
            colors[0] = 1;
            colors[1] = 1;
            colors[2] = 0;
            printf("El color cambio a amarillo\n");
        }
        break;
    case 'm': // m => mostrar u ocultar puntos
        mostrar = !mostrar;
        if (mostrar == GL_TRUE)
            printf("Se muestran los puntos\n");
        else
            printf("Se ocultan los puntos\n");
        break;
    case 'e':
        modoEdicion = !modoEdicion;
        if (modoEdicion == GL_TRUE)
            printf("Modo edición activado\n");
        else
            printf("Modo edición desactivado\n");
        break;
    default:
        break;
    }
    glutPostRedisplay(); // Redibuja la ventana
}

void dibuja(void){ // función de dibujo
    glClear(GL_COLOR_BUFFER_BIT); // borra la pantalla

    if (mostrar==GL_TRUE){
        // Dibuja las líneas almacenados en la estructura
        Lista *aux = lista; // aux apunta al inicio de la lista
        glBegin(GL_LINE_STRIP);
        while (aux != NULL){
            glColor3f(aux->colors[0], aux->colors[1], aux->colors[2]);
            glVertex2i(aux->x, aux->y);
            aux = aux->sig;
        }
        glEnd();

        // Dibuja los puntos almacenados en la estructura
        aux = lista; // aux apunta al inicio de la lista
        while (aux != NULL){
            glColor3f(aux->colors[0], aux->colors[1], aux->colors[2]);
            glPointSize(aux->tam);
            glBegin(GL_POINTS);
                glVertex2i(aux->x, aux->y);
            glEnd();
            aux = aux->sig;
        }
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
    glutKeyboardFunc(teclado); // función de teclado
    glutSpecialFunc(pageUp_Down); // función de teclado especial
    glutReshapeFunc(ajusta); // función de ajuste de ventana
    glutMainLoop(); // Bucle de eventos
    return 0;
}