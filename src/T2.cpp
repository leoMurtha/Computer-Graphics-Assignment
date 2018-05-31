#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>

#include <T2.h>
#include <Spider.h>
//#include <Transformations.h>
#include <math.h>
#include <ilumination.h>
#include <deviceInput.h>

//Point p;

Spider spider = Spider();

// Display all drawings and atualizations on the screen
void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    
    ilumination();
	
    /* Tela esquerda de baixo Por cima em Y */
    glPushMatrix();
    glViewport(0, 0, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    glLoadIdentity();
    gluLookAt(0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
	spider.draw();
	glPopMatrix();

    /*Tela direita de baixo De frente por Z*/
    glPushMatrix();
    glViewport(WINDOW_WIDTH/2, 0, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    glLoadIdentity();
    gluLookAt(5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    spider.draw();
    glPopMatrix();

    /* Tela esquerda de cima Na de lado por X */ 
    glPushMatrix();
    glViewport(0, WINDOW_HEIGHT/2, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    spider.draw();
    glPopMatrix();

    /* Tela direita de cima Aleatório */
    glPushMatrix();
    glViewport(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    glLoadIdentity();
    gluLookAt(3.0, 2.0, 10.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
    spider.draw();
    glPopMatrix();

	/*Dispara os comandos APENAS uma vez */
  	glFlush();
}

void update(int val){
	glutTimerFunc(fps, update, 0); // Calls update again
	glutPostRedisplay(); // Calls the display function again
}

// Initiates the screen 
void defaultInit(){
	// Sets the color thar glClear will 'paint' in RGBA
	glClearColor(1, 1, 1, 1);
	// Sets the matrix with projection wich will do alot of matrix operations
	glMatrixMode(GL_PROJECTION); // signal that I want to work with the projection stack
	glLoadIdentity(); // make sure that the projection stack doesn't already have anything on it
	glMatrixMode(GL_MODELVIEW); // the rest of my app will only change MODELVIEW 
	glLoadIdentity();	

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

int main(int argc, char *argv[]){

	// Start up the glut	
	glutInit(&argc, argv);
	// Info for openGL about the screen/buffers
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	// Getting device screen WINDOW_WIDTH and height
	GLint screen_width = glutGet(GLUT_SCREEN_WIDTH), screen_height = glutGet(GLUT_SCREEN_HEIGHT);
	// Centering the window
	glutInitWindowPosition((screen_width - WINDOW_WIDTH)/2, (screen_height - WINDOW_HEIGHT)/2);
	// Window size
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	// Creating window passing a title
	glutCreateWindow(".");

	defaultInit();

	glutMouseFunc(mouse);
	glutDisplayFunc(display);
	glutSpecialFunc(keyboardSpecial);
	glutReshapeFunc(reshape);
	glutTimerFunc(fps, update, 0);
	
	glutMainLoop();

	return EXIT_SUCCESS;
}