#include <GLUT/glut.h>
#include <stdio.h>

static GLint vertices[] = {
    25, 25,
    100, 325,
    175, 25,
    175, 325,
    250, 25,
    325, 325,
};

static GLfloat colors[] = {
    1.0, 0.2, 0.2,
    0.2, 0.2, 1.0,
    0.8, 1.0, 0.2,
    0.75, 0.75, 0.75,
    0.35, 0.35, 0.35,
    0.5, 0.5, 0.5,
};

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glVertexPointer(2, GL_INT, 0, vertices);
    glBegin(GL_TRIANGLES);
    glArrayElement(2);
    glArrayElement(3);
    glArrayElement(5);
    glEnd();
    glFlush();
}

void reshape(int w, int h){
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

void init(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}