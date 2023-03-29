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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Variables globales
char nombre_luz[20]="Luz Puntual";
GLfloat girax = 0, giray = 0, zoom = 0;
GLboolean ejes = GL_FALSE;

// Rotacion XY y Zoom
void mover(void) {
    glTranslated(0, 0, zoom);
    glRotated(girax, 1.0, 0.0, 0.0);
    glRotated(giray, 0.0, 1.0, 0.0);
}

// Crear ejes
void creaEjes(void) {
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(11.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 11.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 11.0);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex3f(11.0, 0.0, 0.0); /* eje x */
        glVertex3f(10.5, 0.0, -.50);
        glVertex3f(10.5, 0.0, .50);
        glVertex3f(0.0, 11.0, 0.0);
        glVertex3f(-.50, 10.5, 0.0);
        glVertex3f(.50, 10.5, 0.0);
        glVertex3f(0.0, 0.0, 11.0);
        glVertex3f(-.50, 0.0, 10.5);
        glVertex3f(.50, 0.0, 10.5);
    glEnd();
}

// Función de teclas normales
void teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
        case 'e': // activa/desactiva los ejes
            ejes = !ejes;
            break;
        case '1':
            glDisable(GL_BLEND);
            break;
        case '2':
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
            break;
        case '3':
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            break;
        case '4':
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_SRC_COLOR);
            break;
        case '5':
            glEnable(GL_BLEND);
            glBlendFunc(GL_DST_COLOR, GL_SRC_COLOR);
            break;
    }
    glutPostRedisplay();
}

// Funciones con Teclas Especiales
void rotar(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT: // rotacion en el eje Y
            giray -= 15;
            break;
        case GLUT_KEY_RIGHT: // rotacion en el eje Y
            giray += 15;
            break;
        case GLUT_KEY_UP: // rotacion en el eje X
            girax -= 15;
            break;
        case GLUT_KEY_DOWN: // rotacion en el eje X
            girax += 15;
            break;
    }
    glutPostRedisplay();
}

void dibuja(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();
        mover();
        if (ejes) creaEjes();

        // Esfera 1
        glColor4f(1.0, 0.0, 0.0, 1.0);
        glPushMatrix();
            glTranslated(0, 3, 0);
            glutSolidSphere(1, 20, 20);
        glPopMatrix();

        // Esfera 2
        glColor4f(0.0, 0.0, 0.0, 1.0);
        glPushMatrix();
            glutSolidSphere(1, 20, 20);
        glPopMatrix();

        // Cubo
        glColor4f(0.0, 0.0, 1.0, 0.3);
        glPushMatrix();
            glRotated(30, 0, 1, 0);
            glutSolidCube(4);
        glPopMatrix();

    glPopMatrix();
    glPopAttrib();

    // Vacia el buffer de dibujo
    glFlush(); 
}

void ajusta(int ancho, int alto){
    glClearColor(1.0, 1.0, 1.0, 0.0);

    // habilitar la iluminacion
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // habilitar el color de los materiales
    glEnable(GL_COLOR_MATERIAL);

    // habilitar la transparencia
    glEnable(GL_BLEND);

    // habilitar el z-buffer
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -10,10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(20, 20);
    glutInitWindowSize(500, 500);
    glutCreateWindow("p6.3");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(rotar);
    glutMainLoop();
    return 0;
}