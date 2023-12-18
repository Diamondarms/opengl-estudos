#include <iostream>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

GLfloat x1 = 0.0f;
GLfloat t1 = 0.0f;
GLfloat rsize = 26.0f;

GLfloat xstep = 2.0f;
GLfloat ystep = 2.0f;

GLfloat windowWidth;
GLfloat windowHeight;

void RenderScene(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f,0.0f,0.0f);
    glRectf(x1, t1, x1+rsize, t1-rsize);
    glutSwapBuffers();
}

void SetupRC(void) {
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
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
        t1 = windowHeight-1;
    else if(t1 < -(windowHeight-rsize + ystep))
    t1 = -windowHeight+rsize-1;

    glutPostRedisplay();
    glutTimerFunc(3,TimerFunction,1);
}

void ChangeSize(GLsizei w, GLsizei h){
    GLfloat aspectRatio;

    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    aspectRatio = (GLfloat)w / (GLfloat)h;

    if (w <= h) {
        glOrtho(-100.0, 100.0, -100.0 / aspectRatio, 100.0 / aspectRatio, 1.0, -1.0);
        windowWidth = 100; windowHeight = 100.0f / aspectRatio;
    } else {
        glOrtho(-100.0 * aspectRatio, 100.0 * aspectRatio, -100.0, 100.0, 1.0, -1.0);
        windowWidth = 100.0f * aspectRatio; windowHeight = 100;
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