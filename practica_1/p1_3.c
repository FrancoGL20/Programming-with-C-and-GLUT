#include <GL/glut.h>
#include <stdio.h>

void dibujaLetra(float vertices[][2],int n_vertices,GLboolean solido,int position[2],int escala){
    float letraEscaladaYMovida[n_vertices][2];
    // escalar y mover letra
    for (int i = 0; i < n_vertices; i++){
        letraEscaladaYMovida[i][0]=vertices[i][0]*escala+position[0];
        letraEscaladaYMovida[i][1]=vertices[i][1]*escala+position[1];
    }
    // recorrer arreglo e imprimir el vertice
    glColor3ub(88, 207, 100); // cambio de color

    // dibujo de líneas
    glBegin(solido?GL_QUAD_STRIP:GL_LINE_LOOP);
    for (int i = 0; i < n_vertices; i++){
        glVertex2fv(letraEscaladaYMovida[i]);
    }
    glEnd();
}
void ajustar(int ancho, int alto){
    glClearColor(1.0,1.0,1.0,0.0); // color de fondo de ventana
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480); // la relacion aspecto de la ventana es 640*480
}
void dibujar(void){
    // limpiar buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // OPCION 1
    // dibujo de primera letra
    int nVertices=14;
    float letraSolida[][2]={{0,0},{1,0},{0,2.5},{1,2},{1.5,2.5},{2,2},{1.5,2.5},{2,3},{0,2.5},{1,3},{0,5},{1,4},{3,5},{3,4}};
    GLboolean solido=GL_TRUE;
    int pos[2]={150,165};
    dibujaLetra(letraSolida,nVertices,solido,pos,30);

    // OPCION 2
    // dibujo de segunda letra
    float letraContorno[][2]={{0,0},{0,5},{3,5},{3,4},{1,4},{1,3},{2,3},{2,2},{1,2},{1,0}};
    nVertices=11;
    solido=GL_FALSE;
    pos[0]=390;
    pos[1]=165;
    dibujaLetra(letraContorno,nVertices,solido,pos,30);
    
    // enviarlo a pantalla
    glFlush();
}
int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480); // tamaño de la ventana que se va a obtener
    glutInitWindowPosition(100, 150); // posición donde se colocará la ventana
    glutCreateWindow("Practica 1.2"); // titulo de la ventana
    glutReshapeFunc(ajustar);
    glutDisplayFunc(dibujar);
    glutMainLoop();
    return 0;
}
