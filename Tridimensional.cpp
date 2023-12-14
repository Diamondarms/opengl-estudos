#include <iostream>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

GLfloat x1 = 0.0f;
GLfloat y1 = 0.0f;
GLfloat rsize = 26.0f;

GLfloat xstep = 2.0f;
GLfloat ystep = 2.0f;

GLfloat windowWidth;
GLfloat windowHeight;

void RenderScene(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f,0.0f,0.0f);
    glRectf(x1, y1, x1+rsize, y1-rsize);
    glutSwapBuffers();
}

void SetupRC(void) {
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

void TimerFunction(int value){
    if(x1 > windowWidth-rsize || x1 < -windowWidth){
        xstep = -xstep;
    }

    if(y1 > windowHeight || y1 < -windowHeight+rsize)
        ystep = -ystep;

    x1 += xstep;
    y1 += ystep;

    if(x1 > (windowWidth-rsize+xstep))
        x1 = windowWidth-rsize-1;
    else if(x1 < -(windowWidth + xstep))
    x1 = -windowWidth-1;

    if(y1 > (windowHeight+ystep))
        y1 = windowHeight-1;
    else if(y1 < -(windowHeight-rsize + ystep))
    y1 = -windowHeight+rsize-1;

    glutPostRedisplay();
    glutTimerFunc(3,TimerFunction,1);
}

void ChangeSize(GLsizei w, GLsizei h){
    GLfloat nRange = 100.0f;

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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("Banana");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutTimerFunc(3,TimerFunction,1);
    SetupRC();

    glutMainLoop();

    return 0;
}