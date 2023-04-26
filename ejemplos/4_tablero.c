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
#include <string.h>

void dibujaTorre(int x, int y) {
    int torre[][2] = {
        {8, 4}, {52, 4}, {52, 12}, {8, 12}, // base
        {16, 12},
        {44, 12},
        {36, 48},
        {24, 48}, // pedestal
        {10, 48},
        {50, 48},
        {56, 60},
        {4, 60}, // base2
        {4, 60},
        {16, 60},
        {16, 68},
        {4, 68}, // almena1
        {24, 60},
        {36, 60},
        {36, 68},
        {24, 68}, // almena2
        {44, 60},
        {56, 60},
        {56, 68},
        {44, 68} // almena3
    };
    glBegin(GL_QUADS);
    for (int i = 0; i < 24; i++)
        glVertex2i(torre[i][0] + x, torre[i][1] + y);
    glEnd();
}

void dibujaTexto(void *tipo, char *s) {
    for (int i = 0; i < strlen(s); i++)
        glutBitmapCharacter(tipo, s[i]);
}

void ajusta(int ancho, int alto) {
    glClearColor(0.0, .75, 0.75, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

void dibuja(void) {
    GLboolean colorBlanco = GL_TRUE;
    float blanco[] = {1., 1., 1.};
    float negro[] = {0., 0., 0.};
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 120; i < (120 + 8 * 50); i += 50) {
        colorBlanco = !colorBlanco;
        for (int j = 40; j < (40 + 8 * 50); j += 50) {
            glColor3fv(colorBlanco ? blanco : negro);
            glRecti(i, j, i + 50, j + 50);
            colorBlanco = !colorBlanco;
        }
    }
    glColor3fv(negro);
    glRasterPos2i(15, 260);
    dibujaTexto(GLUT_BITMAP_HELVETICA_18, "NEGRAS");
    dibujaTorre(20, 175);
    glColor3fv(blanco);
    glRasterPos2i(540, 260);
    dibujaTexto(GLUT_BITMAP_HELVETICA_18, "BLANCAS");
    dibujaTorre(550, 175);
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Tablero Ajedrez");
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutMainLoop();
    return 0;
}