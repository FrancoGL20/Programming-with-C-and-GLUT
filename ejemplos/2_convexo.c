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
#include <stdbool.h> // bool, true, false

int pos_x[60], pos_y[60];
int puntos = 0;
GLboolean fin = GL_FALSE;
void ajusta(int ancho, int alto) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}
void raton(int boton, int estado, int x, int y) {
    int alto_ventana = 480;
    if (!fin) {
        if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
            pos_x[puntos] = x;
            pos_y[puntos] = alto_ventana - y; // voltea la coordenada y
            puntos++;
        }
        glutPostRedisplay();
    }
}
void termina(int tecla, int x, int y) {
    switch (tecla) {
    case GLUT_KEY_END: // Tecla Fin
        fin = GL_TRUE;
        break;
    case GLUT_KEY_HOME: // Tecla Inicio
        puntos = 0;
        fin = GL_FALSE;
    }
    glutPostRedisplay();
}
void teclado(unsigned char tecla, int x, int y) {
    if (tecla == 27)
        exit(0); // Esc =>Salir del programa
}
bool ccw(int a, int b, int c) {
    double area2 = (pos_x[b] - pos_x[a]) * (pos_y[c] - pos_y[a]) - (pos_y[b] - pos_y[a]) * (pos_x[c] - pos_x[a]);
    return area2 >= 0;
}
void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);
    glPointSize(4);
    int i;
    if (puntos > 2) {
        i = 0;
        while (ccw(i % puntos, (i + 1) % puntos, (i + 2) % puntos) && i < puntos + 2)
            i++;
        (i == puntos + 2) ? glColor3f(0, 1, 0) : glColor3f(1, 0, 0);
    }
    glBegin(GL_POINTS);
    for (i = 0; i < puntos; i++)
        glVertex2i(pos_x[i], pos_y[i]);
    glEnd();

    glBegin(fin ? GL_LINE_LOOP : GL_LINE_STRIP);
    for (i = 0; i < puntos; i++)
        glVertex2i(pos_x[i], pos_y[i]);
    glEnd();
    
    glFlush();
}
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Poligono convexo");
    // Registro de funciones
    glutDisplayFunc(dibuja);
    glutMouseFunc(raton);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(termina);
    glutReshapeFunc(ajusta);
    glutMainLoop();
    return 0;
}