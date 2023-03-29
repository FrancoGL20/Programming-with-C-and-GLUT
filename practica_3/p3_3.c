#include <GL/glut.h>
#include <stdio.h>

int nVertices=14;
float letraSolida[][2]={{0,0},{1,0},{0,2.5},{1,2},{1.5,2.5},{2,2},{1.5,2.5},{2,3},{0,2.5},{1,3},{0,5},{1,4},{3,5},{3,4}};
int pos[2]={150,165};
enum direccion{arriba,abajo,izquierda,derecha,ninguna};
enum direccion dir=ninguna;

void dibujaLetra(int position[2],int escala){
    float letraEscaladaYMovida[nVertices][2];
    // escalar y mover letra
    for (int i = 0; i < nVertices; i++){
        letraEscaladaYMovida[i][0]=letraSolida[i][0]*escala+position[0];
        letraEscaladaYMovida[i][1]=letraSolida[i][1]*escala+position[1];
    }

    // dibujo de líneas
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < nVertices; i++){
        glVertex2fv(letraEscaladaYMovida[i]);
    }
    glEnd();
}

// Función que se ejecuta cuando se pulsa una tecla normal
void teclado(unsigned char tecla, int x, int y){ // tecla normal
    switch (tecla){
        case 27:
            exit(0); // Esc =>Salir del programa
        case 'd': 
            dir=ninguna;
            break;
        default:
            break;
    }
    glutPostRedisplay(); // Redibuja la ventana
}

// Función que se ejecuta cuando se pulsa una tecla especial
void teclaEspecial(int tecla, int x, int y){
    switch (tecla){
        case GLUT_KEY_UP: // PageUp (flecha arriba) => mover deadpool hacia arriba
            dir=arriba;
            break;
        case GLUT_KEY_DOWN: // PageDown (flecha abajo) => mover deadpool hacia abajo
            dir=abajo;
            break;
        case GLUT_KEY_LEFT: // Home (flecha izquierda) => mover deadpool hacia la izquierda
            dir=izquierda;
            break;
        case GLUT_KEY_RIGHT: // End (flecha derecha) => mover deadpool hacia la derecha
            dir=derecha;
            break;
        default:
            break;
    }
    glutPostRedisplay(); // Redibuja la ventana
}

void ajustar(int ancho, int alto){
    glClearColor(1.0,1.0,1.0,0.0); // color de fondo de ventana
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480); // la relacion aspecto de la ventana es 640*480
}

// Función que modifica la posición del dibujo cada ciertos milisegundos
void animaT(int v) {
    switch (dir) {
        case arriba:
            if (pos[1] < 480-150){
                pos[1] += 10;
            }
            break;
        case abajo:
            if (pos[1] > 0){
                pos[1] -= 10;
            }
            break;
        case izquierda:
            if (pos[0]+90 > 0){
                pos[0] -= 10;
            }else{
                pos[0]=640;
            }
            break;
        case derecha:
            if (pos[0] < 640){
                pos[0] += 10;
            }else{
                pos[0]=-90;
            }
            break;
        default:
            break;
    }
    glutTimerFunc(100, animaT, 0); 
    glutPostRedisplay();
}

void dibujar(void){
    glClear(GL_COLOR_BUFFER_BIT); // limpiar buffer de color

    glColor3ub(88, 207, 100); // cambio de color a verde
    dibujaLetra(pos,30);

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
    glutKeyboardFunc(teclado); // función de tecla normal
    glutSpecialFunc(teclaEspecial); // función de teclado especial
    glutTimerFunc(600, animaT, 0); // Para animar con un timer
    glutMainLoop();
    return 0;
}