#include <iostream>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <cmath>
#include "../Utils/ColorUtil.h"

#define GL_PI 3.1415f
#define GL_2PI 6.383f

GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;

int xMouse = 0;
int yMouse = 0;

const float step = 1.0f;
const float maxRotation = 360.0f;

bool mouseButtonPressed = false;

void RenderScene(void){
    GLfloat x,y,z,angle, r;
    GLfloat radius = 50.0f;
    GLfloat pieces = 64.0f;

    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glRotatef(xRot,1.0f,0.0f,0.0f);
    glRotatef(yRot,0.0f,1.0f,0.0f);

    //glEnable(GL_LINE_STIPPLE);

    glLineWidth(10);
    glLineStipple(3,0xffff);

    glBegin(GL_LINES); glColor3f(0.46f,0.61f,0.97f);
        glVertex3f(0.0f,0.0f,-80.0f);
        glVertex3f(0.0f,0.0f,+80.0f);
    glEnd();
    glBegin(GL_LINES); glColor3f(0.61f,0.97f,0.46f);
        glVertex3f(0.0f,-80.0f,0.0f);
        glVertex3f(0.0f,+80.0f,0.0f);
    glEnd();
    glBegin(GL_LINES); glColor3f(0.97f,0.46f,0.61f);
        glVertex3f(-80.0f,0.0f,0.0f);
        glVertex3f(+80.0f,0.0f,0.0f);
    glEnd();

    glLineWidth(5);
    glLineStipple(3,0x5555);
    
    glColor3f(0.97f,0.46f,0.61f);
    z = 0.0f;
    glBegin(GL_LINE_LOOP); // Vermelho
        for (angle = 0; angle <= GL_2PI; angle += GL_2PI / pieces)
        {
            x = radius*sin(angle);
            y = radius*cos(angle);
            
            glVertex3f(x,y,z);
        }
    glEnd();
    
    glColor3f(0.61f,0.97f,0.46f);
    x = 0.0f;
    glBegin(GL_LINE_LOOP); // Verde
        for (angle = 0; angle <= GL_2PI; angle += GL_2PI / pieces)
        {
            z = radius*sin(angle);
            y = radius*cos(angle);
            
            glVertex3f(x,y,z);
        }
    glEnd();
    glColor3f(0.46f,0.61f,0.97f);
    y = 0.0f;
    glBegin(GL_LINE_LOOP); // Azul
        for (angle = 0; angle <= GL_2PI; angle += GL_2PI / pieces)
        {
            z = radius*sin(angle);
            x = radius*cos(angle);
            
            glVertex3f(x,y,z);
        }
    glEnd();

    radius = 25.0f;
    glLineWidth(3);
    glLineStipple(1,0x087f);

    glColor3f(0.74f,0.46f,0.97f);
    glBegin(GL_LINE_LOOP); // Roxo
        for (angle = 0; angle <= GL_2PI; angle += GL_2PI / pieces)
        {
            x = radius*(GL_PI/4)*sin(angle);
            y = radius*cos(angle);
            z = radius*(GL_PI/4)*sin(angle);
            
            glVertex3f(x,y,z);
        }
        for (angle = 0; angle <= GL_2PI; angle += GL_2PI / pieces)
        {
            x = -radius*(GL_PI/4)*sin(angle);
            y = radius*cos(angle);
            z = radius*(GL_PI/4)*sin(angle);
            
            glVertex3f(x,y,z);
        }
    glEnd();

    glColor3f(0.97f,0.74f,0.46f);
    glBegin(GL_LINE_LOOP); // Laranja
        for (angle = 0; angle <= GL_2PI; angle += GL_2PI / pieces)
        {
            z = radius*(GL_PI/4)*sin(angle);
            x = radius*cos(angle);
            y = radius*(GL_PI/4)*sin(angle);
            
            glVertex3f(x,y,z);
        }
        for (angle = 0; angle <= GL_2PI; angle += GL_2PI / pieces)
        {
            z = -radius*(GL_PI/4)*sin(angle);
            x = radius*cos(angle);
            y = radius*(GL_PI/4)*sin(angle);
            
            glVertex3f(x,y,z);
        }
    glEnd();

    glColor3f(0.46f,0.97f,0.74f);
    glBegin(GL_LINE_LOOP); // Verde
        for (angle = 0; angle <= GL_2PI; angle += GL_2PI / pieces)
        {
            y = radius*(GL_PI/4)*sin(angle);
            z = radius*cos(angle);
            x = radius*(GL_PI/4)*sin(angle);
            
            glVertex3f(x,y,z);
        }
        for (angle = 0; angle <= GL_2PI; angle += GL_2PI / pieces)
        {
            y = -radius*(GL_PI/4)*sin(angle);
            z = radius*cos(angle);
            x = radius*(GL_PI/4)*sin(angle);
            
            glVertex3f(x,y,z);
        }
    glEnd();

    /*glColor3f(0.46f,0.61f,0.97f);
    glLineStipple(3,0x5555);

    y = radius*cos((GL_2PI / pieces)*((pieces/4) + 1));
    glBegin(GL_LINE_LOOP); // Azul
        r = radius*sin((GL_2PI / pieces)*((pieces/4) + 1));
        for (angle = 0; angle <= GL_2PI; angle += (GL_2PI / pieces) * 2)
        {
            z = r*sin(angle);
            x = r*cos(angle);
            
            glVertex3f(x,y,z);
        }
    glEnd();

    y = radius*cos((GL_2PI / pieces)*((pieces/4) - 1));
    glBegin(GL_LINE_LOOP); // Azul
        for (angle = 0; angle <= GL_2PI; angle += (GL_2PI / pieces) * 2)
        {
            z = r*sin(angle);
            x = r*cos(angle);
            
            glVertex3f(x,y,z);
        }
    glEnd();*/


    glPopMatrix();

    glutSwapBuffers();
}

void SetupRC(void) {
    //glClearColor(0.53f, 0.65f, 0.98f, 1.0f);
    glClearColor(0.73f, 0.75f, 0.88f, 1.0f);
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

void Keys(unsigned char key, int x, int y) {
    switch (key) {
        case 27:  // Esc
            exit(0); 
            break;
    }
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
}

void Motion(int x, int y) {
    if (mouseButtonPressed) {
        xRot += x > xMouse ? step : x < xMouse ? -step : 0;
        xMouse = x;
        yRot += y > yMouse ? step : y < yMouse ? -step : 0;
        yMouse = y;

        if (xRot >= maxRotation) xRot -= maxRotation;
        if (yRot >= maxRotation) yRot -= maxRotation;

        glutPostRedisplay();
    }
}

int main(int argc, char* argv[]){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("Banana");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(Keys);
    glutSpecialFunc(SpecialKeys);
    glutMouseFunc(Mouse);
    glutMotionFunc(Motion);
    SetupRC();

    glutMainLoop();

    return 0;
}

