#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define PI 3.14159265359

#include "tarea2_mandalorian.h"
#include "tarea2_deadpool.h"

void evaluaFuncion(double (*funcion)(double)){
    int amplitud = 220 / 4;
    int periodo = 640 / 3;
    int f;
    glColor3ub(2, 2, 245);
    glBegin(GL_LINE_STRIP);
    for (int i = (0 - periodo / 2) + 2; i <= (periodo / 2) + 4; i++){
        f = roundf(amplitud * ((*funcion)(((2 * PI) / periodo) * i)));
        f += roundf(amplitud);
        // hacer el dibujo
        glVertex2f(i + 530, f + 308);
    }
    glEnd();
    glColor3ub(0, 0, 0);
}

void dibujaTexto(void *tipo, char *s, int x, int y){
    glRasterPos2i(x, y);
    for (int i = 0; i < strlen(s); i++)
        glutBitmapCharacter(tipo, s[i]);
}

void ajusta(int ancho, int alto){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

// función para obtener las coordenadas de un circulo dividido
int **getCoords(int nPoints, int r){
    int **coords = (int **)malloc(nPoints * sizeof(int *)); // arreglo de coordenadas
    for (int i = 0; i < nPoints; i++){                                               // inicializar el arreglo
        coords[i] = (int *)malloc(2 * sizeof(int)); // cada coordenada tiene 2 valores
    }
    int x, y;
    int c = 0;
    for (int theta = 0; theta < 360; theta += (360 / nPoints)){
        x = r * cos(theta * (PI / 180));
        y = r * sin(theta * (PI / 180));
        coords[c][0] = x;
        coords[c][1] = y;
        c++;
    }

    // regresar el arreglo de coordenadas
    return coords;
}

// función para dibujar completo el circulo con líneas
void drawCircle(int posX0, int posY0, int r, int divs){
    int **coords = getCoords(divs, r);

    glLineWidth(1.0); // ancho de la línea
    // dibujo de líneas
    int c = 0;
    glBegin(GL_LINES);
    for (int i = 0; i < divs; i++){
        // para cada punto voy a dibujar una línea con los puntos siguientes
        for (int j = i + 1; j < divs; j++){
            glVertex2i(coords[i][0] + posX0, coords[i][1] + posY0);
            // printf("x: %d, y: %d, ", coords[i][0]+posX0, coords[i][1]+posY0);
            glVertex2i(coords[j][0] + posX0, coords[j][1] + posY0);
            // printf("x: %d, y: %d\n", coords[j][0]+posX0, coords[j][1]+posY0);
            c++;
        }
    }
    glEnd();
    // printf("Dibuje %d líneas\n",c);
}

// función para dibujar completa la curva parabolica con líneas
void drawParabolicCurve(int posX0, int posY0, int tam, int sep){
    int ejeXneg[tam][2], ejeYneg[tam][2];
    int ejeXpos[tam][2], ejeYpos[tam][2];
    glBegin(GL_LINES);
    // inicialización
    for (int x = 0; x < tam; x++){
        ejeXneg[x][0] = 0;
        ejeXneg[x][1] = (x * -sep);
        ejeXpos[x][0] = 0;
        ejeXpos[x][1] = (x * sep);
        ejeYneg[x][0] = (x * -sep);
        ejeYneg[x][1] = 0;
        ejeYpos[x][0] = (x * sep);
        ejeYpos[x][1] = 0;
    }
    // dibujo de líneas
    for (int i = 0; i < tam; i++){
        // superior izquierdo
        glColor3ub(188, 188, 5); // amarillo
        glVertex2i(ejeXpos[i][0] + posX0, ejeXpos[i][1] + posY0);
        glVertex2i(ejeYneg[tam - i - 1][0] + posX0, ejeYneg[tam - i - 1][1] + posY0);
        // superior derecho
        glColor3ub(61, 137, 37); // verde
        glVertex2i(ejeXpos[i][0] + posX0, ejeXpos[i][1] + posY0);
        glVertex2i(ejeYpos[tam - i - 1][0] + posX0, ejeYpos[tam - i - 1][1] + posY0);
        // inferior izquierdo
        glColor3ub(61, 137, 37); // verde
        glVertex2i(ejeXneg[i][0] + posX0, ejeXneg[i][1] + posY0);
        glVertex2i(ejeYneg[tam - i - 1][0] + posX0, ejeYneg[tam - i - 1][1] + posY0);
        // inferior derecho
        glColor3ub(188, 188, 5); // amarillo
        glVertex2i(ejeXneg[i][0] + posX0, ejeXneg[i][1] + posY0);
        glVertex2i(ejeYpos[tam - i - 1][0] + posX0, ejeYpos[tam - i - 1][1] + posY0);
    }
    glEnd();
}

void dibuja(void){
    int tam = 4; // tamaño del punto
    glClear(GL_COLOR_BUFFER_BIT);

    // LÍNEAS DIVISORAS *******************************************
    glLineWidth(2);
    glColor3ub(151, 65, 24);
    glBegin(GL_LINES);
    glVertex2i(0, 480 / 2);
    glVertex2i(640, 480 / 2);
    glVertex2i(640 / 3, 0);
    glVertex2i(640 / 3, 480);
    glVertex2i((640 / 3) * 2, 0);
    glVertex2i((640 / 3) * 2, 480);
    glEnd();

    // 1er RECUADRO ***********************************************
    glColor3ub(94, 33, 41);
    dibujaTexto(GLUT_BITMAP_HELVETICA_18, "Vargas", 70, 260);

    FILE *poli;
    char nombre[] = "tarea2_dragon.dat";
    int n_lineas, n_vertices, x, y;
    poli = fopen(nombre, "r");
    if (poli == NULL){
        printf("No se puede abrir el archivo %s\n", nombre);
    }
    fscanf(poli, "%d", &n_lineas);
    // printf("Numero de lineas: %d\n", n_lineas);
    for (int i = 0; i < n_lineas; ++i){
        fscanf(poli, "%d", &n_vertices);
        // printf("Linea %d: %d vertices -> ",i+1,n_vertices);
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < n_vertices; ++j){
            fscanf(poli, "%d %d", &x, &y);
            // printf("(%d,%d)",x,y);
            glVertex2i(x + 20, -y + 465);
        }
        // printf("\n");
        glEnd();
    }
    fclose(poli);

    // 2do RECUADRO ***********************************************
    glColor3ub(182, 37, 192);

    drawCircle(319, 360, 90, 15);
    drawCircle(416 - 21, 480 - 30, 20, 8);
    drawCircle(213 + 25, 240 + 30, 20, 6);
    drawCircle(416 - 21, 240 + 30, 20, 4);
    drawCircle(213 + 25, 480 - 30, 20, 9);

    // 3er RECUADRO ***********************************************
    glLineWidth(3);
    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2i((640 / 6) * 5, 480 / 2);
    glVertex2i((640 / 6) * 5, 480);
    glVertex2i((640 / 3) * 2, (480 / 4) * 3);
    glVertex2i(640, (480 / 4) * 3);
    glEnd();

    glColor3ub(0, 0, 255);

    glLineWidth(1);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xCCCC);
    glBegin(GL_LINES);

    for (int i = ((640 / 6) * 4) + 5; i < 640; i += 20){
        glVertex2i(i, 480 / 2);
        glVertex2i(i, 480);
    }
    // líneas horizontales
    for (int i = (480 / 2); i < 480; i += 20){
        glVertex2i((640 / 3) * 2, i);
        glVertex2i(640, i);
    }
    glEnd();
    glDisable(GL_LINE_STIPPLE);

    glLineWidth(3);
    evaluaFuncion(cos);
    glLineWidth(1);

    // 4to RECUADRO ***********************************************
    glPointSize(tam);
    glBegin(GL_POINTS);
    for (int i = 0; i < ALTO; i++)
        for (int j = 0; j < ANCHO; j++){
            glColor3ubv(paleta1[mandalorian[i][j]]);
            glVertex2i(0 + j * tam, 125 - i * tam);
        }
    glEnd();


    // 4to RECUADRO ***********************************************
    tam=3;
    glPointSize(tam);
    glBegin(GL_POINTS);
    for (int i = 0; i < ALTOF; i++)
        for (int j = 0; j < ANCHOF; j++){
            glColor3ubv(paleta2[deadpool[i][j]]);
            glVertex2i(120+ j * tam, 220 - i * tam);
        }
    glEnd();

    // 5to RECUADRO ***********************************************
    drawParabolicCurve(320, 120, 25, 4);
    drawParabolicCurve(385, 50, 4, 8);
    drawParabolicCurve(255, 50, 5, 5);
    drawParabolicCurve(385, 175, 7, 4);
    drawParabolicCurve(255, 175, 9, 4);

    // 6to RECUADRO ***********************************************
    glColor3ub(239, 142, 52);
    dibujaTexto(GLUT_BITMAP_HELVETICA_18, "Gutierrez", 495, 200);

    FILE *oso;
    char nombre2[] = "./tarea2_pato.dat";
    oso = fopen(nombre2, "r");
    if (oso == NULL){
        printf("No se puede abrir el archivo %s\n", nombre2);
    }
    fscanf(oso, "%d", &n_lineas);
    // printf("Numero de lineas: %d\n", n_lineas);
    for (int i = 0; i < n_lineas; i++){
        fscanf(oso, "%d", &n_vertices);
        // printf("Numero de vertices: %d\n",n_vertices);
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < n_vertices; j++){
            fscanf(oso, "%d %d", &x, &y);
            glVertex2i(x * 6 + 450, y * 6 + 10);
        }
        glEnd();
    }
    fclose(oso);

    // ENVÍO DE LOS DIBUJADO A LA PANTALLA ************************
    glFlush();
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Tarea 2");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutMainLoop();
    return 0;
}