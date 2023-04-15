#include <GL/glut.h>

// Puntos de control de la curva de Bezier
GLfloat ptosctl[4][3] = {{-6.0, 7.0, 0.0}, {9.0, -9.0, 0.0}, {-9.0, -9.0, 0.0}, {5.0, 8.0, 0.0}};

void inicializa(void){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    // Se define la curva de Bezier con los puntos de control ptosctl
    glMap1f(GL_MAP1_VERTEX_3, 0, 1, 3, 4, &ptosctl[0][0]);
    // Se habilita el uso de la curva de Bezier
    glEnable(GL_MAP1_VERTEX_3);
}
void dibuja(void){
    int i;
    glClear(GL_COLOR_BUFFER_BIT);

    // curva de bezier
    glLineWidth(4);
    glColor3f(0.0, 0.0, 0.0);
    glMapGrid1f(30, 0, 1); // Se definen 30 segmentos en el intervalo [0,1]
    glEvalMesh1(GL_LINE, 0, 30); // Se dibuja la curva de Bezier
    glPointSize(4.0);
    glEvalMesh1(GL_POINT, 0, 30); // Se dibujan los puntos de la curva de Bezier

    // puntos de control
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(6.0);
    glBegin(GL_POINTS);
        for (i = 0; i < 4; i++)
            glVertex3fv(&ptosctl[i][0]);
    glEnd();

    glFlush();
}
void ajusta(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void teclado(unsigned char key, int x, int y){
    if (key == 27)
        exit(0);
}
int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Curva de Bezier");
    inicializa();
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
    glutMainLoop();
    return 0;
}