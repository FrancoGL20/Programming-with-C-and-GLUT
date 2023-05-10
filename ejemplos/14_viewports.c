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

void dibuja(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.7, 0.0, 1.0);
    glLineWidth(3);

    glViewport(0, 0, 300, 300); // x, y, ancho, alto
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, 1, 30); // Proyección ortogonal en 3D con los parámetros: izq, der, abajo, arriba, cerca, lejos
    glPushMatrix();
        glTranslatef(0.0, 0.0, -3);
        glRotatef(30.0, 1.0, 0.0, 0.0);
        glRotatef(70.0, 0.0, 1.0, 0.0);
        glScalef(1.7, .5, .5);
        glutWireCube(1);
    glPopMatrix();

    // Se define el viewport con el tamaño de la ventana
    glViewport(300, 0, 300, 300); // x, y, ancho, alto
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 1, 30); // Proyección perspectiva con los parámetros: ángulo de apertura, aspecto, cerca, lejos
    glPushMatrix();
        glTranslatef(0.0, 0.0, -3);
        glRotatef(30.0, 1.0, 0.0, 0.0);
        glRotatef(70.0, 0.0, 1.0, 0.0);
        glScalef(1.7, .5, .5);
        glutWireCube(1);
    glPopMatrix();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 300);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Proyecciones");
    glutDisplayFunc(dibuja);
    glutMainLoop();
    return 0;
}