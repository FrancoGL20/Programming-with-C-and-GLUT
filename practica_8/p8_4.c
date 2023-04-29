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

// Definiciones
#define GRAVEDAD -9.8 // m/s^2
#define MASA 200  // masa de la pelota

// Estructuras
struct ball {
    double posicion[3];
    double velocidad[3];
    double fzaX;
    double fzaZ;
    int color[3];
};

// Variables globales
struct ball pelota[7]={
    {{0, 0, 0}, {0, 0, 0}, .02, -.05, {0, 0, 255}},
    {{-3, 0, -3}, {0, 0, 0}, .03, -.061, {255, 0, 0}},
    {{-3, 0, 3}, {0, 0, 0}, .025, -.05, {0, 255, 0}},
    {{3, 0, -3}, {0, 0, 0}, .035, -.057, {255, 255, 0}},
    {{3, 0, 3}, {0, 0, 0}, .03, -.054, {255, 0, 255}},
    {{0, 0, -3}, {0, 0, 0}, .02, -.065, {0, 255, 255}},
    {{0, 0, 3}, {0, 0, 0}, .026, -.067, {255, 255, 255}}
};
double h = 0.075; // h incrementos de tiempo
GLboolean bx = GL_FALSE;
GLboolean by = GL_FALSE;
GLboolean bz = GL_FALSE;

void integraEuler() {
    for (int i = 0; i < 7; i++) {
        // v(t+h)=v(t)+F(t)/m*h
        if (bx)
            pelota[i].velocidad[0] += pelota[i].fzaX * h;
        if (by)
            pelota[i].velocidad[1] += GRAVEDAD / MASA * h;
        if (bz)
            pelota[i].velocidad[2] += pelota[i].fzaZ * h;

        // x(t+h)=x(t) + v(t+h)*h
        pelota[i].posicion[0] += pelota[i].velocidad[0] * h;
        pelota[i].posicion[1] += pelota[i].velocidad[1] * h;
        pelota[i].posicion[2] += pelota[i].velocidad[2] * h;
    }
}

void ajusta(int alto, int ancho) {
    glClearColor(0.5, 0.5, 0.5, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60, (float)alto / ancho, 1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(2);
    glPushMatrix();
        glTranslatef(0, 0, -16);
        glColor3ub(0, 0, 0);
        glutWireCube(11); // Cubo grande (contenedor)

        // Esferas creadas dentro de un ciclo for
        for(int i=0;i<7;i++){
            glColor3ub(pelota[i].color[0], pelota[i].color[1], pelota[i].color[2]);
            glPushMatrix();
                glTranslated(pelota[i].posicion[0], pelota[i].posicion[1], pelota[i].posicion[2]);
                glutSolidSphere(.4, 20, 20);
            glPopMatrix();
        }
    glPopMatrix();

    glutSwapBuffers();
}

void mueve(void) {
    integraEuler();

    // Colisiones
    for(int i=0;i<7;i++){
        if (pelota[i].posicion[0] >= 5 || pelota[i].posicion[0] <= -5) { // X
            pelota[i].fzaX = -1 * pelota[i].fzaX;
            pelota[i].velocidad[0] = 0;
            pelota[i].posicion[0] = (pelota[i].posicion[0] >= 5) ? 4.8 : -4.8;
        }
        if (pelota[i].posicion[1] >= 5) { // Y Arriba
            pelota[i].velocidad[1] = 0;
            pelota[i].posicion[1] = 4.2;
        }
        if (pelota[i].posicion[1] <= -5) { // Y Abajo
            pelota[i].velocidad[1] = 0.9;
            pelota[i].posicion[1] = -4.8;
        }
        if (pelota[i].posicion[2] >= 5 || pelota[i].posicion[2] <= -5) { // Z
            pelota[i].fzaZ = -1 * pelota[i].fzaZ;
            pelota[i].velocidad[2] = 0;
            pelota[i].posicion[2] = (pelota[i].posicion[2] >= 5) ? 4.8 : -4.8;
        }
    }
    glutPostRedisplay();
}

void teclado(unsigned char key, int x, int y) {
    switch (key) {
    case 27:
        exit(0);
    case 'x':
        bx = !bx;
        break;
    case 'y':
        by = !by;
        break;
    case 'z':
        bz = !bz;
    }
}

int main(int argc, char **argv) {
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("P8.4");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
    glutIdleFunc(mueve);
    glutMainLoop();
    return 0;
}