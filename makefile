all:
	g++ -o snake snake.cc -lglut -lGL -lGLU
clean:
	-rm -f snake
