#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.5, -0.5);
        glVertex2f(-0.5, 0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(0.5, -0.5);
    glEnd();
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2.0, 2.0,
                -2.0 * (GLfloat) h / (GLfloat) w,
                 2.0 * (GLfloat) h / (GLfloat) w,
                -10.0, 10.0);
    else
        glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
                 2.0 * (GLfloat) w / (GLfloat) h,
                -2.0, 2.0,
                -10.0, 10.0);

}

int main(int argc,char** argv)
{
    glutInit(&argc , argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize(500 ,500 );
    glutInitWindowPosition(100 ,100 );
    glutCreateWindow("Ejemplo");
    
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape); 
    
    glutMainLoop();
}