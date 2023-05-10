#include <GL/glut.h>
#include "../files/deadpool.h"                 //archivo .h
#define anchoTextura 32                       // ancho potencia de 2
#define altoTextura 32                        // alto potencia de 2
GLubyte imagen[altoTextura][anchoTextura][3]; // textura procedimental en formato RGB

// Función que crea la textura procedimental
void creaTextura(void) {
    for (int i = 0; i < altoTextura; i++) {
        for (int j = 0; j < anchoTextura; j++) {
            imagen[i][j][0] = (i < ALTO && j < ANCHO) ? paleta[deadpool[i][j]][0] : paleta[0][0];
            imagen[i][j][1] = paleta[(i < ALTO && j < ANCHO) ? deadpool[i][j] : 0][1];
            imagen[i][j][2] = paleta[(i < ALTO && j < ANCHO) ? deadpool[i][j] : 0][2];
        }
    }
    // GL_NEAREST: elige el color de la textura más cercano al pixel, 
    // GL_LINEAR: mezcla los colores de los 4 pixeles más cercanos
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // Cuando se hace más grande un objeto, se usa GL_NEAREST
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // Cuando se hace más pequeño un objeto, se usa GL_NEAREST

    // GL_REPLACE: reemplaza el color del objeto por el de la textura, 
    // GL_MODULATE: mezcla los colores del objeto y de la textura, 
    // GL_DECAL: mezcla los colores del objeto y de la textura, pero no se mezcla el alpha, GL_BLEND: mezcla los colores del objeto y de la textura, pero se mezcla el alpha, 
    // GL_ADD: suma los colores del objeto y de la textura, 
    // GL_COMBINE: combina los colores del objeto y de la textura
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // Selecciona el modo de mezcla de colores

    // GL_CLAMP: se repite el color del borde de la textura,
    // GL_REPEAT: se repite la textura como un mosaico
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); // Modo de repetición de la textura en el eje X
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); // Modo de repetición de la textura en el eje Y

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, anchoTextura, altoTextura,
                0, GL_RGB, GL_UNSIGNED_BYTE, imagen); // Guarda la textura en la memoria de video (VRAM)
}

void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        // Arriba a la derecha
        glTexCoord2f(0.0, 0.0);
        glVertex2f(4.0, 4.0);

        // Abajo a la derecha
        glTexCoord2f(0.0, 1.0);
        glVertex2f(4.0, -4.0);

        // Abajo a la izquierda
        glTexCoord2f(1.0, 1.0);
        glVertex2f(-4.0, -4.0);

        // Arriba a la izquierda
        glTexCoord2f(1.0, 0.0);
        glVertex2f(-4.0, 4.0);
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
