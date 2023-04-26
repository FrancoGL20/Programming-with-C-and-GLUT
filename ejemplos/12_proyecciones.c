#include <GL/glut.h>

GLUquadricObj *cilindro;
GLfloat girax = 0, giray = 0, zoom = 0;
GLboolean malla = GL_FALSE, ejes = GL_TRUE;
//   Rotacion XY y Zoom
void mover(void) {
    glTranslated(0, 0, zoom);
    glRotated(giray, 0.0, 1.0, 0.0);
    glRotated(girax, 1.0, 0.0, 0.0);
}
//  Malla y Ejes
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
    cilindro = gluNewQuadric();
    glPushMatrix();
        mover();
        if (malla)
            creaMalla(10);
        glColor3f(0.5, 0.25, 0.75);
        gluQuadricDrawStyle(cilindro, GLU_LINE);
        gluCylinder(cilindro, 1, 1, 9, 20, 20);
        if (ejes)
            creaEjes();
    glPopMatrix();
    glutSwapBuffers();
}
// Funciones con Teclas
void teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
        case '+': // aumenta el zoom
            zoom++;
            break;
        case '-': // disminuye el zoom
            zoom--;
            break;
        case 'm': // activa/desactiva la malla
            malla = !malla;
            break;
        case 'e': // activa/desactiva los ejes
            ejes = !ejes;
            break;
        case 'p': // proyeccion perspectiva
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            // gluPerspective(angulo, aspecto, cerca, lejos)
            gluPerspective(45, 1, 10, 100);
            zoom = -40;
            break;
        case 'o': // proyeccion ortogonal
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-15, 15, -15, 15, -30, 30);
            zoom = 0;
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
    glMatrixMode(GL_MODELVIEW);       // matriz de modelado
    glLoadIdentity();                 // matriz identidad
    glEnable(GL_DEPTH_TEST);          // activa el Z-buffer
}
int main(int argc, char **argv) {
    // mode: RGB, doble buffer, Z-buffer
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500); // tamaño de la ventana de 500x500
    glutInit(&argc, argv);
    glutCreateWindow("Cilindro");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(rotar);
    glutMainLoop();
    return 0;
}
