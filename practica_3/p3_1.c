// EL programa dibuja una pelota que rebota en los bordes de la ventana
// el numero de vertices de la pelota se puede cambiar con el menu
// el color de la pelota se puede cambiar con las teclas n, r y a

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdlib.h>
#include <math.h>

float xc = 50, yc = 50, velX = 20, velY = 20, radio = 25;
GLubyte paleta[3][3] = {{0, 0, 0}, {255, 0, 0}, {0, 0, 255}};
int n_lados = 20;

// Para glutCreateMenu y glutAttachMenu
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
    for (i = 0; i <= 360; i += 360 / seg) // 360 / seg es el angulo de cada segmento
        glVertex2i(x + radio * cos(i * M_PI / 180), y + radio * sin(i * M_PI / 180)); // M_PI es PI
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
    circulo(xc, yc, n_lados);
    glutSwapBuffers(); // en lugar de glFlush()
}

void anima(void) {
    if (xc + radio >= 640 || xc - radio <= 0) // Si la pelota toca los bordes
        velX = -velX; // Invierte la velocidad en X
    if (yc + radio >= 480 || yc - radio <= 0) // Si la pelota toca los bordes
        velY = -velY; // Invierte la velocidad en Y
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
    glutTimerFunc(150, animaT, 0); 
    glutPostRedisplay();
}

void cambia(int opcion) {
    switch (opcion) {
        case 10:
            n_lados = 20;
            break;
        case 20:
            n_lados = 18;
            break;
        case 30:
            n_lados = 12;
            break;
        case 40:
            n_lados = 8;
            break;
        case 50:
            n_lados = 3;
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
    glutTimerFunc(200, animaT, 0); // Para animar con un timer
    glutDisplayFunc(dibuja); // Para dibujar la pelota
    glutKeyboardFunc(pinta); // Para cambiar el color de la pelota

    glutCreateMenu(cambia); // Para cambiar el numero de lados
    glutAddMenuEntry("20 lados", 10);
    glutAddMenuEntry("18 lados", 20);
    glutAddMenuEntry("12 lados", 30);
    glutAddMenuEntry("8 lados", 40);
    glutAddMenuEntry("3 lados", 50);
    glutAddMenuEntry("Salir", 100);
    glutAttachMenu(GLUT_RIGHT_BUTTON); // Para cambiar el modo de dibujo

    glutMainLoop();
    return 0;
}