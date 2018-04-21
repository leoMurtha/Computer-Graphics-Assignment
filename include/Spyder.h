#ifndef _SPYDER_H_
#define _SPYDER_H_

#include <T1.h>

typedef struct {
	Point seg[3]; /* Leg has three segments */ 
}Leg;

/* Spyder class its atributes and methods */
class Spyder{
	private:	
		Circle cephalo, abdomen;
		Point auxx;
		Leg leftL[4], rightL[4];
		float ldX = 50.0f, ldY = 30.0f;
	public:
		Spyder(); 
		//~Wizard();
		void setBody(Circle, Circle);
		void setLegs(Leg [], Leg[]);
		Circle getCephalo();
		Circle getAbdomen();
		void draw();
		void initLegs();
		void move(Point);
		void turn(Point);

};

#endif 