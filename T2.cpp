#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <T2.h>
#include <Spider.h>
#include <Transformations.h>
#include <iostream>
#include <math.h>

float abRadius = 0.5f;
float ceRadius = abRadius/2.0;


Point p;

/* KIBEI HARD PARTE DE ILUMINAçÃO TEM QUE VER COMO FUNFA */
GLfloat mat_diffuse [] = {1.0, 1.0, 1.0, 1.0};
GLfloat mat_specular [] = {1.0, 1.0, 1.0, 1.0};
GLfloat mat_shininess [] = {100};
GLfloat mat_emission [] = {0.05, 0.05, 0.05, 0.05};

void ilumination(){
     GLfloat light_position[] = {0, 1, 0, 0}; //Luz Emitida do x=0,y=0,z=0 (SOL)

     glLightfv(GL_LIGHT0,GL_POSITION, light_position);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
     glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
     glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
     glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
     glEnable (GL_LIGHTING);
     glEnable (GL_LIGHT0);
     glEnable(GL_COLOR_MATERIAL);
}

void patas(){
	glBegin(GL_LINES); // pega pontos dois a dois
		
		// Pata 1 ---------
		glVertex3d(0.0f,ceRadius,0.0f);
		glVertex3d(0.0f,1.5*ceRadius,0.0f);

		glVertex3d(0.0f,1.5*ceRadius,0.0f);
		glVertex3d(0.0f,abRadius+ceRadius,-abRadius);

		// Pata 2 --------
		glVertex3d(ceRadius*cos(3*M_PI/8),ceRadius*sin(3*M_PI/8),0.0f);
		glVertex3d(ceRadius*cos(3*M_PI/8),1.5*ceRadius,0.0f);

		//glVertex3d(ceRadius*cos(M_PI/4),2*ceRadius*sin(M_PI/4),0.0f);
		//glVertex3d(0.0f,abRadius,-abRadius);

		// Pata 3 ----------
		glVertex3d(ceRadius*cos(5*M_PI/8),ceRadius*sin(5*M_PI/8),0.0f);
		glVertex3d(ceRadius*cos(5*M_PI/8),1.5*ceRadius,0.0f);


		// Pata 4 ----------
		glVertex3d(ceRadius*cos(M_PI/8),ceRadius*sin(M_PI/8),0.0f);
		glVertex3d(ceRadius*cos(M_PI/8),1.5*ceRadius*sin(M_PI/8),0.0f);


	glEnd();
}

// Desenha a aranha
void drawSpider(){
	// Red color used to draw.
    glColor3f(1, 0, 0); 
    // Desenha abdomen no meio da tela
	glutSolidSphere(abRadius,100,100);

	glColor3f(0, 1, 0); 

	// Tranlada pra cima do abdomen e desenha o cephalotorax
    glTranslatef(ceRadius+abRadius, 0.0f, 0.0f);
	glutSolidSphere(ceRadius,100,100);
	
	glColor3f(0,0,0);
	patas();
}

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
	drawSpider();
	glPopMatrix();

    /*Tela direita de baixo De frente por Z*/
    glPushMatrix();
    glViewport(WINDOW_WIDTH/2, 0, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    glLoadIdentity();
    gluLookAt(5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    drawSpider();
    glPopMatrix();

    /* Tela esquerda de cima Na de lado por X */ 
    glPushMatrix();
    glViewport(0, WINDOW_HEIGHT/2, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    drawSpider();
    glPopMatrix();

    /* Tela direita de cima Aleatório */
    glPushMatrix();
    glViewport(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    glLoadIdentity();
    gluLookAt(3.0, 2.0, 10.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
    drawSpider();
    glPopMatrix();

	/*Dispara os comandos APENAS uma vez */
  	glFlush();
}

// Check for mouse input
void mouse(GLint button, GLint state, GLint x, GLint y){

	// Makes destination alterations for mouse left button clicks
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		p.x = x;
		p.y = WINDOW_HEIGHT - y;
	}
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

void keyboardSpecial(GLint key, GLint x, GLint y){ 
    switch(key){
	  	case GLUT_KEY_UP:
	  		printf("Andando pra frente\n");
	  		break;
	  	case GLUT_KEY_DOWN:
	  		printf("Andando pra tras? De ré???\n");
	  		break;
	  	case GLUT_KEY_LEFT:
	  		printf("Rotacionando/virando pra esquerda\n");
	  		break;
	  	case GLUT_KEY_RIGHT:
	  		printf("Rotacionando/virando pra direita\n");
	  		break;
	  }
	  
  std::cout<<"Tecla: "<<(GLint) key<<" (x:"<<x<<", y:"<<y<<")\n"; 
  
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