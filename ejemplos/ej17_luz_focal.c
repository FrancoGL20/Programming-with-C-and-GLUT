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

// Propiedades luz
float luz_ambiente[] = {0.7, 0.7, 0, 0}; // Color de la luz ambiental (amarillo)
float luz_difusa[] = {1, 1, 0, 0}; // Color de la luz difusa (blanco)
float luz_posicion[] = {0, 3, 0, 1}; // Posición de la luz, 1: luz puntual (sol), 0: muchos rayos (luz ambiental)

// Propiedades material tetera y esfera
float mat_ambiente[] = {.3, 0, 0, 1}; // Color de la luz reflejada (rojo)
float mat_difuso[] = {.5, 0, 0, 1}; // Color de la luz reflejada (rojo)
float mat_especular[] = {.8, .8, 0, 1}; // Color de la luz reflejada (amarillo)
float mat_emision[] = {0, 0, 0, 1}; // Se define la emisión de la superficie (0-128)
float mat_brillo = 64; // Se define el brillo de la superficie (0-128)

// Propiedades material esfera-foco
float foco_ambiente_difusa[] = {1, 1, .1, 0};
float foco_emision[] = {0.5, 0.5, 0, 0};

void ajusta(int ancho, int alto){
    glClearColor(0.9, 0.9, 0.9, 0.0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa);
    glLightfv(GL_LIGHT0, GL_POSITION, luz_posicion);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, .8);

    glEnable(GL_LIGHTING); // Activa la iluminación
    glEnable(GL_LIGHT0); // Activa la luz 0
    glEnable(GL_NORMALIZE); // Activa la normalización de normales

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3, 3, -1.5, 3.5, -3, 3);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void dibuja(void){
    glClear(GL_COLOR_BUFFER_BIT);

    // Foco
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, foco_ambiente_difusa);
        glMaterialfv(GL_FRONT, GL_EMISSION, foco_emision);
        glTranslatef(0, 3, 0);
        glutSolidSphere(.35, 15, 15);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difuso);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_especular); // Color de la luz reflejada (amarillo)
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emision); // Se define la emisión de la superficie (0-128), es decir, el color de la luz que emite la superficie
    glMaterialf(GL_FRONT, GL_SHININESS, mat_brillo);
    // Esfera
    glPushMatrix();
        glTranslatef(2.4, 2, 0);
        glutSolidSphere(.4, 20, 20); // esfera
    glPopMatrix();

    // Tetera
    glutSolidTeapot(1.3); // tetera

    // Vacia el buffer de dibujo
    glFlush(); 
}
void teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
    }
    glutPostRedisplay();
}
int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition(20, 20);
    glutInitWindowSize(300*3, 250*3);
    glutCreateWindow("Luz Puntual");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
    glutMainLoop();
    return 0;
}