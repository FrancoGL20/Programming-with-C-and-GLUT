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

// Variables globales
double h = 0.075; // h incrementos de tiempo
double posicion[] = {0, 0, 0};
// variable posición, matriz de 7 x 3
double pos[7][3] = {
    {0, 0, 0},
    {-3, 0, -3},
    {-3, 0, 3}, // 3
    {3, 0, -3},
    {3, 0, 3},
    {0, 0, -3}, // 6
    {0, 0, 3}
};
double velocidad[] = {0, 0, 0};
double vel[7][3] = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}, // 3
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}, // 6
    {0, 0, 0}
};
double fzaX = .02;
double fzax[7] = {
    .02,
    .03,
    .025, // 3
    .035,
    .03,
    .02, // 6
    .026
};
double fzaZ = -.05;
double fzaz[7] = {
    -.05,
    -.061,
    -.05, // 3
    -.057,
    -.054,
    -.065, // 6
    -.067
};
// Bandera para activar/desactivar fuerzas
GLboolean bx = GL_FALSE;
GLboolean by = GL_FALSE;
GLboolean bz = GL_FALSE;

void integraEuler() {
    // TODO: recordar, quiza borrar
    // // v(t+h)=v(t)+F(t)/m*h
    // if (bx)
    //     velocidad[0] += fzaX * h;
    // if (by)
    //     velocidad[1] += GRAVEDAD / MASA * h;
    // if (bz)
    //     velocidad[2] += fzaZ * h;
    // // x(t+h)=x(t) + v(t+h)*h
    // posicion[0] += velocidad[0] * h;
    // posicion[1] += velocidad[1] * h;
    // posicion[2] += velocidad[2] * h;

    for (int i = 0; i < 7; i++) {
        if (bx)
            vel[i][0] += fzax[i] * h;
        if (by)
            vel[i][1] += GRAVEDAD / MASA * h;
        if (bz)
            vel[i][2] += fzaz[i] * h;

        pos[i][0] += vel[i][0] * h;
        pos[i][1] += vel[i][1] * h;
        pos[i][2] += vel[i][2] * h;
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

    glColor3ub(0, 0, 0);
    glLineWidth(2);
    glPushMatrix();
        glTranslatef(0, 0, -16);
        glutWireCube(11); 

        // Esfera 1
        glColor3ub(0, 0, 255);
        glPushMatrix();
            glTranslated(pos[0][0], pos[0][1], pos[0][2]);
            glutSolidSphere(.4, 20, 20);
        glPopMatrix();

        // Esfera 2
        glColor3ub(255, 0, 0);
        glPushMatrix();
            glTranslated(pos[1][0], pos[1][1], pos[1][2]);
            glutSolidSphere(.4, 20, 20);
        glPopMatrix();

        // Esfera 3
        glColor3ub(0, 255, 0);
        glPushMatrix();
            glTranslated(pos[2][0], pos[2][1], pos[2][2]);
            glutSolidSphere(.4, 20, 20);
        glPopMatrix();

        // Esfera 4
        glColor3ub(255, 255, 0);
        glPushMatrix();
            glTranslated(pos[3][0], pos[3][1], pos[3][2]);
            glutSolidSphere(.4, 20, 20);
        glPopMatrix();

        // Esfera 5
        glColor3ub(255, 0, 255);
        glPushMatrix();
            glTranslated(pos[4][0], pos[4][1], pos[4][2]);
            glutSolidSphere(.4, 20, 20);
        glPopMatrix();

        // Esfera 6
        glColor3ub(0, 255, 255);
        glPushMatrix();
            glTranslated(pos[5][0], pos[5][1], pos[5][2]);
            glutSolidSphere(.4, 20, 20);
        glPopMatrix();

        // Esfera 7
        glColor3ub(255, 255, 255);
        glPushMatrix();
            glTranslated(pos[6][0], pos[6][1], pos[6][2]);
            glutSolidSphere(.4, 20, 20);
        glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
}

void mueve(void) {
    integraEuler();

    // TODO: recordar, quiza borrar
    // // colisiones
    // if (posicion[0] >= 5 || posicion[0] <= -5) { // X
    //     fzaX = -1 * fzaX;
    //     velocidad[0] = 0;
    //     posicion[0] = (posicion[0] >= 5) ? 4.8 : -4.8;
    // }
    // if (posicion[1] >= 5) { // Y Arriba
    //     velocidad[1] = 0;
    //     posicion[1] = 4.2;
    // }
    // if (posicion[1] <= -5) { // Y Abajo
    //     velocidad[1] = 0.9;
    //     posicion[1] = -4.8;
    // }
    // if (posicion[2] >= 5 || posicion[2] <= -5) { // Z
    //     fzaZ = -1 * fzaZ;
    //     velocidad[2] = 0;
    //     posicion[2] = (posicion[2] >= 5) ? 4.8 : -4.8;
    // }

    for(int i=0;i<7;i++){
        if (pos[i][0] >= 5 || pos[i][0] <= -5) { // X
            vel[i][0] = -1 * vel[i][0];
            pos[i][0] = (pos[i][0] >= 5) ? 4.8 : -4.8;
        }
        if (pos[i][1] >= 5) { // Y Arriba
            vel[i][1] = 0;
            pos[i][1] = 4.2;
        }
        if (pos[i][1] <= -5) { // Y Abajo
            vel[i][1] = 0.9;
            pos[i][1] = -4.8;
        }
        if (pos[i][2] >= 5 || pos[i][2] <= -5) { // Z
            vel[i][2] = -1 * vel[i][2];
            pos[i][2] = (pos[i][2] >= 5) ? 4.8 : -4.8;
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
    glutIdleFunc(mueve); // Funcion de animacion
    glutMainLoop();
    return 0;
}