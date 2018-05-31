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
#include <Spider.h>
#include <T2.h>


using namespace std;


	/* Creates a random spyder, can be changed later */
	Spider::Spider(){
		
			// cephalo initial position and size
			cephalo.r = 0.25f;
			

			// abdomen initial position and size relative to cephalo
			abdomen.r = cephalo.r*2;

			cephalo.c = createPoint(cephalo.r+abdomen.r,0.0f,0.0f);
			abdomen.c = createPoint(0.0f,0.0f,0.0f);

			direction = createNormalizedVector(abdomen.c,cephalo.c);
			speed = 0.1f;
			angle = 0.0f;

		initLegs();
	}

	Circle Spider::getCephalo(){
	return cephalo;
	}

	Circle Spider::getAbdomen(){
		return abdomen;
	}


	void Spider::initLegs(){

		//pata 1
		rightLeg[0].joint[0] = createPoint(0.0f,cephalo.r,0.0f);
		rightLeg[0].joint[1] = createPoint(0.0f,1.5*cephalo.r,0.0f);
		rightLeg[0].joint[2] = createPoint(0.0f,abdomen.r+cephalo.r,-abdomen.r);

		//pata 2
		rightLeg[1].joint[0] = createPoint(cephalo.r*cos(3*M_PI/8),cephalo.r*sin(3*M_PI/8),0.0f);
		rightLeg[1].joint[1] = createPoint(cephalo.r*cos(3*M_PI/8),1.5*cephalo.r,0.0f);
		rightLeg[1].joint[2] = createPoint(cephalo.r*cos(3*M_PI/8),1.5*cephalo.r,0.0f);// MUDAR

		//pata 3
		rightLeg[2].joint[0] = createPoint(cephalo.r*cos(5*M_PI/8),cephalo.r*sin(5*M_PI/8),0.0f);
		rightLeg[2].joint[1] = createPoint(cephalo.r*cos(5*M_PI/8),1.5*cephalo.r,0.0f);
		rightLeg[2].joint[2] = createPoint(cephalo.r*cos(5*M_PI/8),1.5*cephalo.r,0.0f);// MUDAR

		//pata 4
		rightLeg[3].joint[0] = createPoint(cephalo.r*cos(M_PI/8),cephalo.r*sin(M_PI/8),0.0f);
		rightLeg[3].joint[1] = createPoint(cephalo.r*cos(M_PI/8),1.5*cephalo.r*sin(M_PI/8),0.0f);
		rightLeg[3].joint[2] = createPoint(cephalo.r*cos(M_PI/8),1.5*cephalo.r*sin(M_PI/8),0.0f);// MUDAR

	}

	// desenha uma perna
	void drawLeg(Leg l){
		for(int i=1;i<3;i++){	
			glVertex3d(l.joint[i-1].x,l.joint[i-1].y,l.joint[i-1].z);
			glVertex3d(l.joint[i].x,l.joint[i].y,l.joint[i].z);
		}	 
	}

	// Desenha todas as pernas da aranha
	void Spider::drawLegs(){
		glBegin(GL_LINES); // pega pontos dois a dois
		
		for (int i=0;i<4;i++) drawLeg(rightLeg[i]);
		//for (int i=0;i<4;i++) drawLeg(leftLeg[i]);	

		glEnd();
	}

	// Desenha a aranha
	void Spider::draw(){
		// Red color used to draw.
   		glColor3f(1, 0, 0);


	    // Desenha abdomen no meio da tela

   		// Levar centro ate a posicao atual para rotacionar
   		glTranslatef(abdomen.c.x, abdomen.c.y, abdomen.c.z);
   		glRotatef(angle,0.0f,1.0f,0.0f);
   		
	    glutSolidSphere(abdomen.r,100,100);	

		//glColor3f(0, 1, 0);

		// Tranlada pra cima do abdomen e desenha o cephalotorax
	    glTranslatef(cephalo.c.x, cephalo.c.y, cephalo.c.z);
		glutSolidSphere(cephalo.r,100,100);	
		//glColor3f(0,0,0);
		drawLegs();
		glTranslatef((-1.0f)*cephalo.c.x, (-1.0f)*cephalo.c.y, (-1.0f)*cephalo.c.z);
   		

		glRotatef((-1.0f)*angle,0.0f,1.0f,0.0f);
   		glTranslatef((-1.0f)*abdomen.c.x, (-1.0f)*abdomen.c.y, (-1.0f)*abdomen.c.z);
		
		// desenho do vetor direcao para testes
		/*glBegin(GL_LINES);
		glVertex3d(0.0f,0.0f,0.0f);
		glVertex3d(direction.x,direction.y,direction.z);
		glEnd();*/
		
	}

	// Animacoes das patas
	void Spider::legsAnimation(){

	}

	// Movimentacao da Aranha em uma direcao
	void Spider::move(){

		// inicia as animacoes das pernas enquanto a aranha se movimenta
		//legsAnimation();

		abdomen.c.x += (direction.x)*speed;
		abdomen.c.y += (direction.y)*speed;
		abdomen.c.z += (direction.z)*speed;
		
	}	

	// Mudanca de direcao da aranha
	void Spider::turn(float ang){
		
		double zT = direction.z;
		direction.z = direction.z*cos(ang*(M_PI/(180.0f))) - direction.x*sin(ang*(M_PI/(180.0f)));
		direction.x = zT*sin(ang*(M_PI/(180.0f))) + direction.x*cos(ang*(M_PI/(180.0f)));

		angle += ang;

	}

