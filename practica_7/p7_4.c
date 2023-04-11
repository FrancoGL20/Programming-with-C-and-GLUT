#include <GL/glut.h>
#include <stdio.h>
#include <malloc.h>

// Variables globales
int ancho = 200, alto = 200;
unsigned char *datos; // equivalente a unsigned byte

// Función que lee la imagen de un archivo .data
void leeImagen(){
    FILE *imagen;
    imagen = fopen("bear_brown.data", "rb");
    if (imagen == NULL)
        exit(1);
    datos = (unsigned char *)malloc(ancho * alto * 3);
    fread(datos, ancho * alto * 3, 1, imagen);
    fclose(imagen);
}

// Función que carga la textura de la imagen
void cargaTextura(){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, datos);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void dibuja(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);
        glVertex2f(2.0, 2.0);

        glTexCoord2f(0.0, 1.0);
        glVertex2f(2.0, -2.0);

        glTexCoord2f(1.0, 1.0);
        glVertex2f(-2.0, -2.0);

        glTexCoord2f(1.0, 0.0);
        glVertex2f(-2.0, 2.0);
    glEnd();
    glFlush();
}

void ajusta(int width, int height){
    glClearColor(0.7, 0.7, 0.7, 0.0);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.5, 2.5, -2.5, 2.5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    leeImagen();
    cargaTextura();
    glEnable(GL_TEXTURE_2D);
}

// Función que controla las teclas normales
void salir(unsigned char key, int x, int y){
    if (key == 27) {
        free(datos);
        exit(0);
    }
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(300, 300);
    glutCreateWindow("P7.4");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(salir);
    glutMainLoop();
    return 0;
}