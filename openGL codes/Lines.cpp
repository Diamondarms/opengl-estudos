#include <iostream>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <cmath>

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
    GLfloat angle;
    GLfloat axis[3] = {0.0f,0.0f,0.0f};
    GLfloat colors1[3] = {0.97f,0.46f,0.61f};
    GLfloat colors2[3] = {0.74f,0.46f,0.97f};
    GLfloat radius = 50.0f;
    GLfloat pieces = 64.0f;

    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glRotatef(xRot,1.0f,0.0f,0.0f);
    glRotatef(yRot,0.0f,1.0f,0.0f);
    
    glLineWidth(10);

    //Axis x  y z
    GLfloat lineD= 80.0f;
    for (int i = 1; i <= 3; i++) {
        glColor3f(colors1[(0 + i) % 3],colors1[(1 + i) % 3],colors1[(2 + i) % 3]);
        axis[(0 + i) % 3] = axis[(2 + i) % 3]= 0.0f;
        glBegin(GL_LINES);
            axis[(1 + i) % 3] = lineD;
            glVertex3f(axis[0],axis[1],axis[2]);
            axis[(1 + i) % 3] = -lineD;
            glVertex3f(axis[0],axis[1],axis[2]);
        glEnd();
    }

    glLineWidth(5);

    //Circles
    for (int i = 1; i <= 3; i++) {
        glColor3f(colors1[(0 + i) % 3],colors1[(1 + i) % 3],colors1[(2 + i) % 3]);
        axis[(0 + i) % 3] = 0.0f;
        glBegin(GL_LINE_LOOP);
            for (angle = 0; angle <= GL_2PI; angle += GL_2PI / pieces) {
                axis[(1 + i) % 3] = radius*sin(angle);
                axis[(2 + i) % 3] = radius*cos(angle);
                
                glVertex3f(axis[0],axis[1],axis[2]);
            }
        glEnd();
    }

    radius = radius/2;
    glLineWidth(3);
    //Circles with 45°/135° inclination
    for (int i = 1; i <= 3; i++) {
        glColor3f(colors2[(0 + i) % 3],colors2[(1 + i) % 3],colors2[(2 + i) % 3]);
        glBegin(GL_LINE_LOOP);
            for (angle = 0; angle <= GL_2PI; angle += GL_2PI / pieces) {
                axis[(0 + i) % 3] = radius*(GL_PI/4)*sin(angle);
                axis[(1 + i) % 3] = radius*cos(angle);
                axis[(2 + i) % 3] = axis[(0 + i) % 3];

                glVertex3f(axis[0],axis[1],axis[2]);
            }
            for (angle = 0; angle <= GL_2PI; angle += GL_2PI / pieces) {
                axis[(2 + i) % 3] = radius*(GL_PI/4)*sin(angle);
                axis[(1 + i) % 3] = radius*cos(angle);
                axis[(0 + i) % 3] = -axis[(2 + i) % 3];

                glVertex3f(axis[0],axis[1],axis[2]);
            }
        glEnd();
    }
    /*  Equivalente

    z = 0.0f;
    glBegin(GL_LINE_LOOP); // Vermelho
        for (angle = 0; angle <= GL_2PI; angle += GL_2PI / pieces)
        {
            x = radius*sin(angle);
            y = radius*cos(angle);
            
            glVertex3f(x,y,z);
        }
    glEnd();
    
    glBegin(GL_LINE_LOOP); // Roxo
        for (angle = 0; angle <= GL_2PI; angle += GL_2PI / pieces)
        {
            x = radius*(GL_PI/4)*sin(angle);
            y = radius*cos(angle);
            z = x;
            
            glVertex3f(x,y,z);
        }
        for (angle = 0; angle <= GL_2PI; angle += GL_2PI / pieces)
        {
            z = radius*(GL_PI/4)*sin(angle);
            y = radius*cos(angle);
            x = -z;
            
            glVertex3f(x,y,z);
        }
    glEnd();*/

    glPopMatrix();

    glutSwapBuffers();
}

void SetupRC(void) {
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

