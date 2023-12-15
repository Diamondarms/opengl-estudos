#include <iostream>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <valarray>

#define GL_PI 3.1415f

GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;

int xMouse = 0;
int yMouse = 0;

const float step = 1.0f;
const float maxRotation = 360.0f;

bool mouseButtonPressed = false;

void RenderScene(void){
    GLfloat x,y,z,angle;

    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glRotatef(xRot,1.0f,0.0f,0.0f);
    glRotatef(yRot,0.0f,1.0f,0.0f);

    glBegin(GL_POINTS);

    z = -50.0f;
    for (angle = 0; angle <= (2.0f*GL_PI)*3.0f; angle += 0.1f)
    {
        x = 50.0f*sin(angle);
        y = 50.0f*cos(angle);

        glVertex3f(x,y,z);
        z+=0.5f;
    }
        
    glEnd();

    glPopMatrix();

    glutSwapBuffers();
}

void SetupRC(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glColor3f(0.0f,1.0f,0.0f);
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
        case 27:  // Código ASCII para a tecla Esc
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

    switch (key) {
        case 27:  // Código ASCII para a tecla Esc
            exit(0);  // Encerra o programa
            break;
    }
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

