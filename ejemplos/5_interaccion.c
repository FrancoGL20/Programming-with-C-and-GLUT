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

int pos_x[60], pos_y[60];
int puntos = 0;
int tam = 4;                 // tamaño inicial del punto
GLboolean mostrar = GL_TRUE; // mostrar o no los puntos
GLboolean rojo = GL_TRUE;    // elección de color

void ajusta(int ancho, int alto) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

void raton(int boton, int estado, int x, int y) {
    int alto_ventana = 480;
    if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
        pos_x[puntos] = x;
        pos_y[puntos] = alto_ventana - y; // voltea la coordenada y
        puntos++;
    }
    glutPostRedisplay();
}

void pageUp_Down(int tecla, int x, int y) {
    switch (tecla) {
    case GLUT_KEY_PAGE_UP:
        tam++;
        break;
    case GLUT_KEY_PAGE_DOWN:
        tam--;
        break;
    case GLUT_KEY_HOME:
        puntos = 0;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void teclado(unsigned char tecla, int x, int y) {
    switch (tecla) {
    case 27:
        exit(0); // Esc =>Salir del programa
    case 'r':
        rojo = GL_TRUE; // rojo
        break;
    case 'a':
        rojo = GL_FALSE; // azul
        break;
    case 'm':
        mostrar = !mostrar;
    default:
        break;
    }
    glutPostRedisplay();
}

void dibuja(void) {
    int i;
    glClear(GL_COLOR_BUFFER_BIT);
    if (mostrar) {
        (rojo) ? glColor3f(1.0, 0.0, 0.0) : glColor3f(0.0, 0.0, 1.0);
        glPointSize(tam);
        glBegin(GL_POINTS);
        for (i = 0; i < puntos; i++)
            glVertex2i(pos_x[i], pos_y[i]);
        glEnd();
    }
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Dibujando puntos");
    // Registro de funciones
    glutDisplayFunc(dibuja);
    glutMouseFunc(raton);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(pageUp_Down);
    glutReshapeFunc(ajusta);
    glutMainLoop();
    return 0;
}