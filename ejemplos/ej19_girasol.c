#include <GL/glut.h>
#include "../files/girasol.h"                 //archivo .h
#define anchoTextura 16                       // ancho potencia de 2
#define altoTextura 16                        // alto potencia de 2
GLubyte imagen[altoTextura][anchoTextura][3]; // textura procedimental en formato RGB

// Función que crea la textura procedimental
void creaTextura(void) {
    for (int i = 0; i < altoTextura; i++) {
        for (int j = 0; j < anchoTextura; j++) {
            imagen[i][j][0] = (i < ALTO && j < ANCHO) ? paleta1[girasol[i][j]][0] : paleta1[0][0];
            imagen[i][j][1] = paleta1[(i < ALTO && j < ANCHO) ? girasol[i][j] : 0][1];
            imagen[i][j][2] = paleta1[(i < ALTO && j < ANCHO) ? girasol[i][j] : 0][2];
        }
    }
    // Cuando se hace más grande un objeto, se usa GL_NEAREST
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // Cuando se hace más pequeño un objeto, se usa GL_NEAREST
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    // Guarda la textura en la memoria de video (VRAM)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, anchoTextura, altoTextura,
                0, GL_RGB, GL_UNSIGNED_BYTE, imagen);
}

void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        // Arriba izquierda
        glTexCoord2f(0.25, 0.0);
        glVertex2f(2.0, 4.0);

        // Abajo izquierda
        glTexCoord2f(0.0, 1.0);
        glVertex2f(4.0, -4.0);

        // Abajo derecha
        glTexCoord2f(1.0, 1.0);
        glVertex2f(-4.0, -4.0);

        // Arriba derecha
        glTexCoord2f(0.75, 0.0);
        glVertex2f(-2.0, 4.0);
    glEnd();
    glFlush();
}

void tecla(unsigned char key, int x, int y) {
    if (key == 27)
        exit(0);
}

void ajusta(int w, int h) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-4.5, 4.5, -4.5, 4.5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D); // Habilitar uso texturas
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Ejemplo Textura Procedural");
    creaTextura();
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutKeyboardFunc(tecla);
    glutMainLoop();
    return 0;
}
