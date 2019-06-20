#include <GLUT/glut.h>
//#include <OpenGL/gl3.h>
#include <stdio.h>

#define M_PI 3.1415926
#define BUFFER_OFFSET(o) ((GLvoid*)NULL+o)
#define NumberOf(array) (sizeof(array)/sizeof(array[0]))

typedef struct {
    GLfloat x, y, z;
} vec3;

typedef struct {
    vec3 xlate;
    GLfloat angle;
    vec3 axis;
} XForm;

enum {Cube, Cone, NumVAOs};
GLuint VAO[NumVAOs];
GLenum PrimType[NumVAOs];
GLsizei NumElements[NumVAOs];
XForm Xform[NumVAOs] = {
    {{-2.0, 0.0, 5.0}, 0.0, {0.0, 1.0, 0.0}},
    {{0.0, 0.0, 2.0}, 0.0, {1.0, 0.0, 0.0}}
};
GLfloat Angle = 0.0;

void init(){
    printf("%u\n", BUFFER_OFFSET(0));
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(0);
    enum {Vertices, Colors, Elements, NumVBOs};
    GLuint buffers[NumVBOs];
    glGenVertexArrays(NumVAOs, VAO);
    {
        GLfloat cubeVerts[][3] = {
            {-1.0, -1.0, -1.0},
            {-1.0, -1.0, 1.0},
            {-1.0, 1.0, -1.0},
            {-1.0, 1.0, 1.0},
            {1.0, -1.0, -1.0},
            {1.0, -1.0, 1.0},
            {1.0, 1.0, -1.0},
            {1.0, 1.0, 1.0},
        };
        GLfloat cubeColors[][3] = {
            {0.0, 0.0, 0.0},
            {0.0, 0.0, 1.0},
            {0.0, 1.0, 0.0},
            {0.0, 1.0, 1.0},
            {1.0, 0.0, 0.0},
            {1.0, 0.0, 1.0},
            {1.0, 1.0, 0.0},
            {1.0, 1.0, 1.0},
        };
        GLubyte cubeIndices[] = {
            0,1,3,2,
            4,6,7,5,
            2,3,7,6,
            0,4,5,1,
            0,2,6,4,
            1,5,7,3,
        };
        glBindVertexArray(VAO[Cube]);
        glGenBuffers(NumVBOs, buffers);
        glBindBuffer(GL_ARRAY_BUFFER, buffers[Vertices]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerts), cubeVerts, GL_STATIC_DRAW);
        glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
        glEnableClientState(GL_VERTEX_ARRAY);

        glBindBuffer(GL_ARRAY_BUFFER, buffers[Colors]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColors), cubeColors, GL_STATIC_DRAW);
        glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
        glEnableClientState(GL_COLOR_ARRAY);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[Elements]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

        PrimType[Cube] = GL_QUADS;
        NumElements[Cube] = NumberOf(cubeIndices);
    }
    {
        int i, idx;
        float dTheta;
#define NumConePoints 36
        GLfloat coneVerts[NumConePoints+1][3] = {
            {0.0, 0.0, 1.0}
        };
        GLfloat coneColors[NumConePoints+1][3] = {
            {1.0, 1.0, 1.0}
        };
        GLubyte coneIndices[NumConePoints+1];
        dTheta = 2*M_PI/(NumConePoints-1); 
        idx = 1;
        for (i = 0; i < NumConePoints; ++i,++idx){
            float theta = i*dTheta;
            coneVerts[idx][0] = cos(theta);
            coneVerts[idx][1] = sin(theta);
            coneVerts[idx][2] = 0.0;

            coneColors[idx][0] = cos(theta);
            coneColors[idx][1] = sin(theta);
            coneColors[idx][2] = 0.0;

            coneIndices[idx] = idx;
        }

        glBindVertexArray(VAO[Cone]);
        glGenBuffers(NumVBOs, buffers);
        glBindBuffer(GL_ARRAY_BUFFER, buffers[Vertices]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(coneVerts), coneVerts, GL_STATIC_DRAW);
        glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
        glEnableClientState(GL_VERTEX_ARRAY);

        glBindBuffer(GL_ARRAY_BUFFER, buffers[Colors]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(coneColors), coneColors, GL_STATIC_DRAW);
        glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
        glEnableClientState(GL_COLOR_ARRAY);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[Elements]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(coneIndices), coneIndices, GL_STATIC_DRAW);

        PrimType[Cone] = GL_TRIANGLE_FAN;
        NumElements[Cone] = NumberOf(coneIndices);
    }
    glEnable(GL_DEPTH_TEST);
}

void display(){
    int i;
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(Angle, 0.0, 1.0, 0.0);
    for (i = 0; i < NumVAOs; ++i){
        glPushMatrix();
        glTranslatef(Xform[i].xlate.x, Xform[i].xlate.y, Xform[i].xlate.z);
        glRotatef(Xform[i].angle, Xform[i].axis.x, Xform[i].axis.y, Xform[i].axis.z);
        glBindVertexArray(VAO[i]);
        glDrawElements(PrimType[i], NumElements[i], GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
        glPopMatrix();
    }
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h){
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    //glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

