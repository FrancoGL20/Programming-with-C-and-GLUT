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
GLUquadricObj *cilindro;
GLfloat giray = 90;

void aspas(void) {
    cilindro = gluNewQuadric();
    glRotatef(giray, 0.0, 1.0, 0.0);
    glColor3f(.8, .2, 0);
    glPushMatrix(); // palo
        glTranslatef(1.3, -3, 0);
        glScalef(2, 12, 2);
        glutSolidCube(1);
    glPopMatrix();
    glColor3f(1, 1, .9); // centro
    glutSolidSphere(.6, 10, 10);
    glColor3f(.1, .1, .9); // aspas
    gluQuadricDrawStyle(cilindro, GLU_FILL);
    glPushMatrix();
        glRotatef(45, 1, 0, 0);
        glPushMatrix(); // abajo-der
            glScalef(.15, 1, 1);
            gluCylinder(cilindro, .25, 2, 7, 4, 15);
        glPopMatrix();
        glPushMatrix(); // arriba-iqz
            glTranslatef(0, 0, -7);
            glScalef(.15, 1, 1);
            gluCylinder(cilindro, 2, .25, 7, 4, 15);
        glPopMatrix();
        glColor3f(.9, 0, .9);
        glPushMatrix(); // arriba-der
            glRotatef(90, 1, 0, 0);
            glTranslatef(0, 0, -7);
            glScalef(.15, 1, 1);
            gluCylinder(cilindro, 2, .25, 7, 4, 15);
        glPopMatrix();
        glPushMatrix(); // abajo-izq
            glRotatef(90, 1, 0, 0);
            glScalef(.15, 1, 1);
            gluCylinder(cilindro, .25, 2, 7, 4, 15);
        glPopMatrix();
    glPopMatrix();
}

void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushAttrib(GL_ALL_ATTRIB_BITS); // Guarda el estado de OpenGL para evitar que se modifique por accidente en la llamada a aspas()
        glPushMatrix();
            aspas();
        glPopMatrix();
    glPopAttrib();
    glutSwapBuffers();
}

void teclado(unsigned char key, int x, int y) {
    switch (key) {
    case 27:
        exit(0);
    case 'y':
        giray -= 15;
        break;
        glDisable(GL_LIGHTING);
        glDisable(GL_COLOR_MATERIAL);
        break;
    case '2': // Iluminado grises
        glEnable(GL_LIGHTING);
        glDisable(GL_COLOR_MATERIAL);
        break;
    case '3': // Iluminado a color
        glEnable(GL_LIGHTING);
        glEnable(GL_COLOR_MATERIAL);
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void ajusta(int ancho, int alto) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char **argv) {
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutInit(&argc, argv);
    glutCreateWindow("Rehilete");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
    glutMainLoop();
    return 0;
}