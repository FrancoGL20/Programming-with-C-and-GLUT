#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "p2_deadpool.h"

GLboolean paleta=GL_TRUE;
int posX=(640/2)-((ANCHOF/2)*5), posY=(480/2)+((ALTOF/2)*5), salto=20;

// Función que se ejecuta para redimensionar e inicializar la ventana
void ajusta(int ancho, int alto){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

// Función que se ejecuta cuando se pulsa una tecla especial
void pageUp_Down(int tecla, int x, int y){
    switch (tecla){
        case 27:
            exit(0); // Esc =>Salir del programa
        case GLUT_KEY_UP: // PageUp (flecha arriba) => mover deadpool hacia arriba
            paleta=!paleta;
            if (posY < 480-5){
                posY += salto;
            }
            break;
        case GLUT_KEY_DOWN: // PageDown (flecha abajo) => mover deadpool hacia abajo
            paleta=!paleta;
            if (posY > (ALTOF*5)){
                posY -= salto;
            }
            break;
        case GLUT_KEY_LEFT: // Home (flecha izquierda) => mover deadpool hacia la izquierda
            paleta=!paleta;
            if (posX > 5){
                posX -= salto;
            }
            break;
        case GLUT_KEY_RIGHT: // End (flecha derecha) => mover deadpool hacia la derecha
            paleta=!paleta;
            if (posX < 640-(ANCHOF*5)){
                posX += salto;
            }
            break;
        default:
            break;
    }
    glutPostRedisplay(); // Redibuja la ventana
}

void dibuja(void){ // función de dibujo
    glClear(GL_COLOR_BUFFER_BIT); // borra la pantalla

    int tam=5;
    glPointSize(tam);
    glBegin(GL_POINTS);
    for (int i = 0; i < ALTOF; i++){
        for (int j = 0; j < ANCHOF; j++){
            glColor3ubv(paleta? paleta1[deadpool[i][j]]: paleta2[deadpool[i][j]]);
            glVertex2i(posX+ j * tam, posY - i * tam);
        }
    }
    glEnd();

    glFlush(); // enviar los comandos a la tarjeta gráfica
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("P 2_3");
    glutDisplayFunc(dibuja); 
    glutSpecialFunc(pageUp_Down); // función de teclado especial
    glutReshapeFunc(ajusta); // función de ajuste de ventana
    glutMainLoop(); // Bucle de eventos
    return 0;
}