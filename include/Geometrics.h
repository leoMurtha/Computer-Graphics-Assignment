#ifndef _GEOMETRICS_H_
#define _GEOMETRICS_H_

using namespace std;

#define lines 1000

typedef struct {
	float x,y,z;
}Point;

typedef struct {
	Point c;
	float r;
}Circle;

Point createNormalizedVector(Point,Point);

float dist(Point, Point);

void circle(Circle);

void filledCircle(Circle, bool);

void line(Point, Point);

Point createPoint(float,float,float);

#endif