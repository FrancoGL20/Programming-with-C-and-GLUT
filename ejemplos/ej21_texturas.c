#include <stdio.h>
#include <GL/glut.h>
#include "tuxtex.h" // Archivo con textura procedural

// Variables globales
GLuint texturas[4]; // Id's de las texturas
GLubyte pixeles[32][32][3]; // Para textura pixeles (tux)
GLubyte proced[64][64][3];  // Para textura procedural (espacio con estrellas)
GLubyte paleta[6][3] = {{230, 50, 50}, {0, 0, 0}, {80, 80, 80}, {255, 125, 0}, {255, 255, 0}, {255, 255, 255}};

// Carga imagen de archivo data y la convierte en textura de OpenGL
void cargaTextura_data(int ancho, int alto, const char *archivo, GLuint *text, int id_textura, GLboolean esfera){
    unsigned char *datos;
    FILE *file = fopen(archivo, "rb");
    if (file == NULL)    {
        printf("archivo no encontrado");
        exit(1);
    }
    datos = (unsigned char *)malloc(ancho * alto * 3); // reservar memoria para los datos
    fread(datos, ancho * alto * 3, 1, file);
    fclose(file);

    glGenTextures(id_textura, text);
    glBindTexture(GL_TEXTURE_2D, *text);
    if (esfera)    {
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, datos);
}

void dibuja(void){
    glClear(GL_COLOR_BUFFER_BIT);

    // Fondo de color rojo
    glDisable(GL_TEXTURE_2D);
    glColor3ubv(paleta[0]);
    glBegin(GL_QUADS); // pared
        glVertex3f(-5.8, -3.8, -0.5);
        glVertex3f(-5.8, 3.8, -0.5);
        glVertex3f(5.8, 3.8, -0.5);
        glVertex3f(5.8, -3.8, -0.5);
    glEnd();

    // Espacio con estrellas
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // Modo de mezcla de texturas
    glBindTexture(GL_TEXTURE_2D, texturas[2]); // espacio
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-2.5, 2.5, 0);

        glTexCoord2f(0.0, 6.0);
        glVertex3f(-2.5, -0.6, 0);

        glTexCoord2f(3.0, 6.0);
        glVertex3f(2.5, -0.6, 0);

        glTexCoord2f(3.0, 0.0);
        glVertex3f(2.5, 2.5, 0);
    glEnd();

    // Marco de los 4 lados
    glBindTexture(GL_TEXTURE_2D, texturas[1]); // marco
    glBegin(GL_QUADS);
        // Superior
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-3., 3., .5);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(3., 3., .5);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(2.5, 2.5, .5);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-2.5, 2.5, .5);
        // a mi izquierda
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-3., 3., .5);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-2.5, 2.5, .5);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(-2.5, -0.5, .5);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(-3., -1., .5);
        // Inferior
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-3., -1., .5);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(3., -1., .5);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(2.5, -0.5, .5);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-2.5, -0.5, .5);
        // a mi derecha
        glTexCoord2f(0.0, 0.0);
        glVertex3f(3., 3., .5);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(2.5, 2.5, .5);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(2.5, -0.5, .5);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(3., -1., .5);
    glEnd();

    // Tux asomandose (pinguino)
    glBindTexture(GL_TEXTURE_2D, texturas[3]); // Tux asomandose
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(4., -1., 1);
        glTexCoord2f(0.0, 0.4);
        glVertex3f(6, -1., 1);
        glTexCoord2f(1.0, 0.4);
        glVertex3f(6, -3.8, 1);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(4., -3.8, 1);
    glEnd();

    // Esfera con textura de la tierra
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD); // Modo de mezcla de texturas
    glBindTexture(GL_TEXTURE_2D, texturas[0]); // esfera
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glPushMatrix();
        glTranslatef(0, 1, 0);
        glutSolidSphere(1, 25, 25);
    glPopMatrix();
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);

    glFlush();
}

void ajusta(int ancho, int alto){
    glClearColor(.5, .5, .5, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-6, 6, -4, 4, -4, 4);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Función para cargar todas las texturas que se usarán
void carga_texturas(){
    // Texturas de imagenes .data
    cargaTextura_data(1000, 500, "PTierra.data", &texturas[0], 0, GL_TRUE);
    cargaTextura_data(127, 127, "madera.data", &texturas[1], 1, GL_FALSE);

    // Textura procedural espacio estrellado
    for (int i = 0; i < 64; i++) 
        for (int j = 0; j < 64; j++)        {
            GLboolean estrella = rand() % 100 == 0;
            proced[i][j][0] = (estrella) ? 255 : 0;
            proced[i][j][1] = (estrella) ? 255 : 0;
            proced[i][j][2] = (estrella) ? 255 : 0;
        }
    glGenTextures(2, &texturas[2]);
    glBindTexture(GL_TEXTURE_2D, texturas[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, proced);

    // Textura procedural Tux
    for (int i = 0; i < 32; i++)
        for (int j = 0; j < 32; j++){
            pixeles[i][j][0] = paleta[tux[i][j]][0];
            pixeles[i][j][1] = paleta[tux[i][j]][1];
            pixeles[i][j][2] = paleta[tux[i][j]][2];
        }
    glGenTextures(3, &texturas[3]);
    glBindTexture(GL_TEXTURE_2D, texturas[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 32, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, pixeles);
}

// Función que controla las teclas normales
void salir(unsigned char key, int x, int y){
    if (key == 27) {
        for (int i = 0; i < 4; i++)
            glDeleteTextures(i, &texturas[i]);
        exit(0);
    }
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitWindowSize(600, 400);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Múltiples texturas");
    carga_texturas();
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(salir);
    glutMainLoop();
    return 0;
}