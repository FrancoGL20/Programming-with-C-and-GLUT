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

void ajusta(int ancho, int alto) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

void dibuja(void) {
    int triangulo[6][2] = {{50, 25}, {150, 100}, {250, 25}, {350, 25}, {450, 100}, {550, 25}};
    float naranja[3] = {1.0, 0.5, 0.0};
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(10);
    glColor3fv(naranja);
    glBegin(GL_LINES);
    glVertex2i(100, 350);
    glVertex2i(100, 450);
    glEnd();
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xAAAA);
    glBegin(GL_LINES);
    glVertex2i(300, 350);
    glVertex2i(300, 450);
    glEnd();
    glLineStipple(2, 0xAAAA);
    glBegin(GL_LINES);
    glVertex2i(500, 350);
    glVertex2i(500, 450);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    glBegin(GL_QUAD_STRIP);
    glColor3f(0.0, 0.5, 0.5);
    glVertex2i(500, 300);
    glVertex2i(500, 150);
    glColor3f(0.0, 0.7, 0.7);
    glVertex2i(300, 250);
    glVertex2i(300, 150);
    glColor3f(0.0, 1, 1);
    glVertex2i(100, 200);
    glVertex2i(100, 150);
    glEnd();
    glColor3f(1.0, 0.5, 0.5);
    glBegin(GL_TRIANGLES);
    glVertex2iv(triangulo[0]);
    glVertex2iv(triangulo[1]);
    glVertex2iv(triangulo[2]);
    glVertex2iv(triangulo[3]);
    glVertex2iv(triangulo[4]);
    glVertex2iv(triangulo[5]);
    glEnd();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Primitivas");
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutMainLoop();
    return 0;
}