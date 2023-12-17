#include <iostream>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <cmath>

#define GL_PI 3.1415f

GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;

int xMouse = 0;
int yMouse = 0;

const float step = 1.0f;
const float maxRotation = 360.0f;

bool mouseButtonPressed = false;

void RenderScene(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glRotatef(xRot,1.0f,0.0f,0.0f);
    glRotatef(yRot,0.0f,1.0f,0.0f);

    glFrontFace(GL_CW);

    glBegin(GL_TRIANGLE_FAN); // Vermelho

        glColor3f(0.0f,1.0f,0.0f);
        glVertex3i(25,-25,50);

        glEdgeFlag(true);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex3i(0,0,0);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3i(0,-50,0);
        glEdgeFlag(true);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex3i(50,-50,0);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3i(50,0,0);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex3i(0,0,0);

    glEnd();

    glBegin(GL_QUAD_STRIP);
        glVertex3i(25,25,0); //v1
        glVertex3i(0,25,0); //v2
        glVertex3i(25,25,25); //v3
        glVertex3i(0,25,25);  //v4
        glVertex3i(25,50,25); //v5
        glVertex3i(0,50,25); //v6
        glVertex3i(25,50,0);
        glVertex3i(0,50,0);
        glVertex3i(25,25,0);
        glVertex3i(0,25,0);
    glEnd();

    glBegin(GL_QUADS);
        glVertex3i(25,25,0); 
        glVertex3i(25,25,25); 
        glVertex3i(25,50,25); 
        glVertex3i(25,50,0);
        glVertex3i(0,25,25);  
        glVertex3i(0,25,0); 
        glVertex3i(0,50,0);
        glVertex3i(0,50,25); 
    glEnd();

    glFrontFace(GL_CCW);

    glBegin(GL_POLYGON);
        glVertex3i(60,60,0); 
        glVertex3i(60,70,0); 
        glVertex3i(70,70,0); 
        glVertex3i(80,65,0);  
        glVertex3i(80,60,0);
    glEnd();

    glFrontFace(GL_CCW);
    glFrontFace(GL_CCW);

    glBegin(GL_TRIANGLE_FAN);
        
        glColor3f(1.0f,0.0f,0.0f);
        glVertex3i(25,-25,-25);
        glVertex2i(0,0);
        glVertex2i(0,-50);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex2i(50,-50);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex2i(50,0);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex2i(0,0);
    glEnd();

    glColor3f(0.0f,0.0f,1.0f);
    glPointSize(5);
    glBegin(GL_POINTS);
        glVertex2i(0,0);
    glEnd();
        
    glPopMatrix();

    glutSwapBuffers();

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cout << "Erro OpenGL após glFrontFace: " << error << std::endl;

    }
}

void SetupRC(void) {
    glClearColor(0.73f, 0.75f, 0.88f, 1.0f);
    glShadeModel(GL_FLAT);

    true ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
    true ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
    false ? glPolygonMode(GL_BACK,GL_LINE) : glPolygonMode(GL_BACK,GL_FILL) ;
    glEnable(GL_EDGE_FLAG);
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

void SpecialKeys(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_UP:
            xRot += step;
            break;
        case GLUT_KEY_DOWN:
            xRot -= step;
            break;
        case GLUT_KEY_LEFT:
            yRot -= step;
            break;
        case GLUT_KEY_RIGHT:
            yRot += step;
            break;
    }

    if (xRot >= maxRotation) xRot -= maxRotation;
    if (yRot >= maxRotation) yRot -= maxRotation;

    glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            mouseButtonPressed = true;
            xMouse = x;
            yMouse = y;
        } else {
            mouseButtonPressed = false;
        }
    }
    glutPostRedisplay();
}

void Motion(int x, int y) {
    if (mouseButtonPressed) {
        xRot += x > xMouse ? step : x < xMouse ? -step : 0;
        xMouse = x;
        yRot += y > yMouse ? step : y < yMouse ? -step : 0;
        yMouse = y;

        if (xRot >= maxRotation) xRot -= maxRotation;
        if (yRot >= maxRotation) yRot -= maxRotation;

    }
    glutPostRedisplay();
}

int main(int argc, char* argv[]){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutCreateWindow("Banana");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutMouseFunc(Mouse);
    glutMotionFunc(Motion);
    SetupRC();

    glutMainLoop();

    return 0;
}

