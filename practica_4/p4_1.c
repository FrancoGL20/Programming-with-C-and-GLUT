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
#include "p4_1.h"


// Función para ajustar la ventana
void ajusta(int ancho, int alto) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

// Función para manejar la interacción con el mouse
void raton(int boton, int estado, int x, int y) {
    int alto_ventana = 480;
    int px, py;
    if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
        px = x;
        py = alto_ventana - y;
    }
    glutPostRedisplay();
}

// Función para manejar la interacción con las teclas especiales
void tecla_especial(int tecla, int x, int y) {
    switch (tecla) {
    case GLUT_KEY_UP: // tecla flecha arriba
        matriz_escalamiento(1.2, 1.2);
        matrices_multiplicacion(3, 4, 3, Coordenadas, Escalamiento, Coordenadas);
        break;
    case GLUT_KEY_DOWN: // tecla flecha abajo
        matriz_escalamiento(0.8, 0.8);
        matrices_multiplicacion(3, 4, 3, Coordenadas, Escalamiento, Coordenadas);
        break;
    case GLUT_KEY_LEFT: // tecla flecha izquierda
        for (int i = 0; i < 4; i++)
            if (Coordenadas[i][0] != 0)
                Coordenadas[i][0] = -Coordenadas[i][0];
        creaT(205, 0);
        matrices_multiplicacion_vector();
        break;
    case GLUT_KEY_RIGHT: // tecla flecha derecha
        for (int i = 0; i < 4; i++)
            if (Coordenadas[i][1] != 0)
                Coordenadas[i][1] = -Coordenadas[i][1];
        creaT(0, 250);
        matrices_multiplicacion_vector();
        break;
    }
    
    glutPostRedisplay();
}

// Función para manejar la interacción con las teclas normales
void teclado(unsigned char tecla, int x, int y) {
    if (tecla == 27) // Esc =>Salir del programa
        exit(0);      

    glutPostRedisplay();
}

// Función para dibujar
void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; i++)
        glVertex2i(Coordenadas[i][0], Coordenadas[i][1]);
    glEnd();

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("P 4.1");
    creaT(100, 100);
    matrices_multiplicacion_vector();
    glutDisplayFunc(dibuja);
    glutMouseFunc(raton);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(tecla_especial);
    glutReshapeFunc(ajusta);
    glutMainLoop();
    return 0;
}