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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sstream>


using namespace std;

typedef struct sq{
	int x;
	int y;
	int z;
	int mx;
	int my;
	int mz;
	int snake_face;
	struct sq *next;
} sq;

sq *snake;



int mx;
int my;
int mz;

int fx = -6;
int fy = -6;
int fz = 7;
int fface = 0;
int sc = 0;
float level = 1.0;
int level_str = 1.0;
bool p = false;
void *font1 = GLUT_BITMAP_TIMES_ROMAN_24;
void *font2 = GLUT_BITMAP_HELVETICA_18;
int current_face = 0; //0 for default


void add(int x, int y, int z, int snake_face){
	if (snake != NULL) {
		sq *tmp = (sq *)malloc(sizeof(sq));
		tmp -> x = x;
		tmp -> y = y;
		tmp -> z = z;
		tmp -> mx = snake->mx;
		tmp -> my = snake->my;
		tmp -> mz = snake->mz;
		tmp -> snake_face = snake_face;
		tmp -> next = snake;
		snake = tmp;
	} else {
		sq *tmp = (sq *)malloc(sizeof(sq));
		tmp -> x = x;
		tmp -> y = y;
		tmp -> z = z;
		tmp -> mx = 1;
		tmp -> my = 0;
		tmp -> mz = 0;
		tmp -> snake_face = snake_face;
		tmp -> next = snake;
		snake = tmp;
	}
}
void start(){
	free(snake);
	sc = 0;
	snake = NULL;
	add(0, 0, 7, 0);
	add(1, 0, 7, 0);
	add(2, 0, 7, 0);
	add(3, 0, 7, 0);
	add(4, 0, 7, 0);
	mx = 1;
	my = 0;
	mz = 0;
	snake->snake_face = 0;
		current_face = 0;
}
void set_f(){
	bool f = true;
	srand(time(NULL));
	while(f){
		
		fface = (rand() % 4);
		if (fface == 0) {
			
			fx = (rand() % 12) - 6;	 
			
			fy = (rand() % 12) - 6;
			fz = 7;
		}
		else if (fface == 1) {
			
			fz = (rand() % 12) - 6;	 
			
			fy = (rand() % 12) - 6;
			fx = 7;
		}
		else if (fface == 2) {
			
			fx = (rand() % 12) - 6;	 
			
			fy = (rand() % 12) - 6;
			fz = -7;
		}
		else if (fface == 3) {
			
			fz = (rand() % 12) - 6;	 
			
			fy = (rand() % 12) - 6;
			fx = -7;
		}
		sq *p = snake;
		
		while(p != NULL){
			if (snake->x + mx == fx || snake->y + my == fy || snake->z + mz ==fz){
				f = true;
				break;
			}
			if( (p -> x == fx || p -> x == -fx) && (p -> y == fy || p -> y == -fy) 
				&& (p -> z == fz || p -> z == -fz) ){
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
		if(p -> next -> x == snake -> x && p -> next -> y == snake -> y
			&& p -> next -> z == snake -> z)
			return true;	
		p = p -> next;
	}
	return false;
}

void move(){
	sq *p = snake;
	int x = p -> x;
	int y = p -> y;
	int z = p -> z;
	int snake_face = p -> snake_face;
	int tmx = p -> mx;
	int tmy = p -> my;
	int tmz = p -> mz;

	while(p -> next != NULL){
		sq *q = p -> next;
		int tmp = q -> x;
		q -> x = x;
		x = tmp;

		tmp = q -> y;
		q -> y = y;
		y = tmp;

		tmp = q -> z;
		q -> z = z;
		z = tmp;

		tmp = q->snake_face;
		q -> snake_face = snake_face;
		snake_face = tmp;

		tmp = q -> mx;
		q -> mx = tmx;
		tmx = tmp;

		tmp = q -> my;
		q -> my = tmy;
		tmy = tmp;

		tmp = q -> mz;
		q -> mz = tmz;
		tmz = tmp;

		p = p -> next;
	}

	snake -> mx = mx;
	snake -> my = my;
	snake -> mz = mz;
	snake -> x += mx;
	snake -> y += my;
	snake -> z += mz;

	if (snake -> y >= 7){
		snake -> y = -7;
	}
	if (snake -> y <= -8){
		snake -> y = 6;
	}
	
	

	if ( (current_face == 0) && (snake->x >= 7) ) {

		current_face = 1;
		snake->snake_face = 1;
		snake->z --;
		mx = 0;
		my = 0;
		mz = -1;
	}
	else if ( (current_face == 1) && (snake->z >= 7) ) {

		current_face = 0;
		snake->snake_face = 0;
		snake->x --;
		mx = -1;
		my = 0;
		mz = 0;
	}

	else if ( (current_face == 0) && (snake->x <= -8) ) {

		current_face = 3;
		snake->snake_face = 3;
		snake->z --;
		mx = 0;
		my = 0;
		mz = -1;
	}
	else if ( (current_face == 3) && (snake->z >= 7) ) {

		current_face = 0;
		snake->snake_face = 0;
		snake->x ++;
		mx = 1;
		my = 0;
		mz = 0;
	}
	else if ( (current_face == 1) && (snake->z <= -8) ) {

		current_face = 2;
		snake->snake_face = 2;
		snake->x --;
		mx = -1;
		my = 0;
		mz = 0;
	}
	else if ( (current_face == 2) && (snake->x >= 7) ) {

		current_face = 1;
		snake->snake_face = 1;
		snake->z ++;
		mx = 0;
		my = 0;
		mz = 1;
	}
	else if ( (current_face == 2) && (snake->x <= -8) ) {

		current_face = 3;
		snake->snake_face = 3;
		snake->z ++;
		mx = 0;
		my = 0;
		mz = 1;
	}
	else if ( (current_face == 3) && (snake->z <= -8) ) {

		current_face = 2;
		snake->snake_face = 2;
		snake->x ++;
		mx = 1;
		my = 0;
		mz = 0;
	}


}


void drawmap(){
		glColor3f(0.5, 0.0, 100.0);

		for (int x = -7; x <= 7; x++) {
			glBegin(GL_LINE_LOOP);
			glVertex3f(x, -7, -7);
			glVertex3f(x, 7, -7);
			glEnd();
		}
		for (int x = -7; x <= 7; x++) {
			glBegin(GL_LINE_LOOP);
			glVertex3f(-7, x, -7);
			glVertex3f(7, x, -7);
			glEnd();
		}

		for (int x = -7; x <= 7; x++) {
			glBegin(GL_LINE_LOOP);
			glVertex3f(x, -7, 7);
			glVertex3f(x, 7, 7);
			glEnd();
		}
		for (int x = -7; x <= 7; x++) {
			glBegin(GL_LINE_LOOP);
			glVertex3f(-7, x, 7);
			glVertex3f(7, x, 7);
			glEnd();
		}

		for (int x = -7; x <= 7; x++) {
			glBegin(GL_LINE_LOOP);
			glVertex3f(-7, x, -7);
			glVertex3f(-7, x, 7);
			glEnd();
		}
		for (int x = -7; x <= 7; x++) {
			glBegin(GL_LINE_LOOP);
			glVertex3f(-7, -7, x);
			glVertex3f(-7, 7, x);
			glEnd();
		}


		for (int x = -7; x <= 7; x++) {
			glBegin(GL_LINE_LOOP);
			glVertex3f(7, x, -7);
			glVertex3f(7, x, 7);
			glEnd();
		}
		for (int x = -7; x <= 7; x++) {
			glBegin(GL_LINE_LOOP);
			glVertex3f(7, -7, x);
			glVertex3f(7, 7, x);
			glEnd();
		}

}

void foodpar(float x1, float x2, float y1, float y2, float z1, float z2){
	glColor3f(0.0, 1.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (fface == 0) {
		z2 ++;
	}
	else if (fface == 1){
		x2 ++;
	}
	else if (fface == 2){
		z2 --;
	}
	else if (fface == 3){
		x2 --;
	}

	glBegin(GL_QUADS);
		// draw front face
		glVertex3f(x1, y2, z2);
		glVertex3f(x2, y2, z2);
		glVertex3f(x2, y2, z1);
		glVertex3f(x1, y2, z1);

		// draw back face
		glVertex3f(x1, y1, z2);
		glVertex3f(x2, y1, z2);
		glVertex3f(x2, y1, z1);
		glVertex3f(x1, y1, z1);

		// draw left face
		glVertex3f(x2, y2, z2);
		glVertex3f(x2, y1, z2);
		glVertex3f(x2, y1, z1);
		glVertex3f(x2, y2, z1);

		// draw right face
		glVertex3f(x1, y2, z2);
		glVertex3f(x1, y1, z2);
		glVertex3f(x1, y1, z1);
		glVertex3f(x1, y2, z1);

		// draw top
		glVertex3f(x1, y1, z2);
		glVertex3f(x2, y1, z2);
		glVertex3f(x2, y2, z2);
		glVertex3f(x1, y2, z2);

		// draw bottom
		glVertex3f(x1, y1, z1);
		glVertex3f(x2, y1, z1);
		glVertex3f(x2, y2, z1);
		glVertex3f(x1, y2, z1);

	glEnd();
	
}




void par(float x1, float x2, float y1, float y2, float z1, float z2){
	glColor3f(1.0, 1.0, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_QUADS);
		// draw front face
		glVertex3f(x1, y2, z2);
		glVertex3f(x2, y2, z2);
		glVertex3f(x2, y2, z1);
		glVertex3f(x1, y2, z1);

		// draw back face
		glVertex3f(x1, y1, z2);
		glVertex3f(x2, y1, z2);
		glVertex3f(x2, y1, z1);
		glVertex3f(x1, y1, z1);

		// draw left face
		glVertex3f(x2, y2, z2);
		glVertex3f(x2, y1, z2);
		glVertex3f(x2, y1, z1);
		glVertex3f(x2, y2, z1);

		// draw right face
		glVertex3f(x1, y2, z2);
		glVertex3f(x1, y1, z2);
		glVertex3f(x1, y1, z1);
		glVertex3f(x1, y2, z1);

		// draw top
		glVertex3f(x1, y1, z2);
		glVertex3f(x2, y1, z2);
		glVertex3f(x2, y2, z2);
		glVertex3f(x1, y2, z2);

		// draw bottom
		glVertex3f(x1, y1, z1);
		glVertex3f(x2, y1, z1);
		glVertex3f(x2, y2, z1);
		glVertex3f(x1, y2, z1);

	glEnd();
	
}

void set_msg(float x, float y, void *font, char *string)
{
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(x, y);
	int len, i;
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, string[i]);
	}
}

void display_msg(){
	stringstream strs1;
	stringstream strs2;
	strs1 << sc;
	strs2 << level_str;
	string temp_sc = strs1.str();
	string temp_level = strs2.str();
	string sc_str = "Score : ";
	string Level = "Level : ";
	sc_str.append(temp_sc);
	Level.append(temp_level);
	char* char_sc = (char *) sc_str.c_str();
	char* char_level = (char *) Level.c_str();
	set_msg(15.0, 13.0, font1, (char *) char_sc);
	set_msg(15.0, 11.0, font1, (char *) char_level);
	set_msg(-20.0, 13.0, font1, (char *)"w - UP");
	set_msg(-20.0, 11.0, font1, (char *)"s - DOWN");
	set_msg(-20.0, 9.0, font1, (char *)"a - LEFT");
	set_msg(-20.0, 7.0, font1, (char *)"d - RIGHT");
	set_msg(-20.0, 5.0, font1, (char *)"r - RESTART");
	set_msg(-20.0, 3.0, font1, (char *)"esc - ESC");
	// set_msg(-21.0, -13.0, font2, (char *)"When your score reaches 99, you will receive the ANSWER to the ultimate ");
	// set_msg(-21.0, -14.5, font2, (char *)"question of life, the universe, and everything!!!!!");
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();
	glTranslatef(0.0, 0.0, -40.0);
	display_msg();
	//rotate around Y axis
	if (current_face == 0) {
		glRotatef(snake->y * 6.43, 1.0, 0.0, 0.0);
		glRotatef(-snake->x * 6.43, 0.0, 1.0, 0.0);
		
	}
	else if (current_face == 1) {
		glRotatef(-90 , 0.0, 1.0, 0.0);
		glRotatef(snake->z * 6.43, 0.0, 1.0, 0.0);
		glRotatef(-snake->y * 6.43, 0.0, 0.0, 1.0);	
	}

	else if (current_face == 2) {
		glRotatef(180 , 0.0, 1.0, 0.0);
		glRotatef(-snake->y * 6.43, 1.0, 0.0, 0.0);
		glRotatef(snake->x * 6.43, 0.0, 1.0, 0.0);
		
	}

	else if (current_face == 3) {
		glRotatef(90 , 0.0, 1.0, 0.0);
		glRotatef(-snake->z * 6.43, 0.0, 1.0, 0.0);
		glRotatef(snake->y * 6.43, 0.0, 0.0, 1.0);
		
	}
	

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glPushMatrix();
		drawmap();
		glPushMatrix();
			int i;
			sq *p = snake;
			while(p != NULL){
				if (p->snake_face == 0){
					par((p -> x) ,(p -> x) +1,(p -> y),(p -> y) + 1, p -> z, p -> z);
					p = p -> next;
				}
				else if (p->snake_face == 1){
					par((p -> x),(p -> x),(p -> y),(p -> y) + 1, p -> z, p -> z + 1);
					p = p->next;
				}
				else if (p->snake_face == 2){
					par((p -> x),(p -> x) + 1,(p -> y),(p -> y) + 1, p -> z + 1, p -> z + 1);
					p = p->next;
				}
				else if (p->snake_face == 3) {
					par((p -> x) + 1,(p -> x) + 1,(p -> y),(p -> y) + 1, p -> z, p -> z + 1);
					p = p->next;
				}				
			}
			if ( (fface == 0) || (fface == 2) ) {
				foodpar(fx, fx + 1 , fy , fy + 1, fz, fz);
			}
			else if ((fface == 1)||(fface == 3)) {
				foodpar(fx, fx, fy , fy + 1, fz, fz + 1);
			}
			glutSwapBuffers();
		glPopMatrix();
	glPopMatrix();

}
void set_level(int score) {
	if (sc > 5){
		level = 1.5;
		level_str = 2;
	} 
	if (sc > 10) {
		level = 2.0;
		level_str = 3;
	}
	if (sc > 15) {
		level = 2.5;
		level_str = 4;
	}
	if (sc > 20) {
		level = 3.0;
		level_str = 5;
	}

}


void myIdleFunc(int a) {
	if(!p){
		if(tail()) {
			// start();
			cout << "\nGame Over!!!!" << endl;
			cout << "Your final Score is ";
			cout << sc << endl;
			cout << "You survived ";
			cout << level_str;
			cout << " Round\n" << endl;
			exit(0);

		} else if(sc >= 2300) {
			cout << "\n" << endl;
			cout << "you win!" << endl;	
			cout << "\n" << endl;
			exit(0);
		} else{ 

			if ( (fface == 0) && (snake -> x + mx == fx && snake -> y + my == fy && snake -> z + mz == fz) ) {
				add(fx, fy, fz , snake->snake_face);	
				sc++;
				set_f();
			}
			else if ( (fface == 1) && (snake -> x + mx == fx && snake -> y + my == fy && snake -> z + mz  == fz) ) {
				add(fx, fy, fz, snake->snake_face);	
				sc++;
				set_f();
			}
			else if ( (fface == 2) && (snake -> x + mx == fx && snake -> y + my == fy && snake -> z + mz + 1 == fz) ) {
				add(fx, fy, fz - 1, snake->snake_face);	
				sc++;
				set_f();
			}	
			else if ( (fface == 3) && (snake -> x + mx + 1 == fx && snake -> y + my == fy && snake -> z + mz == fz) ) {
				add(fx - 1, fy, fz, snake->snake_face);	
				sc++;
				set_f();
			} 
			set_level(sc);
		}
		move();
		glutPostRedisplay();
	}
	glutTimerFunc(100/level, myIdleFunc, 0);
}

void init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	// glEnable(GL_LIGHTING);
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
void keyboard(unsigned char key, int x, int y)
{
	if(key == 27) {		
		exit(0);	
	}else if((char)key == 'a'){
		if(!p){
			
			if ( (current_face == 0) && (mx != 1) ) {
				mx = -1;
				my =  0;
				mz =  0;
			}
			else if ((current_face == 1) && (mz != -1)) {
				mx = 0;
				my = 0;
				mz = 1;
			}
			else if ((current_face == 2) && (mx != -1)) {
				mx = 1;
				my = 0;
				mz = 0;
			}
			else if ((current_face == 3) && (mz != 1)) {
				mx = 0;
				my = 0;
				mz = -1;
			}
		}	
	}else if((char)key == 'd'){
		if(!p){
			
			if ( (current_face == 0) && (mx != -1) ) {
				mx =  1;
				my =  0;
				mz =  0;
			}
			else if ((current_face == 1) && (mz != 1)) {
				mx = 0;
				my = 0;
				mz = -1;
			}
			else if ((current_face == 2) && (mx != 1)) {
				mx = -1;
				my = 0;
				mz = 0;
			}
			else if ((current_face == 3) && (mz != -1)) {
				mx = 0;
				my = 0;
				mz = 1;
			}
		}
		
	}else if((char)key == 'w'){
		if(!p){
			
			if ( (current_face == 0) && (my != -1) ) {
				mx =  0;
				my =  1;
				mz =  0;
			}
			else if ((current_face == 1) && (my != -1)) {
				mx = 0;
				my = 1;
				mz = 0;
			}
			else if ((current_face == 2) && (my != -1)) {
				mx = 0;
				my = 1;
				mz = 0;
			}
			else if ((current_face == 3) && (my != -1)) {
				mx = 0;
				my = 1;
				mz = 0;
			}
		}
			
	}else if((char)key == 's'){
		if(!p){		
			
			if ( (current_face == 0) && (my != 1) ) {
				mx =  0;
				my =  -1;
				mz =  0;
			}
			else if ( (current_face == 1) && (my != 1) ) {
				mx = 0;
				my = -1;
				mz = 0;
			}
			else if ( (current_face == 2) && (my != 1) ) {
				mx = 0;
				my = -1;
				mz = 0;
			}
			else if ( (current_face == 3) && (my != 1) ) {
				mx = 0;
				my = -1;
				mz = 0;
			}
		}
		
	}else if((char)key == 'p'){
		if(p) p = false;
		else p = true;	
	}else if((char)key == 'r'){
		if( (-7 < snake->x <= 8) && (-7 < snake->z <= 8) ){
			start();
		}	
	}
}



int main(int argc, char** argv)
{

	if(argc < 2){
		cout << "\n usage :\n\n ./snake width height\n" << endl;		
		return 0;
	}
	string s(argv[1]);
	s += string(":16@60");

	glutInit(&argc,argv);
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutGameModeString(s.c_str());

	glutEnterGameMode();
	init();
	glutTimerFunc(400, myIdleFunc, 0);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc( keyboard );
	glutDisplayFunc(display);
	start();
	set_f();
	
	
	glutMainLoop();
	return 0;
}
