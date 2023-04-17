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
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "./deadpool.h"
#include "./mandalorian.h"

// Definiciones de constantes
#define anchoTextura 32
#define altoTextura 32

// Variables globales
float alto_ventana=370;
float ancho_ventana=800;
GLuint texturas[5]; // Id's de las texturas
char gano[20]="Ganaste!";
GLubyte dp[altoTextura][anchoTextura][3]; 
GLubyte md[altoTextura][anchoTextura][3]; 
int text_1, text_2, text_3;

// Carga imagen de archivo data y la convierte en textura de OpenGL
void cargaTextura_data(int ancho, int alto, const char *archivo, GLuint *text, int id_textura, GLboolean esfera){
    unsigned char *datos;
    FILE *file = fopen(archivo, "rb");
    if (file == NULL)    {
        printf("archivo no encontrado");
        exit(1);
    }
    datos = (unsigned char *)malloc(ancho * alto * 3); // reservar memoria para los datos
    fread(datos, ancho * alto * 3, 1, file);
    fclose(file);

    glGenTextures(id_textura, text);
    glBindTexture(GL_TEXTURE_2D, *text);
    if (esfera)    {
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, datos);
}

// Dibujar texto en pantalla
void dibujaTexto(void *tipo, char *s, float x, float y){
    glRasterPos2f(x, y);
    for (int i = 0; i < strlen(s); i++)
        glutBitmapCharacter(tipo, s[i]);
}

void dibuja(void){
    glClear(GL_COLOR_BUFFER_BIT);

    // Primera textura
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturas[text_1]);
    glBegin(GL_QUADS);
        int x=50;
        int y=50;
        int dim=200;

        // Arriba, izquierda
        glTexCoord2f(0.0, 0.0);
        glVertex3f(x, y+dim, 0);

        // Arriba, derecha
        glTexCoord2f(1.0, 0.0);
        glVertex3f(x+dim, y+dim, 0);

        // Abajo, derecha
        glTexCoord2f(1.0, 1.0);
        glVertex3f(x+dim, y, 0);

        // Abajo, izquierda
        glTexCoord2f(0.0, 1.0);
        glVertex3f(x, y, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Segunda textura
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturas[text_2]);
    glBegin(GL_QUADS);
        x=x+200+50;

        // Arriba, izquierda
        glTexCoord2f(0.0, 0.0);
        glVertex3f(x, y+dim, 0);

        // Arriba, derecha
        glTexCoord2f(1.0, 0.0);
        glVertex3f(x+dim, y+dim, 0);

        // Abajo, derecha
        glTexCoord2f(1.0, 1.0);
        glVertex3f(x+dim, y, 0);

        // Abajo, izquierda
        glTexCoord2f(0.0, 1.0);
        glVertex3f(x, y, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Tercera textura
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturas[text_3]);
    glBegin(GL_QUADS);
        x=x+200+50;

        // Arriba, izquierda
        glTexCoord2f(0.0, 0.0);
        glVertex3f(x, y+dim, 0);

        // Arriba, derecha
        glTexCoord2f(1.0, 0.0);
        glVertex3f(x+dim, y+dim, 0);

        // Abajo, derecha
        glTexCoord2f(1.0, 1.0);
        glVertex3f(x+dim, y, 0);

        // Abajo, izquierda
        glTexCoord2f(0.0, 1.0);
        glVertex3f(x, y, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Dibujar texto
    glColor3f(0, 0, 0);
    if (text_1==text_2 && text_2==text_3)
        dibujaTexto(GLUT_BITMAP_HELVETICA_18, "Ganaste!!", 370, 300);

    glFlush();
}

void ajusta(int ancho, int alto){
    float color=0.9;
    glClearColor(color, color, color, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, ancho_ventana, 0, alto_ventana, -4, 4);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Función para cargar todas las texturas que se usarán
void carga_texturas(){
    // Texturas de imagenes .data
    cargaTextura_data(200, 200, "bear_polar.data", &texturas[0], 0, GL_FALSE);
    cargaTextura_data(200, 200, "bear_brown.data", &texturas[1], 1, GL_FALSE);
    cargaTextura_data(200, 200, "bear_panda.data", &texturas[2], 2, GL_FALSE);

    // Texturas procedurales
    // Deadpool
    for (int i = 0; i < altoTextura; i++) {
        for (int j = 0; j < anchoTextura; j++) {
            dp[i][j][0] = (i < ALTO_D && j < ANCHO_D) ? paleta_dp[deadpool[i][j]][0] : paleta_dp[0][0];
            dp[i][j][1] = paleta_dp[(i < ALTO_D && j < ANCHO_D) ? deadpool[i][j] : 0][1];
            dp[i][j][2] = paleta_dp[(i < ALTO_D && j < ANCHO_D) ? deadpool[i][j] : 0][2];
        }
    }
    glGenTextures(3, &texturas[3]);
    glBindTexture(GL_TEXTURE_2D, texturas[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // Cuando se hace más grande un objeto, se usa GL_NEAREST
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // Cuando se hace más pequeño un objeto, se usa GL_NEAREST
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // Selecciona el modo de mezcla de colores
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Modo de repetición de la textura en el eje X
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Modo de repetición de la textura en el eje Y
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, anchoTextura, altoTextura,
                0, GL_RGB, GL_UNSIGNED_BYTE, dp); // Parametros: Tipo de textura, nivel de detalle, formato de color, ancho, alto, borde, formato de color, tipo de dato, datos de la textura
    
    // Mandalorian
    for (int i = 0; i < altoTextura; i++) {
        for (int j = 0; j < anchoTextura; j++) {
            md[i][j][0] = (i < ALTO_M && j < ANCHO_M) ? paleta_md[mandalorian[i][j]][0] : paleta_md[0][0];
            md[i][j][1] = paleta_md[(i < ALTO_M && j < ANCHO_M) ? mandalorian[i][j] : 0][1];
            md[i][j][2] = paleta_md[(i < ALTO_M && j < ANCHO_M) ? mandalorian[i][j] : 0][2];
        }
    }
    glGenTextures(4, &texturas[4]); 
    glBindTexture(GL_TEXTURE_2D, texturas[4]); // Selecciona la textura 4
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // Cuando se hace más grande un objeto, se usa GL_NEAREST
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // Cuando se hace más pequeño un objeto, se usa GL_NEAREST
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // Selecciona el modo de mezcla de colores
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Modo de repetición de la textura en el eje X
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Modo de repetición de la textura en el eje Y
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, anchoTextura, altoTextura,
                0, GL_RGB, GL_UNSIGNED_BYTE, md); // Parametros: Tipo de textura, nivel de detalle, formato de color, ancho, alto, borde, formato de color, tipo de dato, datos de la textura
}

// Función que controla las teclas normales
void teclas_n(unsigned char key, int x, int y){
    // tecla escape
    if (key == 27) {
        for (int i = 0; i < 4; i++)
            glDeleteTextures(i, &texturas[i]);
        exit(0);
    }
    // tecla enter
    if (key == 13) {
        text_1=rand()%5;
        text_2=rand()%5;
        text_3=rand()%5;
        glutPostRedisplay();
    }
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitWindowSize(ancho_ventana, alto_ventana);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("P7_4");
    carga_texturas();
    text_1=rand()%5;
    text_2=rand()%5;
    text_3=rand()%5;
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclas_n);
    glutMainLoop();
    return 0;
}