#include <GL/glut.h>
#include <stdio.h>

enum color{rojo,amarillo,verde};
enum color col=rojo;
int frecuencia[][2]={{2,3000},{3,250},{2,250},{3,250},{2,250},{1,700},{0,4000}}; // color, tiempo
int nFrecuencias=7;
int iFrecuencia=0;

void ajustar(int ancho, int alto){
    glClearColor(1.0,1.0,1.0,0.0); // color de fondo de ventana
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480); // la relacion aspecto de la ventana es 640*480
}

// Función que modifica la posición del dibujo cada ciertos milisegundos
void anima(int v) {
    col=frecuencia[iFrecuencia][0];
    glutTimerFunc(frecuencia[iFrecuencia][1], anima, 0); 
    iFrecuencia=(iFrecuencia+1)%nFrecuencias;
    glutPostRedisplay();
}

void dibujar(void){
    glClear(GL_COLOR_BUFFER_BIT); // limpiar buffer de color

    glColor3ub(88, 207, 100); // cambio de color a verde
    
    // dibujo de líneas
    glBegin(GL_TRIANGLES);
        glColor3ubv(col==rojo? (GLubyte[]){255,0,0} : (GLubyte[]){128,128,128});
        glVertex2i(270,360-30);
        glVertex2i(370,360-30);
        glVertex2i(320,450-30);
        glColor3ubv(col==amarillo? (GLubyte[]){255,255,0} : (GLubyte[]){128,128,128});
        glVertex2i(270,240-30);
        glVertex2i(370,240-30);
        glVertex2i(320,330-30);
        glColor3ubv(col==verde? (GLubyte[]){0,255,0} : (GLubyte[]){128,128,128});
        glVertex2i(270,120-30);
        glVertex2i(370,120-30);
        glVertex2i(320,210-30);
    glEnd();

    // enviarlo a pantalla
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480); // tamaño de la ventana que se va a obtener
    glutInitWindowPosition(100, 150); // posición donde se colocará la ventana
    glutCreateWindow("Practica 1.2"); // titulo de la ventana
    glutReshapeFunc(ajustar);
    glutDisplayFunc(dibujar);
    glutTimerFunc(0, anima, 0); // Para animar con un timer
    glutMainLoop();
    return 0;
}