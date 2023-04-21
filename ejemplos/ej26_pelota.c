#include <GL/glut.h>
#define GRAVEDAD -9.8
#define MASA 200  // masa de la pelota
double h = 0.075; // h incrementos de tiempo
double posicion[] = {0, 0, 0};
double velocidad[] = {0, 0, 0};
double fzaX = .02;
double fzaZ = -.05;
GLboolean bx = GL_FALSE;
GLboolean by = GL_FALSE;
GLboolean bz = GL_FALSE;

void integraEuler()
{
    // v(t+h)=v(t)+F(t)/m*h
    if (bx)
        velocidad[0] += fzaX * h;
    if (by)
        velocidad[1] += GRAVEDAD / MASA * h;
    if (bz)
        velocidad[2] += fzaZ * h;
    // x(t+h)=x(t) + v(t+h)*h
    posicion[0] += velocidad[0] * h;
    posicion[1] += velocidad[1] * h;
    posicion[2] += velocidad[2] * h;
}

void ajusta(int alto, int ancho)
{
    glClearColor(0.5, 0.5, 0.5, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)alto / ancho, 1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void dibuja(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3ub(0, 0, 0);
    glLineWidth(2);
    glPushMatrix();
        glTranslatef(0, 0, -16);
        glutWireCube(11);
        glColor3ub(0, 0, 255);
        glPushMatrix();
            glTranslated(posicion[0], posicion[1], posicion[2]);
            glutSolidSphere(.4, 20, 20);
        glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();
}
void mueve(void)
{
    integraEuler();
    // colisiones
    if (posicion[0] >= 5 || posicion[0] <= -5)
    { // X
        fzaX = -1 * fzaX;
        velocidad[0] = 0;
        posicion[0] = (posicion[0] >= 5) ? 4.8 : -4.8;
    }
    if (posicion[1] >= 5)
    { // Y Arriba
        velocidad[1] = 0;
        posicion[1] = 4.2;
    }
    if (posicion[1] <= -5)
    { // Y Abajo
        velocidad[1] = 0.9;
        posicion[1] = -4.8;
    }
    if (posicion[2] >= 5 || posicion[2] <= -5)
    { // Z
        fzaZ = -1 * fzaZ;
        velocidad[2] = 0;
        posicion[2] = (posicion[2] >= 5) ? 4.8 : -4.8;
    }
    glutPostRedisplay();
}
void teclado(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
    case 'x':
        bx = !bx;
        break;
    case 'y':
        by = !by;
        break;
    case 'z':
        bz = !bz;
    }
}
int main(int argc, char **argv)
{
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Bolita");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
    glutIdleFunc(mueve);
    glutMainLoop();
    return 0;
}