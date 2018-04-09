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
#include <Spyder.h>
#include <T1.h>

using namespace std;

/* Creates a random spyder, can be changed later */
Spyder::Spyder(){
	abdomen.r = 80;
	abdomen.x = WINDOW_WIDTH/2;
	abdomen.y = WINDOW_HEIGHT/2; 
	
	cephalo.r = abdomen.r/2;
	cephalo.x = abdomen.x;
	cephalo.y = abdomen.y + (abdomen.r+cephalo.r); 
	
	initLegs();

	
}

void Spyder::initLegs(){
	/* Initializing the segments attached to the body */
	float dT = M_PI/9;
		for(int i = 0; i < 4; i++){
			leftL[i].seg[0].x = cephalo.x + cephalo.r*cos(-((M_PI+dT) - dT*i));
			leftL[i].seg[0].y = cephalo.y + cephalo.r*sin(-((M_PI+dT) - dT*i));
			rightL[i].seg[0].x = cephalo.x + cephalo.r*cos(-((2*M_PI+dT) - dT*i));
			rightL[i].seg[0].y = leftL[i].seg[0].y;
			for(int j = 1; j < 3; j++){
				leftL[i].seg[j].x = leftL[i].seg[0].x - ldX;
				leftL[i].seg[j].y = leftL[i].seg[0].y - ldY*j;
				rightL[i].seg[j].x = rightL[i].seg[0].x + ldX;
				rightL[i].seg[j].y = leftL[i].seg[j].y;	 	
			}
		}
}

Circle Spyder::getCephalo(){
	return cephalo;
}

Circle Spyder::getAbdomen(){
	return abdomen;
}

/* Draws the entire spyder */
void Spyder::draw(){
	circle(abdomen);
	circle(cephalo);

	for(int i = 0; i < 4; i++){
		line(leftL[i].seg[0], leftL[i].seg[1]);
		line(leftL[i].seg[1], leftL[i].seg[2]);
		line(rightL[i].seg[0], rightL[i].seg[1]);
		line(rightL[i].seg[1], rightL[i].seg[2]);
	}
	
}

