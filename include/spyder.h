#ifndef _SPYDER_H_
#define _SPYDER_H_



typedef struct {
	Point seg[3]; /* Leg has three segments */ 
}Leg;

/* Spyder class its atributes and methods */
class Spyder{
	private:	
		Circle cephalo, abdomen;
		Leg leftL[4], rightL[4];
	public:
		Spyder(); 
		//~Wizard();
		setBody(int, int ,int ,int);
};


#endif 