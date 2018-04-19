#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <limits.h>
#include <string>
#include <vector>
#include <string.h>
#include <T1.h>
#include <Spyder.h>

Spyder spyder = Spyder();
Point p;

float dist(Point i, Point f){
	return sqrt(pow((i.x - f.x),2) + pow((i.y - f.y),2));
}

void line(Point p1, Point p2){
	glLineWidth(3);
	glColor3f(1,0,0);
	glBegin(GL_LINES);
	glVertex3f(p1.x, p1.y, 0);
	glVertex3f(p2.x, p2.y, 0);
	glEnd();
}

void circle(Circle t){
	double thetha = 0;
		glBegin(GL_LINE_STRIP);
		for(int i = 0; i <= lines; i++, thetha = (2*M_PI*i)/lines) glVertex2f(t.c.x + t.r*cos(thetha), t.c.y + t.r*sin(thetha));		
		glEnd();
}


void display(){
  glClear(GL_COLOR_BUFFER_BIT);
  
  glColor3f(0,0,0);
  spyder.draw();

  glFlush();
}

void defaultInit(){
	// Sets the color thar glClear will 'paint' in RGBA
	glClearColor(1.0, 1.0, 1.0, 1.0);
	// Sets the matrix with projection wich will do alot of matrix operations
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLineWidth(3); 
	glEnable(GL_LINE_SMOOTH);
		
	// define a 2D orthographic projection matrix
	gluOrtho2D(0, WINDOW_WIDTH, 0 , WINDOW_HEIGHT);
}

void update(int val){
	glutTimerFunc(fps, update, 0); // Calls update again
	glutPostRedisplay(); // Calls the display function again
}

void mouse(GLint button, GLint state, GLint x, GLint y){
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		p.x = x;
		p.y = WINDOW_WIDTH - y;				
		
		printf("%f %f\n", p.x, p.y);	
		spyder.move(p);
		glutPostRedisplay();
	}
	
}


int main(int argc, char *argv[]){
	// Start up the glut	
	glutInit(&argc, argv);
	// Info for openGL about the screen/buffers this case 2D
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	// Getting device screen WINDOW_WIDTH and height
	GLint screen_width = glutGet(GLUT_SCREEN_WIDTH), screen_height = glutGet(GLUT_SCREEN_HEIGHT);
	// Centering the window
	glutInitWindowPosition((screen_width - WINDOW_WIDTH)/2, (screen_height - WINDOW_HEIGHT)/2);
	// Window size
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	// Creating window passing a title
	glutCreateWindow("Trabalho Parte 1");

	defaultInit();


	glutMouseFunc(mouse);
	glutDisplayFunc(display);
	glutTimerFunc(fps, update, 0);
	
	
	glutMainLoop();


	return EXIT_SUCCESS;
}