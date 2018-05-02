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
Point p,dirVec;
bool moved;

float dot2D(Point A, Point B){
	return (A.x)*(B.x) + (A.y)*(B.y);
}

float dist(Point i, Point f){
	return sqrt(pow((i.x - f.x),2) + pow((i.y - f.y),2));
}

float getAngle(Point a, Point b, Point c){
	Point A,B;
	A.x = b.x - a.x;
	A.y = b.y - a.y;
	B.x = c.x - a.x;
	B.y = c.y - a.y;
	return acos(dot2D(A,B)/(dist(b,a)*dist(c,a)));
}

/* Uses first point as base */
void translate(Point *v, Point t, int n){
	int dx = t.x - v[0].x;
	int dy = t.y - v[0].y;

	for(int i = 0; i < n; i++){
		v[i].x += dx;
		v[i].y += dy;
	}
}

void scale(Point *v, float s, int n){
	for(int i = 0; i < n; i++){
		v[i].x *= s;
		v[i].y *= s;
	}
}

void rotate2(Point f, float angle){
	//glMatrixMode(GL_MODELVIEW);
	
}

void rotate(Point *v, float angle, int n){
	for(int i = 0; i < n; i++){
		double xT = v[i].x;
		v[i].x = v[i].x*cos(angle) - v[i].y*sin(angle);
		v[i].y = xT*sin(angle) + v[i].y*cos(angle);
	}
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
  	
	glPushMatrix();	
	//if(moved){
		spyder.turn(p);  
		moved = false;
		printf("PONTO CLICADO = (%f,%f)\n", p.x,p.y);
	//}
	spyder.move(dirVec,p);
	spyder.draw();

	glPopMatrix();



	glPushMatrix();
	line(spyder.getAbdomen().c, p);
	glPopMatrix();


  	glFlush();
  	glutPostRedisplay();

}

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
	
	p.x = WINDOW_WIDTH/2;
	p.y = WINDOW_HEIGHT/2 + 120;	
	moved = false;
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
		p.y = WINDOW_HEIGHT - y;

		// encontrando vetor direcao
		dirVec.x = p.x - (spyder.getCephalo().c.x);
		dirVec.y = p.y - (spyder.getCephalo().c.y);		
		// normalizando
		float dirVecSize = sqrt((dirVec.x*dirVec.x)+(dirVec.y*dirVec.y));
		dirVec.x /= dirVecSize;
		dirVec.y /= dirVecSize;

		moved = true;
		glutPostRedisplay();
	}
	
}

void idle(void){
	glPushMatrix();

	if(moved){
		spyder.turn(p);
		moved = false;
		printf("asdsad\n");
	}
	glPopMatrix();

	//spyder.move(p);

    glutPostRedisplay();
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
	//glutIdleFunc(idle);

	
	glutMainLoop();

	return EXIT_SUCCESS;
}