#include <GL/glut.h>

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

    // Dibujar un cubo rojo transparente
    glColor4f(1.0f, 0.0f, 0.0f, 0.5f); // Color rojo con alfa = 0.5
    glTranslatef(-1.0f, 0.0f, 0.0f); // Mover el cubo a la izquierda
    glutSolidCube(1.0f); // Dibujar el cubo

    // Dibujar un cubo azul transparente
    glColor4f(0.0f, 0.0f, 1.0f, 0.8f); // Color azul con alfa = 0.8
    glTranslatef(2.0f, 0.0f, -1.0f); // Mover el cubo a la derecha y atrás
    glutSolidCube(1.0f); // Dibujar el cubo

    glFlush();
}

void init(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Color de fondo blanco
    glEnable(GL_DEPTH_TEST); // Habilitar el test de profundidad
    glEnable(GL_BLEND); // Habilitar el modo de mezcla
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Función de mezcla para transparencia
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ejemplo de transparencia");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}