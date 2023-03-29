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
#include <stdio.h>
#include <math.h>

// Variables globales
GLfloat girax = 15, giray = -30, zoom = 0;
enum color{rojo,amarillo,verde};
enum color col=verde;
int frecuencia[][2]={{2,3000},{3,250},{2,250},{3,250},{2,250},{1,700},{0,4000}}; // color, tiempo en ms
int nFrecuencias=7;
int iFrecuencia=0;

// Caracteristicas de la luz
float luz_ambiente[] = {0.7, 0.7, 0, 0}; // Color de la luz ambiente (amarillo)
float luz_difusa[] = {1, 1, 0, 0}; // Color de la luz difusa (amarillo)
float luz_posicion[] = {10, 10, 10, 1}; // Posicion de la luz (arriba a la izquierda)

// Caracteristicas del material 0 (gris)
float mat0_ambient[] = {0.19225, 0.19225, 0.19225, 1}; // Color del objeto cuando no recibe luz (gris)
float mat0_diffuse[] = {0.50754, 0.50754, 0.50754, 1}; // Color del objeto cuando recibe luz difusa (gris)
float mat0_specular[] = {0.508273, 0.508273, 0.508273, 1}; // Color del objeto cuando recibe luz especular (gris)
float mat0_emision[] = {0, 0, 0, 1}; // Color del objeto cuando recibe luz especular (gris)
float mat0_shininess = 20; // Brillo del objeto (0-128)

// Caracteristicas del material 1 (rojo)
float mat1_ambient[] = {.3, 0, 0, 1}; // Color del objeto cuando no recibe luz (rojo)
float mat1_diffuse[] = {.5, 0, 0, 1}; // Color del objeto cuando recibe luz difusa (rojo)
float mat1_specular[] = {.8, .8, 0, 1}; // Color del objeto cuando recibe luz especular (amarillo)
float mat1_emision[] = {0.6, 0, 0, 1}; // Color del objeto cuando recibe luz especular (amarillo)
float mat1_shininess = 20; // Brillo del objeto (0-128)

// Caracteristicas del material 2 (amarillo)
float mat2_ambient[] = {.3, .3, 0, 1}; // Color del objeto cuando no recibe luz (amarillo)
float mat2_diffuse[] = {.5, .5, 0, 1}; // Color del objeto cuando recibe luz difusa (amarillo)
float mat2_specular[] = {.8, .8, 0, 1}; // Color del objeto cuando recibe luz especular (amarillo)
float mat2_emision[] = {0, 0, 0, 1}; // Color del objeto cuando recibe luz especular (amarillo)
float mat2_shininess = 20; // Brillo del objeto (0-128)

// Caracteristicas del material 3 (verde)
float mat3_ambient[] = {0, .3, 0, 1}; // Color del objeto cuando no recibe luz (verde)
float mat3_diffuse[] = {0, .5, 0, 1}; // Color del objeto cuando recibe luz difusa (verde)
float mat3_specular[] = {.8, .8, 0, 1}; // Color del objeto cuando recibe luz especular (amarillo)
float mat3_emision[] = {0, 0, 0, 1}; // Color del objeto cuando recibe luz especular (amarillo)
float mat3_shininess = 20; // Brillo del objeto (0-128)

// Caracteristicas del material 4 (naranja claro)
float mat4_ambient[] = {0.829412, 0.823529, 0.027451, 1}; // Color del objeto cuando no recibe luz (naranja claro)
float mat4_diffuse[] = {0.880392, 0.668627, 0.113725, 1}; // Color del objeto cuando recibe luz difusa (naranja claro)
float mat4_specular[] = {0.992157, 0.941176, 0.807843, 1}; // Color del objeto cuando recibe luz especular (naranja claro)
float mat4_emision[] = {0, 0, 0, 1}; // Color del objeto cuando recibe luz especular (amarillo)
float mat4_shininess = 27; // Brillo del objeto (0-128)

// Rotacion XY y Zoom
void mover(void) {
    glTranslated(0, 0, zoom);
    glRotated(giray, 0.0, 1.0, 0.0);
    glRotated(girax, 1.0, 0.0, 0.0);
}

void materialGris(){
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat0_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat0_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat0_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat0_emision);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat0_shininess);
}

void dibuja(void) {
    // limpiar frame buffer y Z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        mover();

        // Base del semaforo
        glPushMatrix();
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat4_ambient);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat4_diffuse);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat4_specular);
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat4_emision);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat4_shininess);
            glScalef(4, 10, 2);
            glutSolidCube(1);
        glPopMatrix();

        // Linterna roja
        glPushMatrix();
            if (col==rojo){
                glMaterialfv(GL_FRONT, GL_AMBIENT, mat1_ambient);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, mat1_diffuse);
                glMaterialfv(GL_FRONT, GL_SPECULAR, mat1_specular);
                glMaterialfv(GL_FRONT, GL_EMISSION, mat1_emision);
                glMaterialf(GL_FRONT, GL_SHININESS, mat1_shininess);
            }else{
                materialGris();
            }
            glTranslatef(0, 3, 0.5);
            glScalef(1.3, 1.3, 1.3);
            glutSolidSphere(1.0, 40, 40);
        glPopMatrix();

        // Linterna amarilla
        glPushMatrix(); // foco yellow
            if (col==amarillo){
                glMaterialfv(GL_FRONT, GL_AMBIENT, mat2_ambient);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, mat2_diffuse);
                glMaterialfv(GL_FRONT, GL_SPECULAR, mat2_specular);
                glMaterialfv(GL_FRONT, GL_EMISSION, mat2_emision);
                glMaterialf(GL_FRONT, GL_SHININESS, mat2_shininess);
            }else{
                materialGris();
            }
            glTranslatef(0, 0, 0.5);
            glScalef(1.3, 1.3, 1.3);
            glutSolidSphere(1.0, 40, 40);
        glPopMatrix();
        
        // Linterna verde
        glPushMatrix(); // foco green
            if (col==verde){
                glMaterialfv(GL_FRONT, GL_AMBIENT, mat3_ambient);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, mat3_diffuse);
                glMaterialfv(GL_FRONT, GL_SPECULAR, mat3_specular);
                glMaterialfv(GL_FRONT, GL_EMISSION, mat3_emision);
                glMaterialf(GL_FRONT, GL_SHININESS, mat3_shininess);
            }else{
                materialGris();
            }
            glTranslatef(0, -3, 0.5);
            glScalef(1.3, 1.3, 1.3);
            glutSolidSphere(1.0, 40, 40);
        glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
}

// Funciones con Teclas
void teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
        case '+': // aumenta el zoom
            zoom++;
            break;
        case '-': // disminuye el zoom
            zoom--;
            break;
        case 'p': // proyeccion perspectiva
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(45, 1, 10, 100);
            zoom = -40;
            break;
        case 'o': // proyeccion ortogonal
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-13, 13, -13, 13, -30, 30);
            zoom = 0;
        default:
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

void ajusta(int ancho, int alto) {
    glClearColor(1.0, 1.0, 1.0, 0.0); // color de fondo

    glEnable(GL_LIGHTING); // Activa la iluminación
    glEnable(GL_LIGHT0); // Activa la luz 0
    glEnable(GL_NORMALIZE); // Activa la normalización de normales

    glLightfv(GL_LIGHT0, GL_POSITION, luz_posicion); // Posición de la luz

    glEnable(GL_DEPTH_TEST);          // activa el Z-buffer
    glMatrixMode(GL_MODELVIEW);       // matriz de modelado
    glLoadIdentity();                 // matriz identidad
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -30, 30);
    
}

// Función para animar
void anima(int v) {
    col=frecuencia[iFrecuencia][0];
    glutTimerFunc(frecuencia[iFrecuencia][1], anima, 0); 
    iFrecuencia=(iFrecuencia+1)%nFrecuencias;
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500); // tamaño de la ventana de 500x500
    glutInit(&argc, argv);
    glutCreateWindow("P6.2");
    glutTimerFunc(1, anima, 0);
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(rotar);
    glutMainLoop();
    return 0;
}
