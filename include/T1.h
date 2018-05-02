#ifndef _T1_H_
#define _T1_H_

using namespace std;

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT  600
#define fps 100/6
#define W 119
#define S 115
#define UP 101
#define DWN 103
#define lines 1000

typedef struct {
	float x,y;
}Point;

typedef struct {
	Point c;
	float r;
}Circle;

void circle(Circle);

void line(Point, Point);

float dist(Point, Point);

void translate(Point*, Point, int);

void scale(Point*, float, int);

void rotate(Point *, float, int);

void rotate2(Point, float);

float getAngle(Point, Point, Point);

#endif