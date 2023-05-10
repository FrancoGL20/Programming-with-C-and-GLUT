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
#include <malloc.h>
int ancho = 192, alto = 183;
unsigned char *datos; // equivalente a unsigned byte

void leeImagen() {
    FILE *imagen;
    imagen = fopen("Anahuac.data", "rb");
    if (imagen == NULL)
        exit(1);
    datos = (unsigned char *)malloc(ancho * alto * 3);
    fread(datos, ancho * alto * 3, 1, imagen);
    fclose(imagen);
}

void cargaTextura() {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, datos);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(-2.0, -2.0);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(2.0, -2.0);
    glTexCoord2f(0.5, 0.0);
    glVertex2f(0.0, 2.0);
    glEnd();
    glFlush();
}

void ajusta(int width, int height) {
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

void salir(unsigned char key, int x, int y) {
    if (key == 27) {
        free(datos);
        exit(0);
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(300, 300);
    glutCreateWindow("textura sintética raw");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(salir);
    glutMainLoop();
    return 0;
}