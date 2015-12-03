all:
	g++ -o snake snake.cpp -lglut -lGL -lGLU
clean:
	-rm -f snake
