#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// función para crear un arreglo con números del 0 al 7 en orden aleatorio sin repetir
int *randomArray() {
    // ajustar semilla de aleatorio a la hora actual
    time_t t;
    srand((unsigned)time(&t));

    int *array = (int *)malloc(6 * sizeof(int)); // arreglo de 6 elementos
    int i = 0;
    while (i < 6) { // se repite hasta que se llenen los 6 elementos
        int random = rand() % 8; // número aleatorio entre 0 y 7
        int j = 0;
        while (j < i) { // verifica que no se repita el número
            if (array[j] == random) {
                break;
            }
            j++;
        }
        if (j == i) { // si no se repite se agrega al arreglo
            array[i] = random;
            i++;
        }
    }
    return array;
}

void drawText(void *type, int posX, int posY) {
    // apertura de archivo
    FILE *fileToPrint;
    char name[] = "./files/practica1_4.txt";
    fileToPrint = fopen(name, "r");
    if (fileToPrint == NULL) {
        printf("No se puede abrir el archivo %s\n", name);
        exit(1);
    }

    char c[100]; // arreglo para almacenar cada linea del archivo
    int space = 20; // espacio entre lineas
    glRasterPos2i(posX, posY); // posicion inicial del cursor
    while (fgets(c, 100, fileToPrint)) { // lee linea por linea
        printf("%s", c);
        for (int i = 0; i < strlen(c); i++) { // recorre cada caracter de la linea
            glutBitmapCharacter(type, c[i]); // imprime caracter por caracter
        }
        posY = posY - space;
        glRasterPos2i(posX, posY); // posiciona el cursor
    }
    printf("\n");

    fclose(fileToPrint); // cierre de archivo
}
void adjust(int width, int height) {
    // color de fondo
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // la relacion aspecto de la ventana es 640*480
    gluOrtho2D(0, 640, 0, 480);
}
void draw(void) {
    glClear(GL_COLOR_BUFFER_BIT); // limpiar buffer de color

    float colors[][3] = {
        {1.0, 0.0, 0.0},
        {1, 1, 0},
        {0.0, 0.0, 0.0},
        {0.533333333333333, 0.745098039215686, 0.396078431372549},
        {0.054901960784314, 0.054901960784314, 1.0},
        {0.745098039215686, 0.250980392156863, 0.498039215686275},
        {0.47843137254902, 0.329411764705882, 0.219607843137255},
        {0.325490196078431, 0.713725490196078, 0.619607843137255},
    };

    int *randomColors = randomArray();

    // arreglo de posiciones de los textos
    int positions[][2] = {
        {100, 400},
        {180, 300},
        {260, 200},
        {250, 400},
        {330, 300},
        {410, 200},
    };

    // dibujo de 6 textos
    for (int i = 0; i < 6; i++) {
        glColor3fv(colors[randomColors[i]]); // color del dibujo
        drawText(GLUT_BITMAP_HELVETICA_18, positions[i][0],positions[i][1]); // dibujo del texto
    }

    // enviarlo a pantalla
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);     // tamaño de la ventana que se va a obtener
    glutInitWindowPosition(100, 150); // posición de la ventana
    glutCreateWindow("Practica 1.4"); // titulo de la ventana
    glutReshapeFunc(adjust);
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}
