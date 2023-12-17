#include <iostream>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <cmath>

void RenderScene(void){
    static GLdouble dRadius = 0.1;
    static GLdouble dAngle = 0.0;

    //glPointSize(10);

    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);

    if (dAngle == 0.0)
        glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
        glVertex2d(dRadius * cos(dAngle), dRadius*sin(dAngle));
    glEnd();

    dRadius *= 1.01;
    dAngle += 0.1;

    if(dAngle > 30.0){
        dRadius = 0.1;
        dAngle = 0.0;
    }

    glFlush();
}

void SetupRC(void) {
    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
}

void ChangeSize(GLsizei w, GLsizei h){
    GLfloat nRange = 800.0f;

    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h) {
        glOrtho(-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    } else {
        glOrtho(-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char* argv[]){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("Banana");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    SetupRC();

    glutMainLoop();

    return 0;
}

