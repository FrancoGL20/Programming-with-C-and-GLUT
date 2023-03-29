#include <stdlib.h>
#include <GL/glut.h>

int muslo = 0, pantorrilla = 0, pie = 0;

void dibuja(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

        glRotatef((GLfloat)muslo, 0.0, 0.0, 1.0);
        glPushMatrix();
            glTranslatef(0.0, 1.6, 0.0);
            glScalef(0.6, 2, 0.5);
            glColor3f(1, 0, 1);
            glutSolidCube(1.0); // muslo
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0, 0.3, 0.0);
            glColor3f(.7, .7, .7);
            glutSolidSphere(0.29, 15, 15); // rodilla
        glPopMatrix();

        glPushMatrix();
            glRotatef(-(GLfloat)pantorrilla * 2, 0.0, 0.0, 1.0);
            
            glPushMatrix();
                glTranslatef(0.0, -1, 0.0);
                glScalef(0.6, 2, 0.5);
                glColor3f(0, 0, 1); // azul
                glutSolidCube(1.0); // pantorrilla
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0.0, -2.3, 0.0);
                glColor3f(.7, .7, .7); // gris
                glutSolidSphere(0.28, 15, 15); // talon
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0, -2.8, 0.0);
                glRotatef((GLfloat)pie, 0.0, 0.0, 1.0);
                glTranslatef(0, 2.8, 0.0);
                glPushMatrix();
                    glTranslatef(0.25, -2.8, 0.0);
                    glScalef(1, 0.35, 0.7);
                    glColor3f(.5, 0, .8); // morado
                    glutSolidCube(1.0); // pie
                glPopMatrix();
            glPopMatrix();

        glPopMatrix();
        
    glPopMatrix();
    glutSwapBuffers();
}

void teclado(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
    case 'M':
        muslo = (muslo + 5) % 360;
        break;
    case 'm':
        muslo = (muslo - 5) % 360;
        break;
    case 'A':
        if (pantorrilla >= 75)
            pantorrilla = 75;
        else
            pantorrilla += 5;
        break;
    case 'a':
        if (pantorrilla <= -5)
            pantorrilla = -5;
        else
            pantorrilla -= 5;
        break;

        if (pie >= 30)
            pie = 30;
        else
            pie += 5;
        break;
    case 'p':
        if (pie <= -30)
            pie = -30;
        else
            pie -= 5;
    }
    glutPostRedisplay();
}
void ajusta(int ancho, int alto)
{
    glClearColor(0., 0., 0., 0.);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4, 4, -4, 4, -4, 4);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Pierna");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
    glutMainLoop();
    return 0;
}