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
	cephalo.r = 40;
	cephalo.c.x = WINDOW_WIDTH/2;
	cephalo.c.y = WINDOW_HEIGHT/2 + 120; 
	abdomen.r = cephalo.r*2;

	speed = 1.0f;
	
	updatePos();
}

void Spyder::updatePos(){
	abdomen.c.x = cephalo.c.x;
	abdomen.c.y = cephalo.c.y - (abdomen.r+cephalo.r); 
	
	initLegs();
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

Circle Spyder::getCephalo(){
	return cephalo;
}

Circle Spyder::getAbdomen(){
	return abdomen;
}

/* Function called inside the move in case the there is a need for the spyder to move */ 
void Spyder::turn(Point f){
	float angle = getAngle(abdomen.c, cephalo.c, f);
	printf("%f\n", cos(230));
	/*
		Pra estacionar tem que
		colocar turn em move pra toda vez girar
	*/

	/*
	angle = 180*angle/M_PI;
	glTranslatef(abdomen.c.x, abdomen.c.y, 0);
	if(f.x - cephalo.c.x < 0) glRotatef(angle, 0, 0, 1.0);
	else if(f.x - cephalo.c.x > 0) glRotatef(-angle, 0, 0, 1.0);
	glTranslatef(-abdomen.c.x, -abdomen.c.y, 0); */

	if((cephalo.c.x - f.x) < 0){
		 if(cephalo.c.y > abdomen.c.y) angle = -angle;
	}else if(cephalo.c.x - f.x > 0){
		 if(cephalo.c.y < abdomen.c.y) angle = -angle;
	}

	/* MEIO QUE TRANSLADANDO EIXO pra origem */
	cephalo.c.x -= abdomen.c.x;
	cephalo.c.y -= abdomen.c.y;
	
	float xT = cephalo.c.x;
	cephalo.c.x =  xT * cos(angle) - cephalo.c.y * sin(angle);
	cephalo.c.y =  xT * sin(angle) + cephalo.c.y * cos(angle);
	cephalo.c.x += abdomen.c.x;
	cephalo.c.y += abdomen.c.y;
	
}

void Spyder::move(Point dirVec, Point p){ // FAZER MOVIMENTO POR VETOR
	// VETOR DE DIREÇÃO
	if(dist(cephalo.c, p) > 1){

		cephalo.c.x += dirVec.x*speed;
		cephalo.c.y += dirVec.y*speed;

		abdomen.c.x += dirVec.x*speed;
		abdomen.c.y += dirVec.y*speed;		
	}
	
	initLegs();
	
}

/* Draws the entire spyder */
void Spyder::draw(){
	circle(abdomen);
	circle(cephalo);

	line(cephalo.c, abdomen.c);
	for(int i = 0; i < 4; i++){
		line(leftL[i].seg[0], leftL[i].seg[1]);
		line(leftL[i].seg[1], leftL[i].seg[2]);
		line(rightL[i].seg[0], rightL[i].seg[1]);
		line(rightL[i].seg[1], rightL[i].seg[2]);
	}

}

