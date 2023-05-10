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

GLfloat girax = 0, giray = 0, zoom = -10, ojoX = 0, ojoY = 0;
GLboolean ejes = GL_TRUE, clic = GL_FALSE;
int gx, gy;

//   Rotacion XY y Zoom
void mover(void) {
    glTranslated(0, 0, zoom);
    glRotated(girax, 1.0, 0.0, 0.0);
    glRotated(giray, 0.0, 1.0, 0.0);
}

void raton(int boton, int estado, int xv, int yv) {
    clic = boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN;
    if (clic) {
        gx = xv;
        gy = yv;
    }
    if (boton == 3 || boton == 4) // scroll up => 3 scroll down=>4
        zoom += (boton == 3) ? 0.1 : -0.1;
    glutPostRedisplay();
}

void girar(int xv, int yv) {
    if (clic) {                       // inicia circulos con centro
        girax -= (gy - yv); // alrededor eje y
        giray -= (gx - xv); // alrededor eje x
        gx = xv;
        gy = yv;
    }
    glutPostRedisplay();
}

//  Ejes
void creaEjes(float largo) {
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(largo, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, largo, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, largo);
    glEnd();
    float base = largo * .025, alto = largo * .06;
    glColor3f(1, 0, 0);
    glPushMatrix(); // eje x
    glRotatef(90, 0, 1, 0);
    glTranslatef(0, 0, largo);
    glutSolidCone(base, alto, 10, 10);
    glPopMatrix();
    glColor3f(0, 1, 0);
    glPushMatrix(); // eje y
    glRotatef(-90, 1, 0, 0);
    glTranslatef(0, 0, largo);
    glutSolidCone(base, alto, 10, 10);
    glPopMatrix();
    glColor3f(0, 0, 1);
    glPushMatrix(); // eje z
    glTranslatef(0, 0, largo);
    glutSolidCone(base, alto, 10, 10);
    glPopMatrix();
    glColor3f(0.0, 0.0, 0.0);
}

void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // reinicia la pila de modelo
    gluLookAt(ojoX, ojoY, 0, 0, 0, -1, 0, 1, 0);
    glPushMatrix();
    mover();
    glColor3f(.1, .5, .5);
    glutWireTeapot(1.5);
    if (ejes)
        creaEjes(4);
    glPopMatrix();
    glutSwapBuffers();
}

void teclado(unsigned char key, int x, int y) {
    if (key == 27)
        exit(0);
}

void flechas(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
        ojoX -= .1;
        break;
    case GLUT_KEY_RIGHT:
        ojoX += .1;
        break;
    case GLUT_KEY_UP:
        ojoY += .1;
        break;
    case GLUT_KEY_DOWN:
        ojoY -= .1;
    }
    glutPostRedisplay();
}

void ajusta(int ancho, int alto) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 3, 60);
}

int main(int argc, char **argv) {
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutInit(&argc, argv);
    glutCreateWindow("Camara");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(flechas);
    glutMouseFunc(raton);
    glutMotionFunc(girar);
    glutMainLoop();
    return 0;
}
