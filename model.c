#include <GLUT/glut.h>

void init(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void draw_trangle(){
    glBegin(GL_TRIANGLES);
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(-1.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glEnd();
    glFlush();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1.0, 1.0, 1.0);
    draw_trangle();

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xF0F0);
    glLoadIdentity();
    glTranslatef(-1.0, 0.0, 0.0);
    draw_trangle();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
    return 0;
}