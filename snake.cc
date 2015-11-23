/**
*Author :Tharindra Galahena
*Project:snake game openGL and c++
*Date   :19/02/2012
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>


using namespace std;

typedef struct sq{
	int x;
	int y;
	int mx;
	int my;
	struct sq *next;
} sq;

sq *snake;

int mx;
int my;
int fx = -6;
int fy = -6;
int sc = 0;
bool p = false;

void add(int x, int y){
	sq *tmp = (sq *)malloc(sizeof(sq));
	tmp -> x = x;
	tmp -> y = y;
	tmp -> mx = 1;
	tmp -> my = 0;
	tmp -> next = snake;
	snake = tmp;
}
void start(){
	snake = NULL;
	add(0, 0);
	add(1, 0);
	add(2, 0);
	add(3, 0);
	add(4, 0);
	mx = 1;
	my = 0;
}
void set_f(){
	bool f = true;
	while(f){
		srand(time(NULL));
		fx = (rand() % 34) - 17;	 
		srand(time(NULL));
		fy = (rand() % 34) - 17;
		sq *p = snake;
		while(p != NULL){
			if(p -> x == fx && p -> y == fy){
				f = true;
				break;		
			}	
			f = false;
			p = p -> next;
		}	
	}
}
bool tail(){
	sq *p = snake;
	while(p -> next != NULL){
		if(p -> next -> x == snake -> x + mx && p -> next -> y == snake -> y + my)
			return true;	
		p = p -> next;
	}
	return false;
}
void rev(){
	sq *snake2 = NULL;
	sq *p = snake;
	while(p != NULL){
		sq *tmp = (sq *)malloc(sizeof(sq));
		tmp -> x = p -> x;
		tmp -> y = p -> y;
		tmp -> mx = -1 * p -> mx;
		tmp -> my = -1 * p -> my;
		tmp -> next = snake2;
		snake2 = tmp;
		sq *x = p -> next;
		free(p);
		p = x;	
	}
	snake = snake2;
	mx = snake -> mx;
	my = snake -> my;
}

void move(){
	sq *p = snake;
	int x = p -> x;
	int y = p -> y;
	int tmx = p -> mx;
	int tmy = p -> my;
	while(p -> next != NULL){
		sq *q = p -> next;
		int tmp = q -> x;
		q -> x = x;
		x = tmp;

		tmp = q -> y;
		q -> y = y;
		y = tmp;

		tmp = q -> mx;
		q -> mx = tmx;
		tmx = tmp;

		tmp = q -> my;
		q -> my = tmy;
		tmy = tmp;

		p = p -> next;
	}
	snake -> mx = mx;
	snake -> my = my;
	snake -> x += mx;
	snake -> y += my;
}
void par(float x1, float x2, float y1, float y2, float z1, float z2){
	glColor3f(0.5, 0.0, 100.0);
	glBegin(GL_QUADS);
	
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y1, z1);
	glVertex3f(x2, y2, z1);
	glVertex3f(x1, y2, z1);

	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();

	glTranslatef(0.0, 0.0, -22.0);
	int i;
	sq *p = snake;
	par(-8.7,  9.2,  9.0,  9.2, 0.0, 0.0);
	par(-8.7,  9.2, -8.5, -8.7, 0.0, 0.0);
	par(-8.5, -8.7, -8.7,  9.2, 0.0, 0.0);
	par( 9.2,  9.0, -8.7,  9.2, 0.0, 0.0);
	while(p != NULL){
		par((p -> x)/2.0,(p -> x)/2.0 + 0.4,(p -> y)/2.0,(p -> y)/2.0 + 0.4, 0.0, 0.0);
		p = p -> next;	
	}
	par(fx/2.0, fx/2.0 + 0.4 , fy/2.0 , fy/2.0 + 0.4, 0.0 , 0.0);
	glutSwapBuffers();
}
void myIdleFunc(int a) {
	if(!p){
		if(snake -> x + mx >= 18 || snake -> x + mx <= -18) start();
		else if(snake -> y + my >= 18 || snake -> y + my <= -18) start();
		else if(tail()) start();
		else if(sc >= 30) {
			cout << "\n" << endl;
			cout << "you win!" << endl;	
			cout << "\n" << endl;
			exit(0);
		}else{
			if(snake -> x + mx == fx && snake -> y + my == fy){
				add(fx, fy);	
				sc++;
				set_f();
			}
		}
		move();
		glutPostRedisplay();
	}
	glutTimerFunc(400, myIdleFunc, 0);
}
void keyboard(unsigned char key, int x, int y)
{
	if(key == 27) {		
		exit(0);	
	}else if((char)key == 'a'){
		if(!p){
			if(mx == 1) rev();
			else{
				mx = -1;
				my =  0;
			}	
		}
	}else if((char)key == 'd'){
		if(!p){
			if(mx == -1) rev();
			else{
				mx =  1;
				my =  0;
			}
		}
	}else if((char)key == 'w'){
		if(!p){
			if(my == -1) rev();
			else{
				mx =  0;
				my =  1;
			}
		}	
	}else if((char)key == 's'){
		if(!p){		
			if(my == 1) rev();
			else{
				mx =  0;
				my = -1;
			}
		}
	}else if((char)key == 'p'){
		if(p) p = false;
		else p = true;	
	}
}

void init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);	
	glLoadIdentity ();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	GLfloat acolor[] = {1.4, 1.4, 1.4, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, acolor);

}
void Reshape(int w, int h)
{
    	glViewport(0, 0, w, h);
    	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	gluPerspective(45.0, (float)w/(float)h, 0.1, 200.0);
	
}
int main(int argc, char** argv)
{

	if(argc < 2){
		cout << "\n usage :\n\n ./snake width height\n" << endl;		
		return 0;
	}
	string s(argv[1]);
	s += string(":16@60");

	start();
	set_f();
	glutInit(&argc,argv);
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutGameModeString(s.c_str());
	
	glutEnterGameMode();
	init();
	glutTimerFunc(400, myIdleFunc, 0);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc( keyboard );
	glutDisplayFunc(display);
	
	
	glutMainLoop();
	return 0;
}
