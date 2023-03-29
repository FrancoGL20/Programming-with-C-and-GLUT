#include <GL/glut.h>
#include <stdio.h>
#include <string.h>

void ajusta(int ancho, int alto){
    // color de fondo
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // la relacion aspecto de la ventana es 640*480
    gluOrtho2D(0,640,0,480); 
}
void dibuja(void){
    glClear(GL_COLOR_BUFFER_BIT); // limpiar buffer de color
    
    glColor3ub(150, 150, 150); // cambio de color
    FILE *oso;
    char nombre[] = "./files/tarea2_pato.dat";
    int n_lineas, n_vertices, x, y;
    oso = fopen(nombre, "r");
    if (oso == NULL){
        printf("No se puede abrir el archivo %s\n", nombre);
    }
    fscanf(oso, "%d", &n_lineas);
    printf("Numero de lineas: %d\n", n_lineas);
    for (int i = 0; i < n_lineas; i++){
        fscanf(oso, "%d", &n_vertices);
        printf("Numero de vertices: %d\n",n_vertices);
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < n_vertices; j++){
            fscanf(oso, "%d %d", &x, &y);
            glVertex2i((x)*7+450, (y)*7);
        }
        glEnd();
    }
    fclose(oso);

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

    // enviarlo a pantalla
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480); // tamaño de la ventana que se va a obtener
    glutInitWindowPosition(100, 150); // posición de la ventana
    glutCreateWindow("Ejercicio 5"); // titulo de la ventana
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutMainLoop();
    return 0;
}