#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265359

// función para obtener las coordenadas de un circulo
int** getCoords(int nPoints, int r){
    int** coords = (int**)malloc(nPoints*sizeof(int*)); // arreglo de coordenadas
    for (int i = 0; i < nPoints; i++){ // inicializar el arreglo
        coords[i] = (int*)malloc(2*sizeof(int)); // cada coordenada tiene 2 valores
    }
    int x,y;
    int c=0;
    for (int theta = 0; theta < 360; theta+=(360/nPoints)){
        x=r*cos(theta*(PI/180)); 
        y=r*sin(theta*(PI/180));
        coords[c][0]=x;
        coords[c][1]=y;
        c++;
    }
    
    // regresar el arreglo de coordenadas
    return coords;
}

// función para dibujar completo el circulo 
void drawCircle(int posX0, int posY0, int r, int divs){
    int **coords = getCoords(divs, r);

    glColor3ub(255, 125, 0); // cambio de color
    glLineWidth(1.0); // ancho de la línea
    // dibujo de líneas
    int c=0;
    glBegin(GL_LINES);
    for (int i = 0; i < divs; i++){
        // para cada punto voy a dibujar una línea con los puntos siguientes
        for (int j = i+1; j < divs; j++){
            glVertex2i(coords[i][0]+posX0, coords[i][1]+posY0);
            // printf("x: %d, y: %d, ", coords[i][0]+posX0, coords[i][1]+posY0);
            glVertex2i(coords[j][0]+posX0, coords[j][1]+posY0);
            // printf("x: %d, y: %d\n", coords[j][0]+posX0, coords[j][1]+posY0);
            c++;
        }
    }
    glEnd();
    glColor3ub(0, 0, 0); // cambio de color
    printf("Dibuje %d líneas\n",c);
}

void adjust(int ancho, int alto){
    // color de fondo blanco
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // la relacion aspecto de la ventana es 640*480
    gluOrtho2D(0,640,0,480); 
}
void draw(void){
    glClear(GL_COLOR_BUFFER_BIT); // limpiar buffer de color

    drawCircle(319,360,90,15);
    drawCircle(416-21,480-30,20,8);
    drawCircle(213+25,240+30,20,6);
    drawCircle(416-21,240+30,20,4);
    drawCircle(213+25,480-30,20,9);

    // dibujo de cuadricula
    glBegin(GL_LINES);
        glVertex2i(0,240);
        glVertex2i(640,240);
        glVertex2i(213,0);
        glVertex2i(213,480);
        glVertex2i(426,0);
        glVertex2i(426,480);
    glEnd();

    // enviarlo a pantalla
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480); // tamaño de la ventana que se va a obtener
    glutInitWindowPosition(100, 150); // posición de la ventana
    glutCreateWindow("T2_2"); // titulo de la ventana
    glutReshapeFunc(adjust);
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}