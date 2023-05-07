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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Variables globales
int n = 4;
int tam_pantalla = 700;
enum mod {edicion, seleccion, visualizacion};
enum mod modo = seleccion;
GLfloat girax = 15, giray = -30;
GLint punto_seleccionado[2]={0,0};
GLboolean malla = GL_FALSE, ejes = GL_FALSE;
GLfloat ptosctl[4][4][3] = {
    {{-8, -8, 0}, {-2.665, -8, 0}, {2.665, -8, 0}, {8, -8, 0}},
    {{-8, -2.665, 0}, {-2.665, -2.665, 0}, {2.665, -2.665, 0}, {8, -2.665, 0}},
    {{-8, 2.665, 0}, {-2.665, 2.665, 0}, {2.665, 2.665, 0}, {8, 2.665, 0}},
    {{-8, 8, 0}, {-2.665, 8, 0}, {2.665, 8, 0}, {8, 8, 0}}};

// Cambiar rango
float cambia_rango(float orig_min, float orig_max, float new_min, float new_max, float value) {
    return (value - orig_min) * (new_max - new_min) / (orig_max - orig_min) + new_min;
}

// Función que cambia el modo de visualización
void cambia_modo(enum mod m) {
    modo = m;
    switch (modo) {
        case edicion:
            printf("Modo edición activado\n");
            break;
        case seleccion:
            printf("Modo selección activado\n");
            break;
        case visualizacion:
            printf("Modo visualización activado\n");
            malla = GL_FALSE;
            ejes = GL_FALSE;
            break;
    }
    glutPostRedisplay();
}

// Rotacion XY y Zoom
void mover(void) {
    glRotated(giray, 0.0, 1.0, 0.0);
    glRotated(girax, 1.0, 0.0, 0.0);
}

// Función que se ejecuta cuando se pulsa un botón del ratón
void raton(int boton, int estado, int x, int y){
    // botón izquierdo del mouse cuando se está en modo selección
    if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN && modo == seleccion) {
        float x_raton = cambia_rango(0, tam_pantalla, -12, 12, x);
        float y_raton = - cambia_rango(0, tam_pantalla, -12, 12, y);
        float menor_distancia = 100000;
        for (int i = 0; i < n; i++) {
            for (int  j = 0; j < n; j++) {
                int x_punto = ptosctl[i][j][0];
                int y_punto = ptosctl[i][j][1];
                float d = sqrt(pow(x_raton - x_punto, 2) + pow(y_raton - y_punto, 2));
                if (d < menor_distancia) {
                    menor_distancia = d;
                    punto_seleccionado[0] = i;
                    punto_seleccionado[1] = j;
                }
            }
        }
        cambia_modo(edicion);
    }
    glutPostRedisplay();
}

// Crear malla
void creaMalla(int long_eje) {
    glColor3f(1.0, 0.0, 0.0); // Color rojo
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
    glColor3f(0.0, 0.0, 0.0); // color negro
    glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(11.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 11.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 11.0);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex3f(11.0, 0.0, 0.0); // color rojo
        glVertex3f(10.5, 0.0, -.50);
        glVertex3f(10.5, 0.0, .50);
        glColor3f(0.25, 1, 0.25); // color verde
        glVertex3f(0.0, 11.0, 0.0);
        glVertex3f(-.50, 10.5, 0.0);
        glVertex3f(.50, 10.5, 0.0);
        glColor3f(0.25, 0.25, 1.0); // color azul
        glVertex3f(0.0, 0.0, 11.0);
        glVertex3f(-.50, 0.0, 10.5);
        glVertex3f(.50, 0.0, 10.5);
    glEnd();
}

// Función que inicializa la textura
void inicializa(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ptosctl[0][0][0]);

    glEnable(GL_MAP2_VERTEX_3);
}

// Funciones con Teclas
void tecl_norm(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
        case 'm': // activa/desactiva la malla
            malla = !malla;
            break;
        case 'c': // activa/desactiva los ejes
            ejes = !ejes;
            break;
        case 's': // activa el modo selección
            cambia_modo(seleccion);
            break;
        case 'e': // activa el modo edicion
            cambia_modo(edicion);
            break;
        case 'v': // activa el modo visualización
            cambia_modo(visualizacion);
            break;
        default:
            break;
    }
    if (modo == edicion) {
        switch (key) {
            case '4': // mueve el punto de control seleccionado en -x
                    ptosctl[punto_seleccionado[0]][punto_seleccionado[1]][0] -= 0.5;
                break;
            case '7': // mueve el punto de control seleccionado en +x
                    ptosctl[punto_seleccionado[0]][punto_seleccionado[1]][0] += 0.5;
                break;
            case '5': // mueve el punto de control seleccionado en -y
                    ptosctl[punto_seleccionado[0]][punto_seleccionado[1]][1] -= 0.5;
                break;
            case '8': // mueve el punto de control seleccionado en +y
                    ptosctl[punto_seleccionado[0]][punto_seleccionado[1]][1] += 0.5;
                break;
            case '6': // mueve el punto de control seleccionado en -z
                    ptosctl[punto_seleccionado[0]][punto_seleccionado[1]][2] -= 0.5;
                break;
            case '9': // mueve el punto de control seleccionado en +z
                    ptosctl[punto_seleccionado[0]][punto_seleccionado[1]][2] += 0.5;
                break;
        }
        glDisable(GL_MAP2_VERTEX_3);
        glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ptosctl[0][0][0]);
        glEnable(GL_MAP2_VERTEX_3);
    }
    glutPostRedisplay();
}

// Funciones con Teclas Especiales
void tec_esp(int key, int x, int y) {
    if (modo != seleccion){
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
    }
    glutPostRedisplay();
}

void dibuja(void) {
    int i, j;
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
        if(modo == seleccion){ 
            glColor3f(1.0, 0.0, 0.0); // Color rojo
        } else if (modo == edicion || modo == visualizacion) {
            mover();
            if (malla)
                creaMalla(10);
            if (ejes)
                creaEjes();
            glColor3f(0.2, 0.2, 0.2); // Color gris oscuro
        }

        // Superficie de Bezier
        glLineWidth(2);
        glMapGrid2f(20, 0, 1, 20, 0, 1); // 20x20 puntos de control
        glEvalMesh2(GL_LINE, 0, 20, 0, 20); // 20x20 puntos de control

        // Puntos de control
        if(modo != visualizacion){
            glPointSize(7.0);
            glColor3f(0.0, 0.0, 1.0); // Color azul
            glBegin(GL_POINTS);
                for (i = 0; i < 4; i++){
                    for (j = 0; j < 4; j++){
                        // Si el punto actual es el punto a editar
                        if(punto_seleccionado[0]==i && punto_seleccionado[1]==j){
                            glEnd();

                            glColor3f(1.0, 0.0, 0.0);
                            
                            glPushMatrix();
                                glTranslatef(ptosctl[i][j][0], ptosctl[i][j][1], ptosctl[i][j][2]);
                                glutSolidSphere(0.3, 10, 10);
                                glScalef(0.2, 0.2, 0.2);
                                creaEjes();
                            glPopMatrix();


                            glColor3f(0.0, 0.0, 1.0);
                            // glPointSize(7.0);
                            glBegin(GL_POINTS);
                        } else {
                            glVertex3fv(&ptosctl[i][j][0]);
                        }
                    }
                }
            glEnd();
        }
    glPopMatrix();
    glFlush();
}
void ajusta(int ancho, int alto) {
    glViewport(0, 0, ancho, alto);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-12.0, 12.0, -12.0, 12.0, -20.0, 25.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(tam_pantalla, tam_pantalla);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("P 8_2");
    inicializa();
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta); // función de ajuste
    glutKeyboardFunc(tecl_norm); // función de teclas normales
    glutSpecialFunc(tec_esp); // función de teclas especiales
    glutMouseFunc(raton); // función de ratón
    glutMainLoop();
    return 0;
}