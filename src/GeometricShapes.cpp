#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <Geometrics.h>
#include <Transformations.h>

// Draws a line between point a and b
void line(Point a, Point b){

	glLineWidth(3);
	glColor3f(1,0,0);
	glBegin(GL_LINES);
	glVertex3f(a.x, a.y, 0);
	glVertex3f(b.x, b.y, 0);
	glEnd();

}

// Draws a circle 
void circle(Circle t){
	double thetha = 0;

	glBegin(GL_LINE_STRIP);
	for(int i = 0; i <= lines; i++, thetha = (2*M_PI*i)/lines) glVertex2f(t.c.x + t.r*cos(thetha), t.c.y + t.r*sin(thetha));		
	glEnd();
}