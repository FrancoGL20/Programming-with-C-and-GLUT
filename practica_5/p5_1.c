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

// Variables globales
GLUquadricObj *cilindro;
GLfloat girax = 15, giray = -30, zoom = 0;
GLboolean malla = GL_FALSE, ejes = GL_TRUE;
enum color{rojo,amarillo,verde};
enum color col=rojo;
int frecuencia[][2]={{2,3000},{3,250},{2,250},{3,250},{2,250},{1,700},{0,4000}}; // color, tiempo en ms
int nFrecuencias=7;
int iFrecuencia=0;

// Rotacion XY y Zoom
void mover(void) {
    glTranslated(0, 0, zoom);
    glRotated(giray, 0.0, 1.0, 0.0);
    glRotated(girax, 1.0, 0.0, 0.0);
}

// Crear malla
void creaMalla(int long_eje) {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    int i;
    for (i = -long_eje; i <= long_eje; i++) {
        glVertex3f(i, 0, -long_eje);
        glVertex3f(i, 0, long_eje);
        glVertex3f(-long_eje, 0, i);
        glVertex3f(long_eje, 0, i);
    }
    glEnd();
}

// Crear ejes
void creaEjes(void) {
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
        glColor3f(0.25, 1, 0.25); /* eje y */
        glVertex3f(0.0, 11.0, 0.0);
        glVertex3f(-.50, 10.5, 0.0);
        glVertex3f(.50, 10.5, 0.0);
        glColor3f(0.25, 0.25, 1.0); /* eje z */
        glVertex3f(0.0, 0.0, 11.0);
        glVertex3f(-.50, 0.0, 10.5);
        glVertex3f(.50, 0.0, 10.5);
    glEnd();
}


void dibuja(void) {
    // limpiar frame buffer y Z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        mover();
        if (malla)
            creaMalla(10);
        if (ejes)
            creaEjes();

        // Base del semaforo
        glColor3ub(255, 165, 0);
        glPushMatrix();
            glScalef(4, 10, 2);
            glutSolidCube(1);
        glPopMatrix();

        // Linterna roja
        glColor3ubv(col==rojo? (GLubyte[]){255,0,0} : (GLubyte[]){128,128,128});
        glPushMatrix();
            glTranslatef(0, 3, 0.5);
            glScalef(1.3, 1.3, 1.3);
            glutSolidSphere(1.0, 40, 40);
        glPopMatrix();

        // Linterna amarilla
        glColor3ubv(col==amarillo? (GLubyte[]){255,255,0} : (GLubyte[]){128,128,128});
        glPushMatrix(); // foco yellow
            glTranslatef(0, 0, 0.5);
            glScalef(1.3, 1.3, 1.3);
            glutSolidSphere(1.0, 40, 40);
        glPopMatrix();
        
        // Linterna verde
        glColor3ubv(col==verde? (GLubyte[]){0,255,0} : (GLubyte[]){128,128,128});
        glPushMatrix(); // foco green
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
        case 'm': // activa/desactiva la malla
            malla = !malla;
            break;
        case 'e': // activa/desactiva los ejes
            ejes = !ejes;
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
    glEnable(GL_DEPTH_TEST);          // activa el Z-buffer

    glMatrixMode(GL_MODELVIEW);       // matriz de modelado
    glLoadIdentity();                 // matriz identidad
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-15, 15, -15, 15, -30, 30);
    
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
    glutCreateWindow("P5.1");
    glutTimerFunc(1, anima, 0);
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(rotar);
    glutMainLoop();
    return 0;
}
