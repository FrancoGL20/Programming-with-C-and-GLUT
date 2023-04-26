#include <GL/glut.h>

#define ALTO 15
#define ANCHO 13

GLubyte paleta1[6][3] = {{0, 255, 255}, {255, 255, 0}, {255, 128, 0}, {0, 255, 0}, {0, 128, 64}, {0, 0, 0}};
GLubyte girasol[ALTO][ANCHO] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
                                {0, 0, 0, 1, 2, 2, 2, 2, 2, 1, 0, 0, 0},
                                {0, 0, 1, 2, 2, 5, 2, 5, 2, 2, 1, 0, 0},
                                {0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0},
                                {0, 1, 2, 2, 5, 2, 2, 2, 5, 2, 2, 1, 0},
                                {0, 0, 1, 2, 2, 5, 5, 5, 2, 2, 1, 0, 0},
                                {0, 0, 0, 1, 2, 2, 2, 2, 2, 1, 0, 0, 0},
                                {0, 0, 0, 0, 1, 1, 3, 1, 1, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0},
                                {0, 0, 4, 4, 0, 0, 3, 0, 4, 4, 4, 0, 0},
                                {0, 0, 0, 4, 4, 4, 3, 4, 4, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 4, 3, 4, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0}};
                            
void ajusta(int ancho, int alto) {
    glClearColor(1.0, 1.0, 1.0, 0.0); // color de background blanco
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}
void dibuja(void) {
    int tam = 20; // tamaño del punto
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(tam);
    glBegin(GL_POINTS);
    for (int i = 0; i < ALTO; i++)
        for (int j = 0; j < ANCHO; j++) {
            glColor3ubv(paleta1[girasol[i][j]]);
            glVertex2i(190 + j * tam, 390 - i * tam);
        }
    glEnd();
    glFlush();
}
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Girasol con puntos");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutMainLoop();
    return 0;
}