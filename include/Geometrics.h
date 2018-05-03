#ifndef _GEOMETRICS_H_
#define _GEOMETRICS_H_

using namespace std;

#define lines 1000

typedef struct {
	float x,y;
}Point;

typedef struct {
	Point c;
	float r;
}Circle;

Point createNormalizedVector(Point,Point);

float dist(Point, Point);

void circle(Circle);

void line(Point, Point);


#endif