#include <GL/glut.h>

void ajusta(int ancho, int alto){
    glClearColor(1.0,1.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480); // la relacion aspecto de la ventana es 640*480
}
void dibuja(void){
    // limpiar buffer
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3ub(254, 0, 0); // cambio de color
    // cuadrilatero
    glBegin(GL_QUADS);
    	glVertex2i(100+85+20,400); // arr izq
    	glVertex2i(180+85-20,400); // arr der
    	glVertex2i(180+85+30,300); // ab der
    	glVertex2i(100+85-30,300); // ab izq
    glEnd();
    
    glColor3ub(166, 210, 89); // cambio de color
    glLineWidth(3.0); // ancho de línea
    // pentagono wireframe
    glBegin(GL_LINE_LOOP);
    	glVertex2i(100,200); // arr izq
    	glVertex2i(140,250); // arr cen
    	glVertex2i(180,200); // arr der
    	glVertex2i(180,100); // ab der
    	glVertex2i(100,100); // ab izq
    glEnd();
    glLineWidth(1.0); // ancho de linea
    
    glColor3ub(168, 73, 141); // cambio de color
    // pentagono solido
    glBegin(GL_POLYGON);
    	glVertex2i(100+170,200); // arr izq
    	glVertex2i(140+170,250); // arr cen
    	glVertex2i(180+170,200); // arr der
    	glVertex2i(180+170,100); // ab der
    	glVertex2i(100+170,100); // ab izq
    glEnd();
    
    glColor3ub(115, 99, 73); // cambio de color
    glLineWidth(3.0); // ancho de linea
    glEnable(GL_LINE_STIPPLE); // habilitar punteado de l�nea
    glLineStipple(1,0xFE38); // patrón del dibujo
    // pentagono punteado
    glBegin(GL_LINE_LOOP);
    	glVertex2i(100+340,200); // arr izq
    	glVertex2i(140+340,250); // arr cen
    	glVertex2i(180+340,200); // arr der
    	glVertex2i(180+340,100); // ab der
    	glVertex2i(100+340,100); // ab izq
    glEnd();
    glDisable(GL_LINE_STIPPLE); // deshabilitar punteado de l�nea
    glLineWidth(1.0); // ancho de línea
    
    // dibujar con quad strip
    glBegin(GL_TRIANGLE_FAN);
    	glColor3ub(220, 220, 220); // cambio de color
    	glVertex2i(140+340-80,150+200); // cen
    	glColor3ub(255, 0, 0); // cambio de color
    	glVertex2i(100+340-80,100+200); // ab izq
    	glColor3ub(0, 255, 0); // cambio de color
    	glVertex2i(100+340-80,200+200); // arr izq
    	glColor3ub(0, 0, 255); // cambio de color
    	glVertex2i(140+340-80,250+200); // arr cen
    	glColor3ub(130, 50, 50); // cambio de color
    	glVertex2i(180+340-80,200+200); // arr der
    	glColor3ub(50,130,50); // cambio de color
    	glVertex2i(180+340-80,100+200); // ab der
    	glColor3ub(80,60,150); // cambio de color
    	glVertex2i(100+340-80,100+200); // ab izq
    glEnd();
    
    
    // enviarlo a pantalla
    glFlush();
}
int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480); // tamaño de la ventana que se va a obtener
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Practica 1.1"); // titulo de la ventana
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutMainLoop();
    return 0;
}
