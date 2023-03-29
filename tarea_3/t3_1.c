//  Implementa el algoritmos de Bresenham para círculos. Introducir los datos de entrada (el centro y radio 
// del círculo) con el ratón, de tal forma que mientras no se suelte el botón se establezca el tamaño final del 
// círculo. Se debe dibujar más de un círculo eligiendo entre varios colores empleando estructuras.

#if WIN32
    #include <windows.h>
    #include <GL/glut.h>
#endif
#if __APPLE__
    #define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
    #include <GLUT/glut.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct circulo Circulo;
Circulo *listaCirculos=NULL;
// ultimo circulo de la lista
Circulo *ultimoCirculo=NULL;
// bool de glut
GLboolean centro = GL_FALSE;
int x0c, y0c, radio, r, g, b;

struct circulo{
    int x0;
    int y0;
    int radio;
    // color rgb
    int r;
    int g;
    int b;
    struct circulo *sig;
};

// insertar un circulo en la lista
void insertarCirculo(int x0, int y0, int radio, int r, int g, int b){
    Circulo *nuevo = (Circulo *)malloc(sizeof(Circulo));
    nuevo->x0 = x0;
    nuevo->y0 = y0;
    nuevo->radio = radio;
    nuevo->r = r;
    nuevo->g = g;
    nuevo->b = b;
    nuevo->sig = NULL;
    ultimoCirculo = nuevo;
    if(listaCirculos==NULL){
        listaCirculos = nuevo;
    }else{
        Circulo *aux = listaCirculos;
        while(aux->sig!=NULL){
            aux = aux->sig;
        }
        aux->sig = nuevo;
    }
}

// Función que se ejecuta cuando se pulsa un botón del ratón
void raton(int boton, int estado, int x, int y){
    int altoVentana = 480;
    if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
        x0c = x;
        y0c = altoVentana-y;
        printf("Centro establecido\n");
        printf("x0: %d, y0: %d\n",x0c,y0c);
        r = rand()%255;
        g = rand()%255;
        b = rand()%255;
        insertarCirculo(x0c,y0c,0,r,g,b);
    }
    glutPostRedisplay(); // Redibuja la ventana
}

void dibuja8Puntos(int x, int y, int x0, int y0){
    glVertex2i(x0+x,y0+y);
    glVertex2i(x0-x,y0+y);
    glVertex2i(x0+x,y0-y);
    glVertex2i(x0-x,y0-y);
    glVertex2i(x0+y,y0+x);
    glVertex2i(x0-y,y0+x);
    glVertex2i(x0+y,y0-x);
    glVertex2i(x0-y,y0-x);
}

// función de circulo de breseham que reciba el centro y el radio y dibuje el circulo
void circuloBreseham(int x0, int y0, int R){
    // x0 y y0 son las coordenadas del centro del circulo
    int x=0, y=R;
    int d=3-2*R;
    glBegin(GL_POINTS);
    while(x<=y){
        dibuja8Puntos(x,y,x0,y0);
        if(d<0){
            d=d+4*x+6;
        }else{
            d=d+4*(x-y)+10;
            y--;
        }
        x++;
    }
    glEnd();
}

void ajustar(int ancho, int alto){
    glClearColor(1.0,1.0,1.0,0.0); // color de fondo de ventana
    glMatrixMode(GL_PROJECTION); // se modifica la matriz de proyección
    glLoadIdentity();
    gluOrtho2D(0,640,0,480); // la relacion aspecto de la ventana es 640*480
}

void dibujar(void){
    glClear(GL_COLOR_BUFFER_BIT); // limpiar buffer de color

    glColor3b(0,0,0);
    glPointSize(1.0);
    // dibujar circulos en la lista
    Circulo *aux = listaCirculos;
    while(aux!=NULL){
        glColor3b(aux->r,aux->g,aux->b);
        circuloBreseham(aux->x0,aux->y0,aux->radio);
        aux = aux->sig;
    }

    // enviarlo a pantalla
    glFlush();
}

void mover(int x, int y){
        x0c = x;
        y0c = 480-y;
        radio = sqrt(abs(x0c-ultimoCirculo->x0)*abs(x0c-ultimoCirculo->x0)+abs(y0c-ultimoCirculo->y0)*abs(y0c-ultimoCirculo->y0));
        ultimoCirculo->radio = radio;
    glutPostRedisplay();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480); // tamaño de la ventana que se va a obtener
    glutInitWindowPosition(100, 150); // posición donde se colocará la ventana
    glutCreateWindow("Tarea 3.1"); // titulo de la ventana
    glutReshapeFunc(ajustar);
    glutDisplayFunc(dibujar);
    glutMouseFunc(raton);
    glutMotionFunc(mover); // función de movimiento del ratón
    glutMainLoop();
    return 0;
}