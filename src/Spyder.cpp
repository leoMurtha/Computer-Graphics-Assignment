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
	// cephalo initial position and size
	cephalo.r = 40;
	cephalo.c.x = WINDOW_WIDTH/2;
	cephalo.c.y = WINDOW_HEIGHT/2 + 120; 
	// abdomen initial position and size relative to cephalo
	abdomen.r = cephalo.r*2;
	abdomen.c.x = cephalo.c.x;
	abdomen.c.y = cephalo.c.y - (abdomen.r+cephalo.r); 

	speed = 1.0f;

	// OQ SAO P2 E P3???
	p2 = p3 = 0;
	
	initLegs();

	//updatePos();
}

Circle Spyder::getCephalo(){
	return cephalo;
}

Circle Spyder::getAbdomen(){
	return abdomen;
}

void Spyder::initLegs(){
// » Pernas direita 

// Perna 1 - rightL[0]

	rightL[0].seg[0].x = cephalo.c.x + (cephalo.r * cos(M_PI/3));
	rightL[0].seg[0].y = cephalo.c.y + (cephalo.r * sin(M_PI/3));
	
	
	rightL[0].seg[1].x = rightL[0].seg[0].x + ldX*2 * cos(M_PI/2.5);
	rightL[0].seg[1].y = rightL[0].seg[0].y + ldY*2 * sin(M_PI/2.5);
	
	rightL[0].seg[2].x = rightL[0].seg[1].x + ldX * cos(M_PI/3.5);
	rightL[0].seg[2].y = rightL[0].seg[1].y + ldY * sin(M_PI/3.5);

// Perna 2 e 3 - rightL[1] e rightL[2] (são identicas)

	for(int i=1; i<3;i++){
		rightL[i].seg[0].x = cephalo.c.x + cephalo.r * cos(M_PI/6 * (i-1));
		rightL[i].seg[0].y = cephalo.c.y + cephalo.r * sin(M_PI/6 * (i-1));
		
		rightL[i].seg[1].x = rightL[i].seg[0].x + i*ldX/2 * cos(M_PI/4);
		rightL[i].seg[1].y = rightL[i].seg[0].y + i*ldY/2 * sin(M_PI/4);
		
		rightL[i].seg[2].x = rightL[i].seg[1].x + ldX*2 * cos(19*M_PI/12);
		rightL[i].seg[2].y = rightL[i].seg[1].y + ldY*2 * sin(19*M_PI/12);
	}

// Perna 4
	rightL[3].seg[0].x = cephalo.c.x + (cephalo.r * cos(11*M_PI/6));
	rightL[3].seg[0].y = cephalo.c.y + (cephalo.r * sin(11*M_PI/6));
	
	rightL[3].seg[1].x = rightL[3].seg[0].x + ldX/2 * cos(M_PI/4);
	rightL[3].seg[1].y = rightL[3].seg[0].y + ldY/2 * sin(M_PI/4);
	
	rightL[3].seg[2].x = rightL[3].seg[1].x + ldX*4 * cos(19*M_PI/12);
	rightL[3].seg[2].y = rightL[3].seg[1].y + ldY*4 * sin(19*M_PI/12);

// » Pernas esquerdas

// Perna 1 - leftL[0]

	leftL[0].seg[0].x = cephalo.c.x - cephalo.r * cos(M_PI/3);
	leftL[0].seg[0].y = cephalo.c.y + cephalo.r * sin(M_PI/3);
	
	leftL[0].seg[1].x = leftL[0].seg[0].x - ldX*2 * cos(M_PI/2.5);
	leftL[0].seg[1].y = leftL[0].seg[0].y + ldY*2 * sin(M_PI/2.5);
	
	leftL[0].seg[2].x = leftL[0].seg[1].x - ldX * cos(M_PI/3.5);
	leftL[0].seg[2].y = leftL[0].seg[1].y + ldY * sin(M_PI/3.5);

// Perna 2 e 3 - leftL[1] e leftL[2] (são identicas)

	for(int i=1; i<3;i++){
		leftL[i].seg[0].x = cephalo.c.x - (cephalo.r * cos(M_PI/6 * (i-1)));
		leftL[i].seg[0].y = cephalo.c.y + (cephalo.r * sin(M_PI/6 * (i-1)));
		
		leftL[i].seg[1].x = leftL[i].seg[0].x - i*ldX/2 * cos(M_PI/4);
		leftL[i].seg[1].y = leftL[i].seg[0].y + i*ldY/2 * sin(M_PI/4);
		
		leftL[i].seg[2].x = leftL[i].seg[1].x - ldX*2 * cos(19*M_PI/12);
		leftL[i].seg[2].y = leftL[i].seg[1].y + ldY*2 * sin(19*M_PI/12);
	}

// Perna 4
	leftL[3].seg[0].x = cephalo.c.x - (cephalo.r * cos(11*M_PI/6));
	leftL[3].seg[0].y = cephalo.c.y + (cephalo.r * sin(11*M_PI/6));
	
	leftL[3].seg[1].x = leftL[3].seg[0].x - ldX/2 * cos(M_PI/4);
	leftL[3].seg[1].y = leftL[3].seg[0].y + ldY/2 * sin(M_PI/4);
	
	leftL[3].seg[2].x = leftL[3].seg[1].x - ldX*4 * cos(19*M_PI/12);
	leftL[3].seg[2].y = leftL[3].seg[1].y + ldY*4 * sin(19*M_PI/12);

}



// Rotates the body of the spider
void Spyder::turn(Point f){
	double angle = getAngle(abdomen.c, cephalo.c, f);
	
	cephalo.c = rotate(cephalo.c, abdomen.c, angle);

	for(int i = 0; i < 4; i++){	
		for(int j = 0; j < 3; j++){
			leftL[i].seg[j] = rotate(leftL[i].seg[j], abdomen.c, angle);
			rightL[i].seg[j] = rotate(rightL[i].seg[j], abdomen.c, angle);
		}
	}
	
}

// makes legs move, simuletion the spider walking
void Spyder::legsMovement(){
	if(p2 < 15){
			leftL[0].seg[1] = rotate(leftL[0].seg[1],leftL[0].seg[0], 0.1);
			leftL[0].seg[2] = rotate(leftL[0].seg[2],leftL[0].seg[0], 0.1);
			rightL[0].seg[1] = rotate(rightL[0].seg[1],rightL[0].seg[0], 0.1);
			rightL[0].seg[2] = rotate(rightL[0].seg[2],rightL[0].seg[0], 0.1);
			
			p2++;
		}else if(p3 < 15){
			leftL[0].seg[1] = rotate(leftL[0].seg[1],leftL[0].seg[0], -0.1);
			leftL[0].seg[2] = rotate(leftL[0].seg[2],leftL[0].seg[0], -0.1);
			rightL[0].seg[1] = rotate(rightL[0].seg[1],rightL[0].seg[0], -0.1);
			rightL[0].seg[2] = rotate(rightL[0].seg[2],rightL[0].seg[0], -0.1);
			
			p3++;
	}else p2 = p3 = 0;		
		
}


// makes all body parts of the spider move in the same direction
void Spyder::move(Point dirVec, Point p){ 

	// stops movement close to the destination point
	if(dist(cephalo.c, p) > 1){

		
		// destini finding
		Point dest;
		dest.x = dirVec.x*speed;
		dest.y = dirVec.y*speed;

		// Body translation
		cephalo.c = translation(cephalo.c,dest);
		abdomen.c = translation(abdomen.c,dest);
		// Legs translation
		for(int i = 0; i < 4; i++){	
			for(int j = 0; j < 3; j++){
				leftL[i].seg[j] = translation(leftL[i].seg[j],dest);
				rightL[i].seg[j] = translation(rightL[i].seg[j],dest);			
			}
		}

		legsMovement();
		
	}
}

/* Draws the entire spyder */
void Spyder::draw(){

	// body drawing
	circle(abdomen);
	circle(cephalo);

	//line(cephalo.c, abdomen.c);

	// legs drawing
	for(int i = 0; i < 4; i++){
		line(leftL[i].seg[0], leftL[i].seg[1]);
		line(leftL[i].seg[1], leftL[i].seg[2]);
		line(rightL[i].seg[0], rightL[i].seg[1]);
		line(rightL[i].seg[1], rightL[i].seg[2]);
	}

}

