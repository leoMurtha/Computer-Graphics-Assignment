#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <Transformations.h>



float dot2D(Point A, Point B){
	return (A.x)*(B.x) + (A.y)*(B.y);
}

float getAngle(Point a, Point b, Point c){
	Point A,B;

	A.x = b.x - a.x;
	A.y = b.y - a.y;

	B.x = c.x - a.x;
	B.y = c.y - a.y;

	return acos(dot2D(A,B)/(dist(b,a)*dist(c,a)));
}


// Makes the rotation of an axis formed by two dots, u and v
Point rotate(Point v, Point u, float angle){

	v.x -= u.x;
	v.y -= u.y;

	double xT = v.x;
	v.x = v.x*cos(angle) - v.y*sin(angle);
	v.y = xT*sin(angle) + v.y*cos(angle);
		
	v.x += u.x;
	v.y += u.y;
	
	return v;
}