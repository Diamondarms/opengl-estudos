#include <iostream>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <cmath>

GLfloat x1 = 0.0f;
GLfloat t1 = 0.0f;
GLfloat rsize = 26.0f;

GLfloat xstep = 2.0f;
GLfloat ystep = 2.0f;

GLfloat windowWidth;
GLfloat windowHeight;

void RenderScene(void){
    GLdouble dRadius = 0.1;
    GLdouble dAngle;

    glClearColor(0.53f, 0.65f, 0.98f, 1.0f);

    glClearStencil(0.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); 

    glStencilFunc(GL_NEVER,0x0,0x0);
    glStencilOp(GL_INCR,GL_INCR,GL_INCR);

    glColor3i(1,1,1);
    glBegin(GL_LINE_STRIP);
        for(dAngle = 0; dAngle < 400.0; dAngle += 0.1){
            glVertex2d(dRadius * cos(dAngle), dRadius*sin(dAngle));
            dRadius *= 1.002;
        }
    glEnd();


    glStencilFunc(GL_NOTEQUAL,0x1,0x1);
    glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);

    glColor3f(1.0f,0.0f,0.0f);
    glRectf(x1, t1, x1+rsize, t1-rsize);

    glutSwapBuffers();
}

void TimerFunction(int value){
    if(x1 > windowWidth-rsize || x1 < -windowWidth){
        xstep = -xstep;
    }

    if(t1 > windowHeight || t1 < -windowHeight+rsize)
        ystep = -ystep;

    x1 += xstep;
    t1 += ystep;

    if(x1 > (windowWidth-rsize+xstep))
        x1 = windowWidth-rsize-1;
    else if(x1 < -(windowWidth + xstep))
    x1 = -windowWidth-1;

    if(t1 > (windowHeight+ystep))
        t1 = windowHeight-1.0f;
    else if(t1 < -(windowHeight-rsize + ystep))
    t1 = -windowHeight+rsize-1.0f;

    glutPostRedisplay();
    glutTimerFunc(33,TimerFunction,1);
}

void SetupRC(void) {
    glClearColor(0.53f, 0.65f, 0.98f, 1.0f);
    glEnable(GL_STENCIL_TEST);
}

void ChangeSize(GLsizei w, GLsizei h){
    GLfloat nRange = 100.0f;

    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat aspectRatio = (GLfloat)w / (GLfloat)h;
    if (w <= h) {
        glOrtho(-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
        windowWidth = 100; windowHeight = 100.0f / aspectRatio;
    } else {
        glOrtho(-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
        windowWidth = 100.0f * aspectRatio; windowHeight = 100;
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char* argv[]){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_STENCIL);
    glutInitWindowSize(800,600);
    glutCreateWindow("Banana");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutTimerFunc(3,TimerFunction,1);
    SetupRC();

    glutMainLoop();

    return 0;
}

