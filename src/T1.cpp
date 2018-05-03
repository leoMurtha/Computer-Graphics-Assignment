#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <T1.h>
#include <Spyder.h>
#include <Transformations.h>

// BIBLIOTECAS QUE PARECEM NAO SER USADAS ( EXCLUIR DEPOIS )
//#include <cstdlib>
//#include <iostream>
//#include <math.h>
//#include <limits.h>
//#include <string>
//#include <vector>
//#include <string.h>
// =========================================================


Spyder spyder = Spyder();
Point destPoint,dirVec;
bool moved, mouseClicked = false;


// Display all drawings and atualizations on the screen
void display(){
	glClear(GL_COLOR_BUFFER_BIT);
  	glColor3f(0,0,0);
  	  	

  	if(mouseClicked){
  		// rotates the spyder
		spyder.turn(destPoint);
		
		// find new movement direction
		dirVec = createNormalizedVector(spyder.getCephalo().c,destPoint);

		mouseClicked = false;
	}

	spyder.move(dirVec, destPoint);
	spyder.draw();
	

  	glFlush();
}

// Check for mouse input
void mouse(GLint button, GLint state, GLint x, GLint y){

	// Makes destination alterations for mouse left button clicks
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		// resets the spider destination
		destPoint.x = x;
		destPoint.y = WINDOW_HEIGHT - y;
		// inform that mouse has a new dest
		mouseClicked = true;
	}
	
}


void update(int val){
	glutTimerFunc(fps, update, 0); // Calls update again
	glutPostRedisplay(); // Calls the display function again
}


// Initiates the screen 
void defaultInit(){
	// Sets the color thar glClear will 'paint' in RGBA
	glClearColor(1.0, 1.0, 1.0, 1.0);
	// Sets the matrix with projection wich will do alot of matrix operations
	glMatrixMode(GL_PROJECTION); // signal that I want to work with the projection stack
	glLoadIdentity(); // make sure that the projection stack doesn't already have anything on it
	glMatrixMode(GL_MODELVIEW); // the rest of my app will only change MODELVIEW 
	glLoadIdentity();
	glLineWidth(3); 
	glEnable(GL_LINE_SMOOTH);
	
	destPoint.x = WINDOW_WIDTH/2;
	destPoint.y = WINDOW_HEIGHT/2 + 120;	

	// define a 2D orthographic projection matrix
	gluOrtho2D(0, WINDOW_WIDTH, 0 , WINDOW_HEIGHT);
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