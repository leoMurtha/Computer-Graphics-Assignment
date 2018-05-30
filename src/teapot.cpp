#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

GLfloat xRotated, yRotated, zRotated, xT;
GLdouble size=1;
int width = 1400, height = 800;
void display(void);
void reshape(int x, int y);
void idle(void)
{
    xT += 0.001;
	xRotated += 0.01;
	yRotated += 0.01;
    zRotated += 0.01; 
    display();
}

int main (int argc, char **argv)
{
    glutInit(&argc, argv); 
    glutInitWindowSize(width,height);
    glutCreateWindow("Teapot");
    xRotated = yRotated = zRotated = 3.0;
    xRotated=33;
    yRotated=33;
    xT = 0;
 
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}

void rotate(){
    glRotatef(xRotated, 1.0, 0.0, 0.0);
    //glRotatef(yRotated, 0.0, 1.0, 0.0);
    //glRotatef(zRotated, 0.0, 0.0, 1.0);
}

void display(void)
{

    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
    // clear the identity matrix.
    glLoadIdentity();
    
    // Red color used to draw.
    glColor3f(.5, 0.7, 0.0); 
    
    /* Por cima em Y */
    glPushMatrix();
    glViewport(0, height/2.5, width/4, height/4);
    glLoadIdentity();
    gluLookAt(0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -xT, 0.0);
    glutWireTeapot(1);
    glPopMatrix();

    /* De lado por X */
    glViewport(width/4, height/2.5, width/4, height/4);
    glLoadIdentity();
    gluLookAt(5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    rotate();
    glutWireTeapot(1);

    /* Na frente da cena por Z */
    glViewport(0.5*width, height/2.5, width/4, height/4);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    rotate();
    glutWireTeapot(1);

    glViewport(width*0.75, height/2, width/4, height/4);
    glLoadIdentity();
    gluLookAt(3.0, 2.0, 10.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
    rotate();
    glutWireTeapot(1);

    glFlush();        
    // sawp buffers called because we are using double buffering 
   // glutSwapBuffers();
}

void reshape(int x, int y)
{
    if (y == 0 || x == 0) return;   
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity(); 
    gluPerspective(39.0,(GLdouble)x/(GLdouble)y,0.6,21.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}