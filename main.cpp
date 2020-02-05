/*******************************************************
 * Homework 2: OpenGL                                  *
 * CS 148 (Summer 2016), Stanford University           *
 *-----------------------------------------------------*
 * First, you should fill in problem1(), problem2(),   *
 * and problem3() as instructed in the written part of *
 * the problem set.  Then, express your creativity     *
 * with problem4()!                                    *
 *                                                     *
 * Note: you will only need to add/modify code where   *
 * it says "TODO".                                     *
 *                                                     *
 * The left mouse button rotates, the right mouse      *
 * button zooms, and the keyboard controls which       *
 * problem to display.                                 *
 *                                                     *
 * For Linux/OS X:                                     *
 * To compile your program, just type "make" at the    *
 * command line.  Typing "make clean" will remove all  *
 * computer-generated files.  Run by typing "./hw2"    *
 *                                                     *
 * For Visual Studio:                                  *
 * You can create a project with this main.cpp and     *
 * build and run the executable as you normally would. *
 *******************************************************/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#if __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

using namespace std;
double PI {atan(1) *4};

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = {0,1,4,1};
int windowWidth = 640, windowHeight = 480;
double yRot = 0;
int curProblem = 1; // TODO: change this number to try different examples

float specular[] = { 1.0, 1.0, 1.0, 1.0 };
float shininess[] = { 50.0 };


void problem1()
{
    for(int i = 0; i < 10; ++i)
    {
        glPushMatrix(); //pushes current transformation matrix onto stack(In this case, that will be an Identity matrix)
        glTranslatef(cos(i*(PI/5)),sin(i*(PI/5)),0); //Coordinates to translate by are circuiliar coord of pi/5ths
        glRotatef(i*36,0,0,1); //rotate for 36 degrees for every translation

        glutSolidTeapot(0.20); //render teapot
        glPopMatrix(); //return to identity matrix
    }
}

void problem2()
{
    //unit size of cube is 0.20, therefore this value is used to scale the translations
    double translationScaler{0.20};

    //There are 15 cubes that scale from unit size to approximately 3 times the size(vertically)
    //This is the value that needs to be added to the scale to reach 3 times the size of the original cube within in exactly 15 cubes
    //ScaleFactor(3) - ScaleFactor(1) / # of cubes(15)
    double scaleFactor{2.0/15};

    //Scaling keeps object centered and stretches
    //In order, to keep all cubes level with first cube, each cube needs to be translated upwards by a certain amount
    //
    double incV{1.0/150};

    for(int i = 0; i < 15;++i)
    {
        glPushMatrix(); //pushes current transformation matrix onto stack(In this case, that will be an Identity matrix)
        glScalef(1,1+((i+1)*scaleFactor),1); //Applies scale transformation
        glTranslatef(-1.5+translationScaler*i,i*incV,0); //Applies translation transformation
        glutSolidCube(0.20); //Acutally renders cube with specific size
        glPopMatrix(); //Applies original matrix(Identity)
    }
}

void problem3()
{
    //draw six teapots
    for(int i = 0; i < 6; ++i)
    {
        glPushMatrix();
        glTranslatef(-2.5+i,-1.5,0); // start at -2.5 and increment for every next for loop
        glutSolidTeapot(0.25);
        glPopMatrix();
    }

    //then five
    for(int i = 0; i <5; ++i)
    {
        glPushMatrix();
        glTranslatef(-2.0 + i,-1.0,0);
        glutSolidTeapot(0.25);
        glPopMatrix();
    }

    //etc...
    for(int i = 0; i<4; ++i)
    {
        glPushMatrix();
        glTranslatef(-1.5 + i, -0.5,0);
        glutSolidTeapot(0.25);
        glPopMatrix();
    }

    for(int i = 0; i < 3; ++i)
    {
        glPushMatrix();
        glTranslatef(-1.0 + i,0,0);
        glutSolidTeapot(0.25);
        glPopMatrix();
    }

    for(int i =0; i< 2; ++i)
    {
        glPushMatrix();
        glTranslatef(-0.5 + i,0.5,0);
        glutSolidTeapot(0.25);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(0,1,0);
    glutSolidTeapot(0.25);
    glPopMatrix();
}

void problem4()
{

    for(int i =0; i < 3; ++i)
    {
        glPushMatrix();
        glTranslatef(0.55,0.55,0);
        glRotatef(45,0,0,1);
        glutSolidTeapot(0.15);
        glPopMatrix();

        //triangle made from lines
        glBegin(GL_LINES);
            glColor3f(1,0,0); glVertex3f(0.2,0.3,0); glVertex3f(1,0.3,0);
            glColor3f(1,0,0); glVertex3f(0.2,0.3,0); glVertex3f(0.6,1,0);
            glColor3f(1,0,0); glVertex3f(1,0.3,0); glVertex3f(0.6,1,0);
        glEnd(/*GL_LINES*/);



        for(int j = 0;j < 10; ++j)
        {
            if(i==0)
            {
                glPushMatrix();
                glTranslatef(-0.1*j,0,0);
                glutSolidCube(0.1);
                glPopMatrix();
            }

            else if(i==1)
            {
                glPushMatrix();
                glTranslatef(0,-0.1*j,0);
                glutSolidCube(0.1);
                glPopMatrix();
            }

            else
            {
                glPushMatrix();
                glTranslatef(-0.1*j,-0.1*j,0);
                glutSolidCube(0.1);
                glPopMatrix();
            }
        }
    }
}


void display() {
    glClearColor(0,0,0,0); //determine color that the window will be cleared to(black)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //actually clears window and sets it to the color in glClearColor

    glDisable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glBegin(GL_LINES); //define object to be drawn
        glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(1,0,0); // x axis - glcolor3f determines what color to draw with
        glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,1,0); // y axis - vertex determines corners of polygon (x,y,z)
        glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,1); // z axis
    glEnd(/*GL_LINES*/);

    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glEnable(GL_LIGHT0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); //clears the matrix
    glViewport(0,0,windowWidth,windowHeight);

    float ratio = (float)windowWidth / (float)windowHeight;
    gluPerspective(50, ratio, 1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

    glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

    glRotatef(yRot,0,1,0);

    if (curProblem == 1) problem1();
    if (curProblem == 2) problem2();
    if (curProblem == 3) problem3();
    if (curProblem == 4) problem4();

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) leftDown = (state == GLUT_DOWN);
    else if (button == GLUT_RIGHT_BUTTON) rightDown = (state == GLUT_DOWN);

    lastPos[0] = x;
    lastPos[1] = y;
}

void mouseMoved(int x, int y) {
    if (leftDown) yRot += (x - lastPos[0])*.1;
    if (rightDown) {
        for (int i = 0; i < 3; i++)
            cameraPos[i] *= pow(1.1,(y-lastPos[1])*.1);
    }


    lastPos[0] = x;
    lastPos[1] = y;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    curProblem = key-'0';
    if (key == 'q' || key == 'Q' || key == 27){
        exit(0);
    }
    glutPostRedisplay();
}

void reshape(int width, int height) {
    windowWidth = width;
    windowHeight = height;
    glutPostRedisplay();
}

//Five routines perform tasks necessary to initialize a window.
int main(int argc, char** argv)
{
    //initializes GLUT and processes any command line arguments
    glutInit(&argc, argv);

    //specifies whether to use an RGBA or color-index color model.You can also specify whether you want a single- or double-buffered window.
    //Finally, you can use this routine to indicate that you want the window to have an associated depth, stencil, and/or accumulation buffer.
    //For example, if you want a window with double buffering, the RGBA color model, and a depth buffer,
    //you might call glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH).
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    //specifies the size, in pixels, of your window.
    glutInitWindowSize(windowWidth, windowHeight);

    //creates a window with an OpenGL context. It returns a unique int identifier for the new window.
    //Be warned: Until glutMainLoop() is called (see next section), the window is not yet displayed.
    glutCreateWindow("HW2");

    //is the first and most important event callback function you will see. Whenever GLUT determines the contents of the window need to be
    //redisplayed, the callback function registered by glutDisplayFunc() is executed. Therefore, you should put all the routines you need
    //to redraw the scene in the display callback function.
    glutDisplayFunc(display);


    glutMotionFunc(mouseMoved);
    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    //All windows that have been created are now shown, and rendering to those windows is now effective. Event processing begins,
    //and the registered display callback is triggered. Once this loop is entered, it is never exited!
    glutMainLoop();

    return 0;
}
