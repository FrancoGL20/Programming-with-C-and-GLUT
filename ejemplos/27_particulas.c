/* Basado en codigo particle.c de Nate Robins, 1998 */
#include <stdlib.h>
#include <GL/glut.h>
#ifdef _WIN32
#define drand48() ((float)rand() / RAND_MAX)
#endif
#define PS_WATERFALL 0
#define PS_FOUNTAIN 1
#define PS_GRAVITY -9.8
#define masa 0.75 // masa de la partícula
#define dt 0.005  // h incrementos de tiempo
typedef struct
{
    float position[3];
    float velocity[3];
} PSparticle;
PSparticle *particles = NULL;
int num_particles = 10000;
int type = PS_WATERFALL;
int np = 0;    // contador de particulas
int flujo = 2; // particulas emitidas por unidad de tiempo
void psTimeStep(PSparticle *p)
{
    // v(t+h)=v(t)+F(t)/m*h
    p->velocity[0] += 0;
    p->velocity[1] += PS_GRAVITY / masa * dt;
    p->velocity[2] += 0;
    // x(t+h)=x(t) + v(t+h)*h
    p->position[0] += p->velocity[0] * dt;
    p->position[1] += p->velocity[1] * dt;
    p->position[2] += p->velocity[2] * dt;
}
void psNewParticle(PSparticle *p)
{
    if (type == PS_WATERFALL)
    {
        p->velocity[0] = -2 * drand48();
        p->velocity[1] = 0;
        p->velocity[2] = 0.5 * drand48();
        p->position[0] = 0;
        p->position[1] = 2.5;
        p->position[2] = 0;
    }
    else if (type == PS_FOUNTAIN)
    {
        p->velocity[0] = 2 * (drand48() - 0.5);
        p->velocity[1] = 6;
        p->velocity[2] = 2 * (drand48() - 0.5);
        p->position[0] = -0.1;
        p->position[1] = 0.9;
        p->position[2] = 0;
    }
}
void reshape(int width, int height)
{
    glClearColor(0, 0, 0, 0);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)width / height, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 1, 3, 0, 1, 0, 0, 1, 0);
    glPointSize(3);
}
void display(void)
{
    static int i;
    static float c;
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glBegin(GL_POINTS);
    for (i = 0; i < np; i++)
    {
        // asignar color por posición
        c = particles[i].position[1] / 2.5 * 255;
        glColor3ub(c, 128 + c * 0.5, 255);
        glVertex3fv(particles[i].position);
    }
    glEnd();
    glPopMatrix();
    glutSwapBuffers();
}
void idle(void)
{
    int i;
    // crea nuevas particulas
    if (np < num_particles)
        for (i = 0; i < flujo; i++)
        {
            psNewParticle(&particles[np]);
            np++;
        }
    // llama al integrador
    for (i = 0; i < np; i++)
        psTimeStep(&particles[i]);
    glutPostRedisplay();
}
void bail(int code)
{
    free(particles);
    exit(code);
}
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        bail(0);
    case 't':
        type = !type;
        break;
    case '+':
        if (flujo < 5)
            flujo++;
        break;
    case '-':
        if (flujo > 1)
            flujo--;
    }
}
int main(int argc, char **argv)
{
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glutInit(&argc, argv);
    glutCreateWindow("Particles");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    // espacio en memoria
    particles = (PSparticle *)malloc(sizeof(PSparticle) * num_particles);
    glutMainLoop();
    return 0;
}