#include <GL/glut.h>
#include <stdlib.h>
GLfloat puntos[4][3] = {{-3., -3., 0.}, {-3, 3.0, 0.0}, {0.5, 3.0, 0.0}, {0.5, -3.0, 0.0}};
void dibuja(void)
{
    int i;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    glColor4f(1.0, 0.0, 0.0, 1.0);
    for (i = 0; i < 4; i++)
        glVertex3fv(puntos[i]);
    glColor4f(0.0, 1.0, 0.0, 0.25);
    for (i = 0; i < 4; i++)
        glVertex3f(-puntos[i][0], -puntos[i][1], -puntos[i][2]);
    glEnd();
    glFlush();
}
void ajusta(int ancho, int alto)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-5.0, 5.0, -5.0, 5.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_BLEND);
}
void teclado(unsigned char tecla, int x, int y)
{
    switch (tecla)
    {
    case 27:
        exit(0);
    case 'o': // Equivale a glDisable(GL_BLEND)
        glBlendFunc(GL_ONE, GL_ZERO);
        break;
    case 't':
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    glutPostRedisplay();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Transparencia");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
    glutMainLoop();
    return 0;
}