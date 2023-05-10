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

#include <stdlib.h>

void myinit(void) {
    GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat position[] = {0.0, 3.0, 3.0, 0.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glFrontFace(GL_CW);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
}

void renderTeapot(GLfloat x, GLfloat y,
                  GLfloat ambr, GLfloat ambg, GLfloat ambb,
                  GLfloat difr, GLfloat difg, GLfloat difb,
                  GLfloat specr, GLfloat specg, GLfloat specb,
                  GLfloat shine) // x: posicion x, y: posicion y, ambr: componente roja de la componente ambiental, ambg: componente verde de la componente ambiental, ambb: componente azul de la componente ambiental, difr: componente roja de la componente difusa, difg: componente verde de la componente difusa, difb: componente azul de la componente difusa, specr: componente roja de la componente especular, specg: componente verde de la componente especular, specb: componente azul de la componente especular, shine: componente especular
{
    float mat[4];
    glPushMatrix();
        glTranslatef(x, y, 0.0);
        mat[3] = 1.0;
        mat[0] = ambr;
        mat[1] = ambg;
        mat[2] = ambb;
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
        mat[0] = difr;
        mat[1] = difg;
        mat[2] = difb;
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
        mat[0] = specr;
        mat[1] = specg;
        mat[2] = specb;
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
        glMaterialf(GL_FRONT, GL_SHININESS, shine * 128.0);
        glutSolidTeapot(2.5);
    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Laton, color amarillo
    renderTeapot(5.0, 10.0, 0.329412, 0.223529, 0.027451,
                 0.780392, 0.568627, 0.113725, 0.992157, 0.941176, 0.807843,
                 0.21794872);
    // Plata, color gris
    renderTeapot(10.0, 16.0, 0.19225, 0.19225, 0.19225,
                 0.50754, 0.50754, 0.50754, 0.508273, 0.508273, 0.508273, 0.4);
    // Plastico verde, color verde
    renderTeapot(10.0, 4.0, 0.0, 0.0, 0.0,
                 0.1, 0.35, 0.1, 0.45, 0.55, 0.45, .25);
    // Plastico Rojo, color rojo
    renderTeapot(15.0, 10.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0,
                 0.7, 0.6, 0.6, .25);

    glFlush();
}

void myReshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 20.0, 0.0, 20.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Materiales");
    glutInitWindowSize(500, 500);
    myinit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}