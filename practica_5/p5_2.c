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
GLUquadricObj *cilindro;
GLfloat girax = 52, giray = 0;
GLboolean malla = GL_FALSE, ejes = GL_FALSE;
int a=2,b=3;
int c=20;
float t=0.2*3.141592653589;
float x,y,z;

// Rotacion XY y Zoom
void mover(void) {
    glRotated(giray, 0.0, 1.0, 0.0);
    glRotated(girax, 1.0, 0.0, 0.0);
}

// Crear malla
void creaMalla(int long_eje) {
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    int i;
    for (i = -long_eje; i <= long_eje; i++) {
        glVertex3f(i, 0, -long_eje);
        glVertex3f(i, 0, long_eje);
        glVertex3f(-long_eje, 0, i);
        glVertex3f(long_eje, 0, i);
    }
    glEnd();
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
        glColor3f(0.25, 1, 0.25); /* eje y */
        glVertex3f(0.0, 11.0, 0.0);
        glVertex3f(-.50, 10.5, 0.0);
        glVertex3f(.50, 10.5, 0.0);
        glColor3f(0.25, 0.25, 1.0); /* eje z */
        glVertex3f(0.0, 0.0, 11.0);
        glVertex3f(-.50, 0.0, 10.5);
        glVertex3f(.50, 0.0, 10.5);
    glEnd();
}

void dibuja(void) {
    // limpiar frame buffer y Z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Dibujar la curva toroidal espiral
    glPushMatrix();
        mover();
        if (malla)
            creaMalla(10);
        if (ejes)
            creaEjes();
        glRotatef(90,1,0,0);
        glScalef(2,2,2);
        // color morado
        glColor3f(0.5, 0.0, 0.5);
        glBegin(GL_LINE_STRIP);
        for (int i=0;i<1000;i++){
            x=(a*sin(c*t)+b)*cos(t);
            y=(a*sin(c*t)+b)*sin(t);
            z=a*cos(c*t);
            glVertex3f(x,y,z);
            t+=0.01;
        }
        glEnd();
    glPopMatrix();

    glutSwapBuffers();
}
// Funciones con Teclas
void teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
        case 'm': // activa/desactiva la malla
            malla = !malla;
            break;
        case 'e': // activa/desactiva los ejes
            ejes = !ejes;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}


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

void ajusta(int ancho, int alto) {
    glClearColor(1.0, 1.0, 1.0, 0.0); // color de fondo
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-15, 15, -15, 15, -30, 30);
    
    glMatrixMode(GL_MODELVIEW);       // matriz de modelado
    glLoadIdentity();                 // matriz identidad
    glEnable(GL_DEPTH_TEST);          // activa el Z-buffer
}

int main(int argc, char **argv) {
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500*1.5, 500); 
    glutInit(&argc, argv);
    glutCreateWindow("P5.2");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(rotar);
    glutMainLoop();
    return 0;
}
