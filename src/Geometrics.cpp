#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <Geometrics.h>

// Calculates the distance between point a and b
float dist(Point a, Point b){
	return sqrt(pow((a.x - b.x),2) + pow((a.y - b.y),2));
}

// create new vector from point a to b
Point createVector(Point a, Point b){
		Point v = b;

		v.x -= a.x;
		v.y -= a.y;

		return v;
}

// Creates a new vector based on points a and b and normalizes it
Point createNormalizedVector(Point a, Point b){

	double vectorSize = dist(a,b);

	Point v = createVector(a,b);

	v.x /= vectorSize;
	v.y /= vectorSize;

	return v;
}

// Draws a line between point a and b
void line(Point a, Point b){

	glLineWidth(6);
	glColor3f(0.4f, 0.30f, 0.01f);
	glBegin(GL_LINES);
	glVertex3f(a.x, a.y, 0);
	glVertex3f(b.x, b.y, 0);
	glEnd();

}

// Draws a circle 
void circle(Circle t){
	double thetha = 0;

	glColor4f(0.0f, 0.0f, 0.0f, 0.0f);//orange/brown
	
	glBegin(GL_LINE_STRIP);
	for(int i = 0; i <= lines; i++, thetha = (2*M_PI*i)/lines) glVertex2f(t.c.x + t.r*cos(thetha), t.c.y + t.r*sin(thetha));		
	glEnd();
}

void filledCircle(Circle t, bool color){
    Point aux;
    
    if(color) glColor3f(0.4f, 0.30f, 0.01f);
	else glColor3f(0.0f, 0.0f, 0.0f);
	
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(t.c.x,t.c.y);

    for (float angle=.0f;angle<(2*M_PI) + 1;angle+=0.2){
        aux.x = t.c.x+sin(angle)*t.r;
        aux.y = t.c.y+cos(angle)*t.r;
        glVertex2f(aux.x,aux.y);
    }

    glEnd();
}