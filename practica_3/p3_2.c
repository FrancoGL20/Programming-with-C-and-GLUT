// Cambio de color de dibujo con pixeles cada 600 ms

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "p3_deadpool.h"

GLboolean paleta=GL_TRUE;
int posX=(640/2)-((ANCHOF/2)*5), posY=(480/2)+((ALTOF/2)*5);

// Para glutTimerFunc
void animaT(int v) {
    paleta=!paleta;
    glutTimerFunc(600, animaT, 0); 
    glutPostRedisplay();
}

// Función que se ejecuta para redimensionar e inicializar la ventana
void ajusta(int ancho, int alto){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
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
    glutReshapeFunc(ajusta); // función de ajuste de ventana
    glutDisplayFunc(dibuja); 
    glutTimerFunc(600, animaT, 0); // Para animar con un timer

    glutMainLoop(); // Bucle de eventos
    return 0;
}