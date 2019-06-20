#include <GLUT/glut.h>
#include <stdio.h>

#define drawOneline(x1,y1,x2,y2) glBegin(GL_LINES); \
    glVertex2f((x1), (y1)); glVertex2f((x2), (y2)); glEnd();

void init(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(){
    int i;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x0101);
    drawOneline(50.0, 125.0, 150.0, 125.0);
    glLineStipple(1, 0x00ff);
    drawOneline(150.0, 125.0, 250.0, 125.0);
    glLineStipple(1, 0x1c47);
    drawOneline(250.0, 125.0, 350.0, 125.0);

    glLineWidth(5.0);
    glLineStipple(1, 0x1010);
    drawOneline(50.0, 100.0, 150.0, 100.0);
    glLineStipple(1, 0x00FF);
    drawOneline(150.0, 100.0, 250.0, 100.0);
    glLineStipple(1, 0x1c47);
    drawOneline(250.0, 100.0, 350.0, 100.0);
    glLineWidth(1.0);
    glDisable(GL_LINE_STIPPLE);
    glFlush();
}

void reshape(int w, int h){
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(400, 150);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}