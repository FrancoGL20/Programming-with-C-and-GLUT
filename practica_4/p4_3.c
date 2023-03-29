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

// Variables globales
enum color{rojo,amarillo,verde};
enum color col=rojo;
int frecuencia[][2]={{2,3000},{3,250},{2,250},{3,250},{2,250},{1,700},{0,4000}}; // color, tiempo en ms
int nFrecuencias=7;
int iFrecuencia=0;

// Función para ajustar la ventana
void ajusta(int ancho, int alto) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,640,0,480,-200,200);
}

// Función para dibujar
void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
        glTranslatef(320, 240, 0);

        // Base del semaforo
        glColor3ub(255, 165, 0);
        glPushMatrix();
            glScalef(180, 420, 1);
            glutSolidCube(1);
        glPopMatrix();

        // Linterna roja
        glColor3ubv(col==rojo? (GLubyte[]){255,0,0} : (GLubyte[]){128,128,128});
        glPushMatrix();
            glTranslatef(0, 130, 0);
            glScalef(55, 55, 1);
            glutSolidSphere(1.0, 40, 40);
        glPopMatrix();

        // Linterna amarilla
        glColor3ubv(col==amarillo? (GLubyte[]){255,255,0} : (GLubyte[]){128,128,128});
        glPushMatrix(); // foco yellow
            glScalef(55, 55, 1);
            glutSolidSphere(1.0, 40, 40);
        glPopMatrix();
        
        // Linterna verde
        glColor3ubv(col==verde? (GLubyte[]){0,255,0} : (GLubyte[]){128,128,128});
        glPushMatrix(); // foco green
            glTranslatef(0, -130, 0);
            glScalef(55, 55, 1);
            glutSolidSphere(1.0, 40, 40);
        glPopMatrix();

    glPopMatrix();
    
    glutSwapBuffers();
}

// Función para animar
void anima(int v) {
    col=frecuencia[iFrecuencia][0];
    glutTimerFunc(frecuencia[iFrecuencia][1], anima, 0); 
    iFrecuencia=(iFrecuencia+1)%nFrecuencias;
    glutPostRedisplay();
}

// Función para el teclado
void teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
            break;
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("P 4.3");
    glutReshapeFunc(ajusta);
    glutTimerFunc(1, anima, 0);
    glutDisplayFunc(dibuja);
    glutKeyboardFunc(teclado);
    glutMainLoop();
    return 0;
}