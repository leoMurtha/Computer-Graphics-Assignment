#include <stdlib.h>
#include <iostream>
#include <deviceInput.h>


// Check for mouse input
void mouse(GLint button, GLint state, GLint x, GLint y){

	// Makes destination alterations for mouse left button clicks
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
	}
}

// checks for keyboard input
void keyboardSpecial(GLint key, GLint x, GLint y){ 
    switch(key){
	  	case GLUT_KEY_UP:
	  		printf("Andando pra frente\n");
	  		break;
	  	case GLUT_KEY_DOWN:
	  		printf("Andando pra tras? De ré???\n");
	  		break;
	  	case GLUT_KEY_LEFT:
	  		printf("Rotacionando/virando pra esquerda\n");
	  		break;
	  	case GLUT_KEY_RIGHT:
	  		printf("Rotacionando/virando pra direita\n");
	  		break;
	  }
	  
  std::cout<<"Tecla: "<<(GLint) key<<" (x:"<<x<<", y:"<<y<<")\n"; 
  
}