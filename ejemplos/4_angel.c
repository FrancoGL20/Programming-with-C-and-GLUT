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

void dibuja(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glTranslatef(0.0, 0.0, -4.0);
    glColor3f(1.0, 0.7, 0.0); // aureola
    glTranslatef(0.0, .8, 0.0);
    glRotatef(90, 1., 0., 0.);
    glutSolidTorus(0.08, 0.7, 20, 20);
    glColor3f(0.8, 0.5, 0.5); // cara
    glScalef(.9, .75, .9);
    glutSolidSphere(1.0, 40, 40);
    glColor3f(0.0, 0.0, 0.0); // ojos
    glTranslatef(-.25, .2, .85);
    glutSolidSphere(.1, 8, 8);
    glTranslatef(.25, .2, .85);
    glutSolidSphere(.1, 8, 8);
    glColor3f(1.0, 0.0, 0.0); // boca
    glTranslatef(0, 0, .8);
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.3, -0.1);
    glVertex2f(-0.2, -0.3);
    glVertex2f(0.2, -0.3);
    glVertex2f(0.3, -0.1);
    glEnd();
    glFlush();
}
void ajusta(int ancho, int alto){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)ancho / alto, 3.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
int main(int argc, char **argv){
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(480, 480);
    glutInit(&argc, argv);
    glutCreateWindow("Anleg");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutMainLoop();
    return 0;
}