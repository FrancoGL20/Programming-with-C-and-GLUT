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
#include <math.h>

// Variables globales
GLfloat girax = 50, giray = 45;
float relacionAspecto = 1.6;
float x,y,z;
int a=2,b=3;
int c=20;
float t=0.2*3.141592653589;
int anchog, altog;
float aspectoDeseado=1.6; // Nunca se modificará
float aspectoActual;

// Por cada punto de la circunferencia se dibujan 8 puntos simetricos
void dibuja8Puntos(int x, int y, int x0, int y0){
    glVertex2i(x0+x,y0+y);
    glVertex2i(x0-x,y0+y);
    glVertex2i(x0+x,y0-y);
    glVertex2i(x0-x,y0-y);
    glVertex2i(x0+y,y0+x);
    glVertex2i(x0-y,y0+x);
    glVertex2i(x0+y,y0-x);
    glVertex2i(x0-y,y0-x);
}

// función de circulo de breseham que reciba el centro y el radio y dibuje el circulo
void circuloBreseham(int x0, int y0, int R){
    // x0 y y0 son las coordenadas del centro del circulo
    int x=0, y=R;
    int d=3-2*R;
    glBegin(GL_POINTS);
    while(x<=y){
        dibuja8Puntos(x,y,x0,y0);
        if(d<0){
            d=d+4*x+6;
        }else{
            d=d+4*(x-y)+10;
            y--;
        }
        x++;
    }
    glEnd();
}

//   Rotacion XY y Zoom
void mover(void) {
    glRotated(girax, 1.0, 0.0, 0.0);
    glRotated(giray, 0.0, 1.0, 0.0);
}

// Dibujo de función
void dibujaFuncion(int len,float salto){
    float x,y,z;
    for (x=-len;x<=len;x+=salto){
        // dibujo de líneas
        glBegin(GL_LINE_STRIP);
        for (z=-len;z<=len;z+=salto){
            y=12*(sin(sqrt(x*x+z*z))/sqrt(x*x+z*z));
            glVertex3f(x,y,z);
        }
        glEnd();
    }
    for (z=-len;z<=len;z+=salto){
        // dibujo de líneas
        glBegin(GL_LINE_STRIP);
        for (x=-len;x<=len;x+=salto){
            y=12*(sin(sqrt(x*x+z*z))/sqrt(x*x+z*z));
            glVertex3f(x,y,z);
        }
        glEnd();
    }
}

void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float ancho,alto;
    float espaciadox,espaciadoy;

    // ----------------- Líneas divisorias ----------------- //
    glViewport(0, 0, anchog,altog); // tamaño y posición de la ventana
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, -1, 1); // relación de aspecto
    glColor3f(0.5, 0.3, 0.0);
    glBegin(GL_LINES);
        glVertex2f(0.5, 0.0);
        glVertex2f(0.5, 1.0);
        glVertex2f(1.0, 0.5);
        glVertex2f(0.0, 0.5);
    glEnd();

    // -------------- Corrección de aspecto ---------------- //
    if (aspectoDeseado <= aspectoActual) { // si la ventana es más ancha que la imagen
        alto=altog/2;
        ancho=alto*aspectoDeseado;
        espaciadox=(anchog/2-ancho)/2;
    }else{ // si la ventana es más alta que la imagen
        ancho=anchog/2;
        alto=ancho/aspectoDeseado;
        espaciadoy=(altog/2-alto)/2;
    }

    // ---------------------- Vista 1 ---------------------- //
    glViewport(anchog/2+espaciadox, altog/2+espaciadoy, ancho, alto); // tamaño y posición de la ventana
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-16, 16, -16, 16, -20, 20); // relación de aspecto
    glPushMatrix();
        mover();
        glColor3f(0.0, 0.5, 0.0);
        dibujaFuncion(10,0.4);
    glPopMatrix();

    // ---------------------- Vista 2 ---------------------- //
    glViewport(anchog/2+espaciadox, 0+espaciadoy, ancho,alto); // tamaño y posición de la ventana
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-768/2, 768/2, -240, 240, -20, 20); // relación de aspecto
    glColor3f(0.5, 0.0, 0.5);
    circuloBreseham(0,0,200);

    // ---------------------- Vista 3 ---------------------- //
    glViewport(0+espaciadox,0+espaciadoy,ancho,alto); // tamaño y posición de la ventana
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-13, 13, -13, 13, -30, 30); // relación de aspecto
    glPushMatrix();
        mover();
        glRotatef(90,1,0,0);
        glScalef(2,2,2);
        glColor3f(1.0, 0.5, 0.0);
        glBegin(GL_LINE_STRIP);
        for (int i=0;i<1000;i++){
            x=(a*sin(c*t)+b)*cos(t);
            y=(a*sin(c*t)+b)*sin(t);
            z=a*cos(c*t);
            glVertex3f(x,y,z);
            t+=0.01;
        }
        glEnd();
    glPopMatrix();

    // ---------------------- Vista 4 ---------------------- //
    glViewport(0+espaciadox, altog/2+espaciadoy, ancho, alto);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3.5, 3.5, -1.4, 1.4, -1, 1); // relación de aspecto
    // líneas divisoras de los ejes x y y
    glColor3f(0.5, 0.3, 0.0);
    glBegin(GL_LINES);
        glVertex2f(0.0, -1.2);
        glVertex2f(0.0, 1.2);
        glVertex2f(-3.3, 0.0);
        glVertex2f(3.3, 0.0);
    glEnd();
    // dibujar la función seno
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_STRIP);
        for (float x=-3.1416;x<=3.1416;x+=0.01)
            glVertex2f(x,sin(x));
    glEnd();

    // --------------- Intercambio de buffers --------------- //
    glutSwapBuffers();
}

// Funciones con Teclas
void teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
        default:
            break;
    }
    glutPostRedisplay();
}

// Ajustar la ventana, ancho y alto son el tamaño de la ventana y se llama a esta función cuando se cambia el tamaño de la ventana
void ajusta(int ancho, int alto) {
    glClearColor(1.0, 1.0, 1.0, 0.0); // color de fondo
    glEnable(GL_DEPTH_TEST);          // activa el Z-buffer
    glMatrixMode(GL_MODELVIEW);     // matriz de modelado
    glLoadIdentity();
    anchog = ancho;
    altog = alto;
    aspectoActual = (float)ancho/alto;
}

int main(int argc, char **argv) {
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(480*1.6,480);
    glutInit(&argc, argv);
    glutCreateWindow("P5.4");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
    glutMainLoop();
    return 0;
}
