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
int dx, dy;
int contador = 0;
int tope = 360 * 3;
GLboolean punto_colocado = GL_FALSE;
GLboolean animando = GL_FALSE;

// Función para dibujar una letra
void dibujaLetra(float vertices[][2],int n_vertices,GLboolean solido,int position[2],int escala){
    float letraEscaladaYMovida[n_vertices][2];
    // escalar y mover letra
    for (int i = 0; i < n_vertices; i++){
        letraEscaladaYMovida[i][0]=vertices[i][0]*escala+position[0];
        letraEscaladaYMovida[i][1]=vertices[i][1]*escala+position[1];
    }

    // recorrer arreglo e imprimir el vertice
    glColor3ub(88, 207, 100);

    // dibujo de líneas
    glBegin(solido?GL_QUAD_STRIP:GL_LINE_LOOP);
    for (int i = 0; i < n_vertices; i++){
        glVertex2fv(letraEscaladaYMovida[i]);
    }
    glEnd();
}

// Función para manejar el redimensionamiento de la ventana
void ajusta(int ancho, int alto) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

// Función para manejar los eventos del ratón
void raton(int boton, int estado, int x, int y) {
    int alto_ventana = 480;
    if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) { // Pulsación del botón izquierdo
        dx = x;
        dy = alto_ventana - y;
        punto_colocado = GL_TRUE;
    }
    glutPostRedisplay();
}

// Función para manejar las teclas normales del teclado
void teclado(unsigned char tecla, int x, int y) {
    if (tecla == 27) // Esc: salir del programa
        exit(0);
    if ((tecla == 'r' || tecla == 'R') && punto_colocado) { // r, R: comenzar la animación
        animando = GL_TRUE;
    }
}

// Función para dibujar la escena
void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT); // Borrar la pantalla

    // dibujo del punto
    glColor3f(1, 0, 0);
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2i(dx, dy);
    glEnd();

    // definición de caracteristicas de la letra
    int nVertices=14;
    float letraSolida[][2]={{0,0},{1,0},{0,2.5},{1,2},{1.5,2.5},{2,2},{1.5,2.5},{2,3},{0,2.5},{1,3},{0,5},{1,4},{3,5},{3,4}};
    GLboolean solido=GL_TRUE;
    int pos[2]={260,165};

    // dibujo de la letra
    if (punto_colocado && animando) { // animación
        glPushMatrix();
        glTranslatef(dx, dy, 0);
        glRotatef(contador, 0.0, 0.0, 1.0);
        glTranslatef(-dx, -dy, 0);
        glColor3f(0, 1, 0);
        dibujaLetra(letraSolida,nVertices,solido,pos,30);
        glPopMatrix();
    } else { // dibujo normal
        glColor3f(0, 1, 0);
        dibujaLetra(letraSolida,nVertices,solido,pos,30);
    }

    glutSwapBuffers(); // Intercambio de buffers
}

// Función para manejar la animación
void anima() {
    if (contador <= tope && animando) { // animación
        contador++;
    } else { // parar la animación
        animando = GL_FALSE;
        contador = 0;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("P 4.2");
    glutDisplayFunc(dibuja);
    glutIdleFunc(anima);
    glutMouseFunc(raton);
    glutKeyboardFunc(teclado);
    glutReshapeFunc(ajusta);
    glutMainLoop();
    return 0;
}