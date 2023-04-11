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
GLboolean malla = GL_FALSE, ejes = GL_FALSE;
GLfloat girax = 45, giray = -30, zoom = 0;
int rotar1=0;
GLboolean animando = GL_FALSE;
GLboolean armando = GL_TRUE;
int angulo_maximo=90;

// Rotacion XY y Zoom
void mover(void) {
    glTranslated(0, 0, zoom);
    glRotated(giray, 0.0, 1.0, 0.0);
    glRotated(girax, 1.0, 0.0, 0.0);
}

// Crear malla
void creaMalla(int long_eje) {
    glColor3f(1.0, 0.0, 0.0);
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
    // Borra la pantalla y el Z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float x=0, z=0;
    int lado=3;

    glPushMatrix();

        // Vista movible
        mover();
        if (malla)
            creaMalla(10);
        if (ejes)
            creaEjes();

        // Base de cubo
        glColor3f(0.0, 0.0, 1.0); // Color azul
        glBegin(GL_POLYGON);
            glVertex3f(x+lado,0,z+lado);
            glVertex3f(x+lado,0,z-lado);
            glVertex3f(x-lado,0,z-lado);
            glVertex3f(x-lado,0,z+lado);
        glEnd();

        // Cara trasera del cubo
        glPushMatrix();
            glTranslated(0, 0, -3);
            glRotated(rotar1, 1, 0, 0);
            glTranslated(0, 0, -3);
            glColor3f(1.0, 0.0, 1.0); // Color morado
            glBegin(GL_POLYGON);
                glVertex3f(x+lado,0,z+lado);
                glVertex3f(x+lado,0,z-lado);
                glVertex3f(x-lado,0,z-lado);
                glVertex3f(x-lado,0,z+lado);
            glEnd();
        glPopMatrix();

        // Cara izquierda del cubo
        glPushMatrix();
            glTranslated(3, 0, 0);
            glRotated(rotar1, 0, 0, 1);
            glTranslated(3, 0, 0);
            glColor3f(1.0, 0.0, 0.0); // Color rojo
            glBegin(GL_POLYGON);
                glVertex3f(x+lado,0,z+lado);
                glVertex3f(x+lado,0,z-lado);
                glVertex3f(x-lado,0,z-lado);
                glVertex3f(x-lado,0,z+lado);
            glEnd();
        glPopMatrix();

        // Cara derecha del cubo
        glPushMatrix();
            glTranslated(-3, 0, 0);
            glRotated(-rotar1, 0, 0, 1);
            glTranslated(-3, 0, 0);
            glColor3f(0.0, 1.0, 0.0); // Color verde
            glBegin(GL_POLYGON);
                glVertex3f(x+lado,0,z+lado);
                glVertex3f(x+lado,0,z-lado);
                glVertex3f(x-lado,0,z-lado);
                glVertex3f(x-lado,0,z+lado);
            glEnd();
        glPopMatrix();

        // Caras de enfrente y superior del cubo
        glPushMatrix();
            glTranslated(0, 0, 3);
            glRotated(-rotar1, 1, 0, 0);
            glTranslated(0, 0, 3);

            // Cara de enfrente del cubo
            glColor3f(1.0, 1.0, 0.0); // Color amarillo
            glBegin(GL_POLYGON);
                glVertex3f(x+lado,0,z+lado);
                glVertex3f(x+lado,0,z-lado);
                glVertex3f(x-lado,0,z-lado);
                glVertex3f(x-lado,0,z+lado);
            glEnd();

            // Cara superior del cubo
            glPushMatrix();
                glTranslated(0, 0, 3);
                glRotated(-rotar1, 1, 0, 0);
                glTranslated(0, 0, 3);
                glColor3f(0.0, 1.0, 1.0); // Color celeste
                glBegin(GL_POLYGON);
                    glVertex3f(x+lado,0,z+lado);
                    glVertex3f(x+lado,0,z-lado);
                    glVertex3f(x-lado,0,z-lado);
                    glVertex3f(x-lado,0,z+lado);
                glEnd();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    // Intercambia los buffers
    glutSwapBuffers();
}

// Funcion para animar el cubo
void animaT(int v) {
    if (animando==GL_TRUE){
        if (armando==GL_TRUE){
            if(rotar1<angulo_maximo){
                rotar1+=1;
            }else{
                animando=GL_FALSE;
                armando=GL_FALSE;
            }
        }else{
            if(rotar1>0){
                rotar1-=1;
            }else{
                animando=GL_FALSE;
                armando=GL_TRUE;
            }
        }
    }
    glutTimerFunc(50, animaT, 0); 
    glutPostRedisplay();
}

// Funciones con Teclas Normales
void teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
            break;
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

// Función para el ratón
void raton(int boton, int estado, int x, int y) {
    if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
        animando = !animando;
    }
    glutPostRedisplay();
}

// Ajustar la ventana, ancho y alto son el tamaño de la ventana y se llama a esta función cuando se cambia el tamaño de la ventana
void ajusta(int anchoA, int altoA) {
    glClearColor(1.0, 1.0, 1.0, 0.0); // color de fondo
    glEnable(GL_DEPTH_TEST); // activa el Z-buffer

    glMatrixMode(GL_MODELVIEW); // matriz de modelado
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-15, 15, -15, 15, -15, 15);
}

int main(int argc, char **argv) {
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800,600); // relación de aspecto 800x600 (4:3)
    glutInit(&argc, argv);
    glutCreateWindow("T4.1: Cubo");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(rotar);
    glutMouseFunc(raton);
    glutTimerFunc(0, animaT, 0);
    glutMainLoop();
    return 0;
}
