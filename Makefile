all:
	@g++ -o T1 src/T1.cpp src/Spyder.cpp -I./include -g -Wall -lglut -lGLU -lGL -lm -std=c++11	
run:
	@./T1
frun:
	@valgrind -v --track-origins=yes --leak-check=full --show-leak-kinds=all ./T1
	
