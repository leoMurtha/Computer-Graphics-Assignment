#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <Geometrics.h>

// Calculates the distance between point a and b
float dist(Point a, Point b){
	return sqrt(pow((a.x - b.x),2) + pow((a.y - b.y),2) + pow((a.z - b.z),2));
}

Point createPoint(float x,float y,float z){
	Point p;

	p.x = x;p.y = y;p.z = z;

	return p;
}

// create new vector from point a to b
Vector createVector(Point a, Point b){
		Vector v;

		v.x = b.x - a.x;
		v.y = b.y - a.y;
		v.z = b.z - a.z;

		v.size = dist(a,b);

		return v;
}

// Creates a new vector based on points a and b and normalizes it
Vector createNormalizedVector(Point a, Point b){
	Vector v = createVector(a,b);

	v.x /= v.size;
	v.y /= v.size;
	v.z /= v.size;

	v.size =1.0f;

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