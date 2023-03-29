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
float mov_completo=0;
float ap_pinza=0;
GLboolean girando=GL_FALSE;
int angulo_giro=0;

// Función para manejar el redimensionamiento de la ventana
void ajusta(int ancho, int alto) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10,10,-10,10,10,-10);
    glEnable(GL_DEPTH_TEST);
}

// Función para dibujar la pinza completa
void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        glTranslatef(mov_completo, 0, 0); // movimiento a lo largo del eje x
        glRotatef(angulo_giro, 0, 1, 0); // giro de la pinza

        // cuerpo de la pinza
        glColor3ub(255, 165, 0); // naranja
        glPushMatrix();
            glTranslatef(0, 10, 0);
            glRotatef(90, 1, 0, 0);
            gluCylinder(gluNewQuadric(), 0.5, 0.5, 12, 20, 20);
        glPopMatrix();

        // pinza izquierda
        glColor3ub(128, 128, 128); // gris
        glPushMatrix();
            glTranslatef(0.125, -2, 0);
            glRotatef(ap_pinza, 0, 0, 1);
            glTranslatef(0, -1.5, 0);
            glScalef(0.25,3,0.7);
            glutSolidCube(1);
        glPopMatrix();

        // pinza derecha
        glColor3ub(0, 0, 255); // azul
        glPushMatrix();
            glTranslatef(-0.125, -2, 0);
            glRotatef(-ap_pinza, 0, 0, 1);
            glTranslatef(0, -1.5, 0);
            glScalef(0.25,3,0.7);
            glutSolidCube(1);
        glPopMatrix();

    glPopMatrix();
    
    glutSwapBuffers(); // se intercambian los buffers
}

// Función para manejar las teclas normales del teclado
void teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
            break;
    }
    glutPostRedisplay();
}

// Función para manejar las teclas especiales del teclado
void tecla_especial(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT: // mover la pinza a la izquierda
            if (mov_completo > -9.5){
                mov_completo=mov_completo-0.5;
            }
            break;
        case GLUT_KEY_RIGHT: // mover la pinza a la derecha
            if (mov_completo < 9.5){
                mov_completo=mov_completo+0.5;
            }
            break;
        case GLUT_KEY_F1: // abrir la pinza
            if (ap_pinza > 0){
                ap_pinza=ap_pinza-5;
            }
            break;
        case GLUT_KEY_F2: // cerrar la pinza
            if (ap_pinza < 40){
                ap_pinza=ap_pinza+5;
            }
            break;
        case GLUT_KEY_F5: // iniciar/parar el giro de la pinza
            girando = !girando;
            break;
    }
    glutPostRedisplay();
}

// Función para animar el giro de la pinza
void anima(int valor) {
    // Si la pinza está girando, se incrementa el ángulo de giro
    if (girando) {
        angulo_giro = (angulo_giro + 5);
        if (angulo_giro > 360)
            angulo_giro = 0;
    }
    glutPostRedisplay();
    glutTimerFunc(50, anima, 0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("P 4.4");
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(tecla_especial);
    glutTimerFunc(0, anima, 0);
    glutMainLoop();
    return 0;
}
