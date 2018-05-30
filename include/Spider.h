#ifndef _SPiDER_H_
#define _SPiDER_H_

#include <T2.h>
#include <Transformations.h>
#include <Geometrics.h>

typedef struct {
	Point seg[3]; /* Leg has two segments */ 
}Leg;

/* Spider class its atributes and methods */
class Spider{
	private:	
		Circle cephalo, abdomen, eye[2];
		float speed;
		int p2,p3,p4;
		Leg leftL[4], rightL[4];
		float ldX,ldY;
		bool resting = true;

	public:
		bool moving = false;
		Spider(); 
		//~Wizard();
		void setBody(Circle, Circle);
		void setLegs(Leg [], Leg[]);
		Circle getCephalo();
		Circle getAbdomen();
		void draw();
		void initLegs();
		void move(Point,Point);
		void turn(Point);
		void legsMovement();
		void legRest();
		void legStartMov();
};

#endif 