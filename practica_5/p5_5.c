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
#include <stdio.h>
#include <math.h>

// Variables globales
int alto = 600, ancho = 800;

void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ----------------- Líneas divisorias ----------------- //
    glViewport(0, 0, ancho, alto); // tamaño y posición de la ventana
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, -1, 1); // relación de aspecto
    glColor3f(0.5, 0.3, 0.0);
    glBegin(GL_LINES);
        glVertex2f(0.5, 0.0);
        glVertex2f(0.5, 1.0);
        glVertex2f(1.0, 0.5);
        glVertex2f(0.0, 0.5);
    glEnd();

    // -------------------- Vista Superior ------------------ //
    glViewport(0,alto/2,ancho/2,alto/2); // x, y, ancho, alto
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-16,16,-12,12,-20,20);
    gluLookAt(0,10,0,   0,0,0,   0,0,-1);
    glPushMatrix();
        glColor3f(0.0, 0.5, 0.0); // verde
        glutWireTeapot(8);
    glPopMatrix();

    // --------------------- Vista Frontal ------------------ //
    glViewport(ancho/2,alto/2,ancho/2,alto/2); // x, y, ancho, alto
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1.5, 1, 30); // ángulo de visión, relación de aspecto, plano cercano, plano lejano
    gluLookAt(5,6,20,  2,0,0,  0,1,0);
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.5); // azul
        glRotated(-20, 0, 1, 0);
        glutWireTeapot(8);
    glPopMatrix();

    // -------------------- Vista Lateral ------------------- //
    glViewport(0,0,ancho/2,alto/2); // x, y, ancho, alto
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-16,16,-12,12,-20,20);
    gluLookAt(0,0,10,   0,0,0,   0,1,0);
    glPushMatrix();
        glColor3f(0.5, 0.0, 0.0); // rojo
        glutWireTeapot(8);
    glPopMatrix();

    // ------------------- Vista de Frente ------------------ //
    glViewport(ancho/2,0,ancho/2,alto/2); // x, y, ancho, alto
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-16,16,-12,12,-20,20);
    gluLookAt(10,0,0,   0,0,0,   0,1,0);
    glPushMatrix();
        glColor3f(0.5, 0.5, 0.0); // amarillo
        glutWireTeapot(8);
    glPopMatrix();

    // --------------- Intercambio de buffers --------------- //
    glutSwapBuffers();
}

// Funciones con Teclas
void teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
        default:
            break;
    }
    glutPostRedisplay();
}

// Ajustar la ventana, ancho y alto son el tamaño de la ventana y se llama a esta función cuando se cambia el tamaño de la ventana
void ajusta(int anchoA, int altoA) {
    glClearColor(1.0, 1.0, 1.0, 0.0); // color de fondo
    glEnable(GL_DEPTH_TEST);          // activa el Z-buffer
    glMatrixMode(GL_MODELVIEW);     // matriz de modelado
    glLoadIdentity();
    ancho = anchoA;
    alto = altoA;
}

int main(int argc, char **argv) {
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800,600); // relación de aspecto 800x600 (4:3)
    glutInit(&argc, argv);
    glutCreateWindow("P5.5");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
    glutMainLoop();
    return 0;
}
