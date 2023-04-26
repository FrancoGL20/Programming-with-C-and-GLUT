#include <GL/glut.h>

void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
        glTranslatef(0, 0, -4);

        glColor3f(1.0, 0.7, 0.0); // aureola
        glPushMatrix();
            glTranslatef(0, .8, 0);
            glRotatef(90, 1, 0, 0);
            glutSolidTorus(0.08, 0.7, 20, 20);
        glPopMatrix();

        glColor3f(0.8, 0.5, 0.5); // cara
        glPushMatrix();
            glScalef(.9, .75, .9);
            glutSolidSphere(1.0, 40, 40);
        glPopMatrix();

        glColor3f(0.0, 0.0, 0.0); // ojos
        glPushMatrix(); // ojo izquierdo
            glTranslatef(-.25, .2, .85);
            glutSolidSphere(.1, 8, 8);
        glPopMatrix();
        glPushMatrix(); // ojo derecho
            glTranslatef(.25, .2, .85);
            glutSolidSphere(.1, 8, 8);
        glPopMatrix();

        glColor3f(1.0, 0.0, 0.0); // boca
        glPushMatrix();
            glTranslatef(0, 0, .8);
            glLineWidth(3);
            glBegin(GL_LINE_STRIP);
                glVertex2f(-0.3, -0.1);
                glVertex2f(-0.2, -0.3);
                glVertex2f(0.2, -0.3);
                glVertex2f(0.3, -0.1);
            glEnd();
        glPopMatrix();

    glPopMatrix();

    glFlush();
}
void ajusta(int ancho, int alto) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)ancho / alto, 3.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
int main(int argc, char **argv) {
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(480, 480);
    glutInit(&argc, argv);
    glutCreateWindow("Angel");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutMainLoop();
    return 0;
}