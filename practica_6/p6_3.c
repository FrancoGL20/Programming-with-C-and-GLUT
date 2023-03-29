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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Variables globales
char nombre_luz[20]="Luz Puntual";
GLfloat girax = 15, giray = -15, zoom = 0;
GLboolean ejes = GL_TRUE;

// Propiedades de luz puntual (sol), llamada luz 0
GLfloat puntual_light_position[] = { 0.0,3.0,0.0, 1.0 };
GLfloat puntual_light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };

// Propiedades de luz direccional (muchos rayos), llamada luz 1
GLfloat direcc_light_position[] = { 0.0, 3.0, 0.0, 0.0 }; // Definimos la luz como direccional y la direccion
GLfloat direcc_light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };

// Propiedades de luz focal (lampara), llamada luz 2
GLfloat focal_light_position[] = { 0.0,3.0,0.0, 1.0 };
GLfloat focal_light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat focal_light_spot_direction[] = { 0.0, -1.0, 0.0 };
GLfloat focal_light_spot_cutoff = 50.0;

// Propiedades material tetera y esfera
float mat_ambiente[] = {.3, 0, 0, 1}; // Color de la luz reflejada (rojo)
float mat_difuso[] = {.5, 0, 0, 1}; // Color de la luz reflejada (rojo)
float mat_especular[] = {.8, .8, 0, 1}; // Color de la luz reflejada (amarillo)
float mat_emision[] = {0, 0, 0, 1}; // Se define la emisión de la superficie (0-128)
float mat_brillo = 64; // Se define el brillo de la superficie (0-128)

// Propiedades material esfera-foco
float foco_ambiente_difusa[] = {1, 1, .1, 0};
float foco_emision[] = {0.5, 0.5, 0, 0};

// Rotacion XY y Zoom
void mover(void) {
    glTranslated(0, 0, zoom);
    glRotated(girax, 1.0, 0.0, 0.0);
    glRotated(giray, 0.0, 1.0, 0.0);
}

// Crear ejes
void creaEjes(void) {
    glDisable(GL_LIGHTING);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(11.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 11.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 11.0);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex3f(11.0, 0.0, 0.0); /* eje x */
        glVertex3f(10.5, 0.0, -.50);
        glVertex3f(10.5, 0.0, .50);
        //glColor3f(0.25, 1, 0.25); /* eje y */
        glVertex3f(0.0, 11.0, 0.0);
        glVertex3f(-.50, 10.5, 0.0);
        glVertex3f(.50, 10.5, 0.0);
        //glColor3f(0.25, 0.25, 1.0); /* eje z */
        glVertex3f(0.0, 0.0, 11.0);
        glVertex3f(-.50, 0.0, 10.5);
        glVertex3f(.50, 0.0, 10.5);
    glEnd();
    glEnable(GL_LIGHTING);
}

// Dibujar texto en pantalla
void dibujaTexto(void *tipo, char *s, float x, float y){
    glRasterPos2f(x, y);
    for (int i = 0; i < strlen(s); i++)
        glutBitmapCharacter(tipo, s[i]);
}

// Función de teclas normales
void teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
        case 'p':
            glEnable(GL_LIGHT0); // Activa la luz 0, puntual (sol)
            glDisable(GL_LIGHT1); // Desactiva la luz 1, direccional (muchos rayos)
            glDisable(GL_LIGHT2); // Desactiva la luz 2, focal (lampara)
            strcpy(nombre_luz, "Luz puntual");
            break;
        case 'd':
            glDisable(GL_LIGHT0); // Desactiva la luz 0, puntual (sol)
            glEnable(GL_LIGHT1); // Activa la luz 1, direccional (muchos rayos)
            glDisable(GL_LIGHT2); // Desactiva la luz 2, focal (lampara)
            strcpy(nombre_luz, "Luz direccional");
            break;
        case 'f':
            glDisable(GL_LIGHT0); // Desactiva la luz 0, puntual (sol)
            glDisable(GL_LIGHT1); // Desactiva la luz 1, direccional (muchos rayos)
            glEnable(GL_LIGHT2); // Activa la luz 2, focal (lampara)
            strcpy(nombre_luz, "Luz focal");
            break;
            break;
        case 'e': // activa/desactiva los ejes
            ejes = !ejes;
            break;
    }
    glutPostRedisplay();
}

// Funciones con Teclas Especiales
void rotar(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT: // rotacion en el eje Y
            giray -= 15;
            break;
        case GLUT_KEY_RIGHT: // rotacion en el eje Y
            giray += 15;
            break;
        case GLUT_KEY_UP: // rotacion en el eje X
            girax -= 15;
            break;
        case GLUT_KEY_DOWN: // rotacion en el eje X
            girax += 15;
            break;
    }
    glutPostRedisplay();
}

void dibuja(void){
    glClear(GL_COLOR_BUFFER_BIT);

    glDisable(GL_LIGHTING); // Desactiva la iluminación
    glColor3f(0, 0, 0);
    dibujaTexto(GLUT_BITMAP_HELVETICA_18, nombre_luz, -5, 4.5);
    glEnable(GL_LIGHTING); // Activa la iluminación

    glPushMatrix();
        mover();
        if (ejes) creaEjes();

        // Foco
        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, foco_ambiente_difusa);
            glMaterialfv(GL_FRONT, GL_EMISSION, foco_emision);
            glTranslatef(0, 3, 0);
            glutSolidSphere(.35, 15, 15); // esfera de tamaño 0.35
        glPopMatrix();

        // Características de esfera y tetera
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambiente);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difuso);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_especular);
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emision);
        glMaterialf(GL_FRONT, GL_SHININESS, mat_brillo);
        
        // Esfera
        glPushMatrix();
            glTranslatef(2.4, 2, 0);
            glutSolidSphere(.4, 20, 20); // esfera
        glPopMatrix();

        // Tetera
        glutSolidTeapot(1.3); // tetera

    glPopMatrix();

    // Vacia el buffer de dibujo
    glFlush(); 
}

void ajusta(int ancho, int alto){
    glClearColor(0.9, 0.9, 0.9, 0.0);

    glEnable(GL_LIGHTING); // Activa la iluminación
    
    // Creación de luces, llamadas 0, 1 y 2
    glLightfv(GL_LIGHT0, GL_POSITION, puntual_light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, puntual_light_diffuse);

    glLightfv(GL_LIGHT1, GL_POSITION, direcc_light_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, direcc_light_diffuse);

    glLightfv(GL_LIGHT2, GL_POSITION, focal_light_position);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, focal_light_diffuse);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, focal_light_spot_direction);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, focal_light_spot_cutoff);

    glEnable(GL_LIGHT0); // Activa la luz 0, puntual (sol)

    glEnable(GL_NORMALIZE); // Activa la normalización de normales

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-6, 6, -3, 5.5, -15,15);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition(20, 20);
    glutInitWindowSize(300*2, 240*2);
    glutCreateWindow("p6.3");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(rotar);
    glutMainLoop();
    return 0;
}