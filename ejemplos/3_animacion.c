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
#include <math.h>

float xc = 50, yc = 50, velX = 20, velY = 20, radio = 25;
GLubyte paleta[3][3] = {{0, 0, 0}, {255, 0, 0}, {0, 0, 255}};
enum colores {
    negro,
    rojo,
    azul
};

enum colores col = negro;
GLenum modo = GL_POLYGON; // wireframe o solida

void circulo(float x, float y, int seg) {
    int i;
    glBegin(modo);
    for (i = 0; i <= 360; i += 360 / seg)
        glVertex2i(x + radio * cos(i * M_PI / 180), y + radio * sin(i * M_PI / 180));
    glEnd();
}

void ajusta(int ancho, int alto) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ubv(paleta[col]);
    circulo(xc, yc, 20);
    glutSwapBuffers();
}

void anima(void) {
    if (xc + radio >= 640 || xc - radio <= 0)
        velX = -velX;
    if (yc + radio >= 480 || yc - radio <= 0)
        velY = -velY;
    xc += velX;
    yc += velY;
    glutPostRedisplay();
}

// Para glutTimerFunc
void animaT(int v) {
    if (xc + radio >= 640 || xc - radio <= 0)
        velX = -velX;
    if (yc + radio >= 480 || yc - radio <= 0)
        velY = -velY;
    xc += velX;
    yc += velY;
    glutTimerFunc(300, animaT, 0); 
    glutPostRedisplay();
}

void cambia(int opcion) {
    switch (opcion) {
    case 10:
        modo = GL_POLYGON;
        break;
    case 20:
        modo = GL_LINE_LOOP;
        break;
    case 100:
        exit(0);
    }
    glutPostRedisplay();
}

void pinta(unsigned char tecla, int x, int y) {
    switch (tecla) {
    case 'n':
        col = negro;
        break;
    case 'r':
        col = rojo;
        break;
    case 'a':
        col = azul;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Pelotita");
    glutReshapeFunc(ajusta);
    // glutIdleFunc(anima);
    glutTimerFunc(200, animaT, 0);
    glutDisplayFunc(dibuja);
    glutKeyboardFunc(pinta);
    glutCreateMenu(cambia);
    glutAddMenuEntry("Solido", 10);
    glutAddMenuEntry("Wireframe", 20);
    glutAddMenuEntry("Salir", 100);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
    return 0;
}