#ifndef _SPIDER_H_
#define _SPIDER_H_

#include <Transformations.h>
#include <Geometrics.h>

typedef struct {
	Point joint[3]; /* Leg has 3 joints */ 
}Leg;

/* Spider class its atributes and methods */
class Spider{
	private:	
		Circle cephalo, abdomen;
		Leg leftLeg[4], rightLeg[4];

		void initLegs();

	public:

		Spider(); 

		void setBody(Circle, Circle);
		void setLegs(Leg [], Leg[]);

		Circle getCephalo();
		Circle getAbdomen();	

		void drawLegs();
		void draw();
		
		void move();
		void turn();
		void legsAnimation();
		
};

#endif 