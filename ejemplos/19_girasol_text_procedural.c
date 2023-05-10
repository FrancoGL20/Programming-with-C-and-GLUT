#include <GL/glut.h>
#include "../files/girasol.h"
#define anchoTextura 16
#define altoTextura 16
GLubyte imagen[altoTextura][anchoTextura][3];
void creaTexturas(void) {
    for (int i = 0; i < altoTextura; i++)
        for (int j = 0; j < anchoTextura; j++) {
            imagen[i][j][0] = (i < ALTO && j < ANCHO) ? paleta1[girasol[i][j]][0] : paleta1[0][0];
            imagen[i][j][1] = paleta1[(i < ALTO && j < ANCHO) ? girasol[i][j] : 0][1];
            imagen[i][j][2] = paleta1[(i < ALTO && j < ANCHO) ? girasol[i][j] : 0][2];
        }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, anchoTextura, altoTextura,
                0, GL_RGB, GL_UNSIGNED_BYTE, imagen);
}
void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS); 
        // Rectangulo superior izquierdo
        glTexCoord2f(0.0, 0.0);
        glVertex2f(-4.0, 0.0);
        glTexCoord2f(1.0, 0.0);
        glVertex2f(-2.0, 0.0);
        glTexCoord2f(1.0, 1.0);
        glVertex2f(-2.0, 4.0);
        glTexCoord2f(0.0, 1.0);
        glVertex2f(-4.0, 4.0);

        // Cuadrado
        glTexCoord2f(0.0, 0.0);
        glVertex2f(4.0, 4.0);
        glTexCoord2f(0.0, 1.0);
        glVertex2f(4.0, 2.0);
        glTexCoord2f(1.0, 1.0);
        glVertex2f(2.0, 2.0);
        glTexCoord2f(1.0, 0.0);
        glVertex2f(2.0, 4.0);

        // Rectángulo medio derecho
        glTexCoord2f(0.0, 0.0);
        glVertex2f(4.0, -0.5);
        glTexCoord2f(0.0, 1.0);
        glVertex2f(0.0, -0.5);
        glTexCoord2f(1.0, 1.0);
        glVertex2f(0.0, 1.5);
        glTexCoord2f(1.0, 0.0);
        glVertex2f(4.0, 1.5);

        // Rectángulo inferior
        glTexCoord2f(0.0, 0.0);
        glVertex2f(4.0, -1.0);
        glTexCoord2f(0.0, 2.0);
        glVertex2f(4.0, -4.0);
        glTexCoord2f(1.0, 2.0);
        glVertex2f(-4.0, -4.0);
        glTexCoord2f(1.0, 0.0);
        glVertex2f(-4.0, -1.0);
    glEnd();
    glFlush();
}
void ajusta(int w, int h) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-4.5, 4.5, -4.5, 4.5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glEnable(GL_TEXTURE_2D);
}
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Textura procedural");
    creaTexturas();
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutMainLoop();
    return 0;
}