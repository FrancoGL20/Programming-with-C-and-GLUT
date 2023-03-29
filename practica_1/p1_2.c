#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#define PI 3.14159265359

void evaluaFuncion(double (*funcion)(double)){
    int amplitud = 240;
    int periodo = 640;
    int f;
    glColor3ub(255, 102, 51); // cambio de color
    glBegin(GL_LINE_STRIP);
    for (int i = (0-periodo/2); i <= (periodo/2); i++){ 
        f = roundf(amplitud * (  (*funcion)  (((2 * PI) / periodo) * i)  ));
        f += roundf(amplitud);
        // hacer el dibujo
        glVertex2f(i+320,f); // 320 es el centro de la pantalla
    }
    glEnd();
    glColor3ub(0, 0, 0); // cambio de color
}
void ajusta(int ancho, int alto){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480); // la relacion aspecto de la ventana es 640*480
}
void dibuja(void){
    // limpiar buffer
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3ub(0, 0, 255); // cambio de color
    // malla azul
    glEnable(GL_LINE_STIPPLE); // habilitar punteado de línea
    glLineStipple(1,0xF0F0); // patrón del dibujo
    glBegin(GL_LINES);
        // líneas verticales
        for (int i = 0; i < 640; i+=20) {
            glVertex2i(i,0);
            glVertex2i(i,480);
        }
        // líneas horizontales
        for (int i = 0; i < 480; i+=20) {
            glVertex2i(0,i);
            glVertex2i(640,i);
        }
    glEnd();
    glDisable(GL_LINE_STIPPLE); // deshabilitar punteado de línea
    
    glColor3ub(0, 0, 0); // cambio de color
    glLineWidth(3.0); // ancho de la línea
    glBegin(GL_LINES);
        glVertex2i(640/2,0);
        glVertex2i(640/2,480);
        glVertex2i(0,480/2);
        glVertex2i(640,480/2);
    glEnd();// ancho de la línea

    evaluaFuncion(cos);

    // enviarlo a pantalla
    glFlush();
}
int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480); // tamaño de la ventana que se va a obtener
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Practica 1.2"); // titulo de la ventana
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutMainLoop();
    return 0;
}
