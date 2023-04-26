#include <GL/gl.h>
#include <GL/glut.h>

void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT); //limpia la pantalla (frame buffer)
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 
    glutInitWindowSize(640,480); 
    glutInitWindowPosition(100, 150); 
    glutCreateWindow("Ventana"); 
    glutDisplayFunc(dibuja); 
    glutMainLoop(); 
    return 0;
}