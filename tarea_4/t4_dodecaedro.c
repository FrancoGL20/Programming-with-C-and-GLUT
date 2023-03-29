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
GLfloat girax = 45, giray = -15, zoom = 0;
float rotar1=0;
GLboolean animando = GL_FALSE;
GLboolean armando = GL_TRUE;
float angulo_maximo=63.5;

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

// Dibujar pentagono en y=0
int pentagono(void) {
    glBegin(GL_POLYGON);
        glVertex3f(0.0, 0.0, 1.0);
        glVertex3f(0.9511, 0.0, 0.3090);
        glVertex3f(0.5878, 0.0, -0.8090);
        glVertex3f(-0.5878, 0.0, -0.8090);
        glVertex3f(-0.9511, 0.0, 0.3090);
    glEnd();
}

void dibuja(void) {
    // Borra la pantalla y el Z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Calculo de lado
    float lado=sqrt(pow(0.9511, 2) + pow(0.3090-1, 2));
    // Calculo de apotema
    float apotema = lado / (2 * tan(36 * 3.14159265359 / 180));

    glPushMatrix();

        // Vista movible
        mover();
        if (malla)
            creaMalla(10);
        if (ejes)
            creaEjes();

        // Base del dodecaedro
        glColor3f(0.0, 0.0, 0.0);
        pentagono();

        // Cara 1
        glPushMatrix();
            glRotatef(36, 0.0, 1.0, 0.0);
            glTranslatef(0.0, 0.0, apotema);
            glRotatef(-rotar1, 1.0, 0.0, 0.0);
            glTranslatef(0.0, 0.0, apotema);
            glColor3ub(181, 255, 233); // celeste
            pentagono();
        glPopMatrix();

        // Cara 2
        glPushMatrix();
            glRotatef(36+(72*1), 0.0, 1.0, 0.0);
            glTranslatef(0.0, 0.0, apotema);
            glRotatef(-rotar1, 1.0, 0.0, 0.0);
            glTranslatef(0.0, 0.0, apotema);
            glColor3ub(197, 224, 217); // verde
            pentagono();
        glPopMatrix();

        // Cara 3
        glPushMatrix();
            glRotatef(36+(72*2), 0.0, 1.0, 0.0);
            glTranslatef(0.0, 0.0, apotema);
            glRotatef(-rotar1, 1.0, 0.0, 0.0);
            glTranslatef(0.0, 0.0, apotema);
            glColor3ub(201, 201, 201); // gris
            pentagono();
        glPopMatrix();

        // Cara 4
        glPushMatrix();
            glRotatef(36+(72*3), 0.0, 1.0, 0.0);
            glTranslatef(0.0, 0.0, apotema);
            glRotatef(-rotar1, 1.0, 0.0, 0.0);
            glTranslatef(0.0, 0.0, apotema);
            glColor3ub(206, 171, 177); // rosa
            pentagono();
        glPopMatrix();

        // Cara 5 y union a las otras caras
        glPushMatrix();

            // Cara 5
            glRotatef(36+(72*4), 0.0, 1.0, 0.0);
            glTranslatef(0.0, 0.0, apotema);
            glRotatef(-rotar1, 1.0, 0.0, 0.0);
            glTranslatef(0.0, 0.0, apotema);
            glColor3ub(68, 69, 69); // gris
            pentagono();

            // Cara union a las otras caras
            glPushMatrix();
                glRotatef(36+(72*5), 0.0, 1.0, 0.0);
                glTranslatef(0.0, 0.0, apotema);
                glRotatef(-rotar1, 1.0, 0.0, 0.0);
                glTranslatef(0.0, 0.0, apotema);
                glColor3ub(206, 171, 177); // rosa
                pentagono();

                // Cara base de las otras caras
                glPushMatrix();
                    glRotatef(36+(72*4), 0.0, 1.0, 0.0);
                    glTranslatef(0.0, 0.0, apotema);
                    glRotatef(-rotar1, 1.0, 0.0, 0.0);
                    glTranslatef(0.0, 0.0, apotema);
                    glColor3f(0.0, 0.0, 0.0);
                    pentagono();

                    // Cara 1 de las otras caras
                    glPushMatrix();
                        glRotatef(36+(72*3), 0.0, 1.0, 0.0);
                        glTranslatef(0.0, 0.0, apotema);
                        glRotatef(-rotar1, 1.0, 0.0, 0.0);
                        glTranslatef(0.0, 0.0, apotema);
                        glColor3ub(197, 224, 217); // verde
                        pentagono();
                    glPopMatrix();

                    // Cara 2 de las otras caras
                    glPushMatrix();
                        glRotatef(36+(72*4), 0.0, 1.0, 0.0);
                        glTranslatef(0.0, 0.0, apotema);
                        glRotatef(-rotar1, 1.0, 0.0, 0.0);
                        glTranslatef(0.0, 0.0, apotema);
                        glColor3ub(201, 201, 201); // gris
                        pentagono();
                    glPopMatrix();

                    // Cara 3 de las otras caras
                    glPushMatrix();
                        glRotatef(36+(72*5), 0.0, 1.0, 0.0);
                        glTranslatef(0.0, 0.0, apotema);
                        glRotatef(-rotar1, 1.0, 0.0, 0.0);
                        glTranslatef(0.0, 0.0, apotema);
                        glColor3ub(181, 255, 233); // celeste
                        pentagono();
                    glPopMatrix();

                    // Cara 4 de las otras caras
                    glPushMatrix();
                        glRotatef(36+(72*6), 0.0, 1.0, 0.0);
                        glTranslatef(0.0, 0.0, apotema);
                        glRotatef(-rotar1, 1.0, 0.0, 0.0);
                        glTranslatef(0.0, 0.0, apotema);
                        glColor3ub(68, 69, 69); // gris
                        pentagono();
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    // Intercambia los buffers
    glutSwapBuffers();
}

// Para glutTimerFunc
void animaT(int v) {
    if (animando==GL_TRUE){
        if (armando==GL_TRUE){
            if(rotar1<angulo_maximo){
                rotar1+=0.5;
            }else{
                animando=GL_FALSE;
                armando=GL_FALSE;
            }
        }else{
            if(rotar1>0){
                rotar1-=0.5;
            }else{
                animando=GL_FALSE;
                armando=GL_TRUE;
            }
        }
    }
    glutTimerFunc(25, animaT, 0); 
    glutPostRedisplay();
}

// Funciones con Teclas
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
    glOrtho(-8, 8, -8, 8, -8, 8);
}

int main(int argc, char **argv) {
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800,800);
    glutInit(&argc, argv);
    glutCreateWindow("T4.2: Dodecaedro");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(rotar);
    glutMouseFunc(raton);
    glutTimerFunc(0, animaT, 0);
    glutMainLoop();
    return 0;
}
