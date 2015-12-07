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
#include <math.h>
#include <time.h>
#include <unistd.h>


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
int current_face = 0; //0 for default
int level_str = 1.0;
int bullet_flag = 0;
int bullet_shoot_flag = 0;
int enemy_down_flag = 0;
int enemy_down_count = 20;
int enemy_down_moving = 0;
int enemy_down_rotation = 0;
int kill_enemy_count = 0;
int game_over_bool = 0;
int game_over_flag = 0;
float PI = 3.14159;
float level = 1.0;
float right_arm_degree = 110;
float right_forearm_degree = 15;
float bullet_trace = -0.8;
float enemy_moving = 0;
float enemy_moving_forward = 0;
float sword_angle = 0;
const float LINE_WIDTH = 2.5;
const float HEAD_RADIUS = 0.4;
const float LEFT_ARM_LENGTH = 0.6;
const float LEFT_FOREARM_LENGTH = 1.2;
const float RIGHT_ARM_LENGTH = 0.6;
const float RIGHT_FOREARM_LENGTH = 1.2;
const float BODY_LENGTH = 1.6;
const float LEFT_LEG_LENGTH = 1.7;
const float RIGHT_LEG_LENGTH = 0.6;
const float RIGHT_FORELEG_LENGTH = 1.2;
const float SWORD_HANDLE = 0.6;

bool p = false;
bool cheat = false;
string cheat_str = "Off";

void *font1 = GLUT_BITMAP_TIMES_ROMAN_24;
void *font2 = GLUT_BITMAP_HELVETICA_18;
void light();
void drawCube(float x1, float x2, float y1, float y2, float z1, float z2);
void drawRectangle(float width, float length);
void drawHead(float radius);
void drawBody();
void drawLine(float length);
void drawBullet();
void drawEnemy(int status);
void drawSword();
void set_level();
void set_everything();
void set_over_msg(int game_over_flag);

void drawCube(float x1, float x2, float y1, float y2, float z1, float z2)
{
	glBegin(GL_QUADS);
		// glNormal3f();
		glVertex3f(x1, y2, z2);
		glVertex3f(x2, y2, z2);
		glVertex3f(x2, y2, z1);
		glVertex3f(x1, y2, z1);

		glVertex3f(x1, y1, z2);
		glVertex3f(x2, y1, z2);
		glVertex3f(x2, y1, z1);
		glVertex3f(x1, y1, z1);

		glVertex3f(x2, y2, z2);
		glVertex3f(x2, y1, z2);
		glVertex3f(x2, y1, z1);
		glVertex3f(x2, y2, z1);

		glVertex3f(x1, y2, z2);
		glVertex3f(x1, y1, z2);
		glVertex3f(x1, y1, z1);
		glVertex3f(x1, y2, z1);

		glVertex3f(x1, y1, z2);
		glVertex3f(x2, y1, z2);
		glVertex3f(x2, y2, z2);
		glVertex3f(x1, y2, z2);

		glVertex3f(x1, y1, z1);
		glVertex3f(x2, y1, z1);
		glVertex3f(x2, y2, z1);
		glVertex3f(x1, y2, z1);

	glEnd();
}

void drawRectangle(float width, float length) 
{
	glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(-width/2, -length/2, 0.0);
		glVertex3f( width/2, -length/2, 0.0);
		glVertex3f( width/2,  length/2, 0.0);
		glVertex3f(-width/2,  length/2, 0.0);
	glEnd();
}

void drawHead(float radius)
{
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 360; i++)
        glVertex2f(radius * cos(2 * PI / 360 * i), radius * sin(2 * PI / 360 * i));
    	glNormal3f(0.0, 0.0, 1.0);
    glEnd();
}

void drawBullet()
{
	glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f( 1.0,  1.0, 0.0);
		glVertex3f(-1.0,  1.0, 0.0);
		glVertex3f(-1.5,  0.0, 0.0);
		glVertex3f(-1.0, -1.0, 0.0);
		glVertex3f( 1.0, -1.0, 0.0);
	glEnd();
}

void drawLine(float length)
{
	glBegin(GL_LINES);
		glVertex3f(-length, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
	glEnd();
}

void drawBody() 
{
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
		drawHead(HEAD_RADIUS);
		glTranslatef(0.0, -HEAD_RADIUS, 0.0);
		glRotatef(90.0, 0.0, 0.0, 1.0);
		drawLine(BODY_LENGTH);
		glRotatef(-45, 0.0, 0.0, 1.0);
		drawLine(LEFT_ARM_LENGTH);
		glTranslatef(-LEFT_ARM_LENGTH, 0.0, 0.0);
		glRotatef(45, 0.0, 0.0, 1.0);
		drawLine(LEFT_FOREARM_LENGTH);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, -HEAD_RADIUS - BODY_LENGTH, 0.0);
		glRotatef(70.0, 0.0, 0.0, 1.0);
		drawLine(LEFT_LEG_LENGTH);
		glRotatef(65.0, 0.0, 0.0, 1.0);
		drawLine(RIGHT_LEG_LENGTH);
		glTranslatef(-RIGHT_LEG_LENGTH, 0.0, 0.0);
		glRotatef(-45.0, 0.0, 0.0, 1.0);
		drawLine(RIGHT_FORELEG_LENGTH);
	glPopMatrix();
	//right arm
	glPushMatrix();
		glTranslatef(0.0, -HEAD_RADIUS, 0.0);
		glRotatef(right_arm_degree, 0.0, 0.0, 1.0);
		drawLine(RIGHT_ARM_LENGTH);
		glTranslatef(-RIGHT_ARM_LENGTH, 0.0, 0.0);
		glRotatef(right_forearm_degree, 0.0, 0.0, 1.0);
		drawLine(RIGHT_FOREARM_LENGTH);
		//right arm
		glTranslatef(-RIGHT_FOREARM_LENGTH, 0.15, 0.0);
		glRotatef(90.0, 0.0, 0.0, 1.0);
		glLineWidth(10.0);
		drawLine(0.5);
		//gun
		glTranslatef(-0.5, 0.0, 0.0);
		glRotatef(-90.0, 0.0, 0.0, 1.0);
		drawLine(0.7);
		//bullet
		glTranslatef(bullet_trace, 0.0, 0.0);
		glScalef(0.2, 0.1, 0.0);
		drawBullet();
	glPopMatrix();
}

void drawEnemy(int status)
{
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
		//head
		drawHead(HEAD_RADIUS);
		glTranslatef(0.0, -HEAD_RADIUS, 0.0);
		glRotatef(90.0, 0.0, 0.0, 1.0);
		//right arm
		drawLine(BODY_LENGTH);
		glRotatef(45, 0.0, 0.0, 1.0);
		drawLine(RIGHT_ARM_LENGTH);
		glTranslatef(-RIGHT_ARM_LENGTH, 0.0, 0.0);
		glRotatef(-45, 0.0, 0.0, 1.0);
		drawLine(RIGHT_FOREARM_LENGTH);
	glPopMatrix();

	glPushMatrix();
		if (status == 1) {
			glTranslatef(0.0, -HEAD_RADIUS - BODY_LENGTH, 0.0);
			glRotatef(125.0 - (20 * sin(enemy_moving) + 20), 0.0, 0.0, 1.0);

			drawLine(LEFT_LEG_LENGTH);
			glRotatef(-(130.0 - (20 * sin(enemy_moving) + 20)), 0.0, 0.0, 1.0);
			glRotatef(80 + (20 * sin(enemy_moving) + 20), 0.0, 0.0, 1.0);
			drawLine(LEFT_LEG_LENGTH);
			// glTranslatef(-RIGHT_LEG_LENGTH, 0.0, 0.0);
			// glRotatef(45.0, 0.0, 0.0, 1.0);
			// drawLine(RIGHT_FORELEG_LENGTH);
		}
		
	glPopMatrix();

	//left arm
	glPushMatrix();
		glTranslatef(0.0, -HEAD_RADIUS, 0.0);
		glRotatef(70, 0.0, 0.0, 1.0);
		drawLine(RIGHT_ARM_LENGTH);
		glTranslatef(-RIGHT_ARM_LENGTH, 0.0, 0.0);
		glRotatef(-15, 0.0, 0.0, 1.0);
		drawLine(RIGHT_FOREARM_LENGTH);
		//sword
		glLineWidth(2.5);
		glTranslatef(-RIGHT_FOREARM_LENGTH, -0.2, 0.0);
		glRotatef(-90.0 + sword_angle, 0.0, 0.0, 1.0);
		drawSword();
	glPopMatrix();
}

void drawSword()
{
	glBegin(GL_LINES);
		//handle
		drawLine(SWORD_HANDLE);
		glTranslatef(-SWORD_HANDLE, 0.0, 0.0);
		glRotatef(45.0, 0.0, 0.0, 1.0);
		drawLine(SWORD_HANDLE);
		glRotatef(-90.0, 0.0, 0.0, 1.0);
		drawLine(SWORD_HANDLE);
		//body
		glTranslatef(-SWORD_HANDLE + 0.3, 0.0, 0.0);
		glRotatef(45.0, 0.0, 0.0, 1.0);
		drawLine(2.5);
		glTranslatef(-2.5, 0.0, 0.0);
		glRotatef(45.0, 0.0, 0.0, 1.0);
		drawLine(0.4);
		glTranslatef(-0.4, 0.0, 0.0);
		glRotatef(100.0, 0.0, 0.0, 1.0);
		drawLine(0.4);
		glTranslatef(-0.4, 0.0, 0.0);
		glRotatef(37.0, 0.0, 0.0, 1.0);
		drawLine(2.5);
	glEnd();
}

void add(int x, int y, int z, int snake_face)
{
	sq *tmp = (sq *)malloc(sizeof(sq));
	tmp -> x = x;
	tmp -> y = y;
	tmp -> z = z;
	if (snake != NULL) {
		tmp -> mx = snake->mx;
		tmp -> my = snake->my;
		tmp -> mz = snake->mz;
	} else {
		tmp -> mx = 1;
		tmp -> my = 0;
		tmp -> mz = 0;
	}
	tmp -> snake_face = snake_face;
	tmp -> next = snake;
	snake = tmp;
}

void start()
{
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

void set_f()
{
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
			if (snake->x + mx == fx || snake->y + my == fy 
				|| snake->z + mz ==fz) {
				f = true;
				break;
			}
			if( (p -> x == fx || p -> x == -fx) && (p -> y == fy 
				|| p -> y == -fy) && (p -> z == fz || p -> z == -fz) ){
				f = true;
				break;		
			}	
			f = false;
			p = p -> next;
		}	
	}
}

bool tail()
{
	sq *p = snake;
	while(p -> next != NULL){
		if(p -> next -> x == snake -> x && p -> next -> y == snake -> y
			&& p -> next -> z == snake -> z)
			return true;	
		p = p -> next;
	}
	return false;
}

void move()
{
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

void foodpar(float x1, float x2, float y1, float y2, float z1, float z2)
{
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
	drawCube(x1, x2, y1, y2, z1, z2);
}

void par(float x1, float x2, float y1, float y2, float z1, float z2)
{
	glColor3f(1.0, 1.0, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	drawCube(x1, x2, y1, y2, z1, z2);
}

void set_msg(float x, float y, void *font, char *string)
{
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(x, y);
	for (int i = 0; i < (int)strlen(string); i++) {
		glutBitmapCharacter(font, string[i]);
	}
}

void display_msg(){
	stringstream strs1;
	stringstream strs2;
	stringstream strs3;
	strs1 << sc;
	strs2 << level_str;
	strs3 << kill_enemy_count;
	string sc_str = "Score : ";
	string Level = "Level : ";
	string enemy_kill = "Enemy Kill: ";
	sc_str.append(strs1.str());
	Level.append(strs2.str());
	enemy_kill.append(strs3.str());
	set_msg( 15.0, 13.0, font2, (char *) sc_str.c_str());
	set_msg( 15.0, 11.0, font2, (char *) Level.c_str());
	set_msg( 15.0, 9.0, font2, (char *) enemy_kill.c_str());
	set_msg(-20.0, 13.0, font1, (char *) "w - UP");
	set_msg(-20.0, 11.0, font1, (char *) "s - DOWN");
	set_msg(-20.0, 9.0, font1, (char *) "a - LEFT");
	set_msg(-20.0, 7.0, font1, (char *) "d - RIGHT");
	set_msg(-20.0, 5.0, font1, (char *) "r - RESTART");
	set_msg(-20.0, 3.0, font1, (char *) "esc - ESC");
	set_msg(-20.0, 1.0, font1, (char *) "c - CHEAT: ");
	set_msg(-13.0, 1.0, font2, (char *) cheat_str.c_str());

	if (game_over_bool == 2) {
		game_over_bool -= 1;
		set_msg(-3.0, 12.0, font2, (char *) "GAME OVER!");
	}
}



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -40.0);
	

	if (game_over_bool == 1) {

		usleep(2000000);
		set_over_msg(game_over_flag);
		exit(0);

	}
	display_msg();
	glPushMatrix();
		glTranslatef(0.0, -15.0, 0.0);
		drawRectangle(50.0, 0.2);
		//stickman
		glPushMatrix();
			glTranslatef(-15.0, 3.7, 0.0);
			glLineWidth(LINE_WIDTH);
			drawBody();
		glPopMatrix();

		glPushMatrix();
			glTranslatef( 15.0 - enemy_moving_forward, 3.7, 0.0);
			glLineWidth(2.0);
			if (enemy_down_flag == 1) {
				glTranslatef(-enemy_down_moving, 3.7, 0.0);
				glRotatef(enemy_down_rotation, 0.0, 0.0, 1.0);
				drawEnemy(1);
			}
			else{
				drawEnemy(1);
			}
			drawEnemy(1);
		glPopMatrix();

	glPopMatrix();
	//rotate around Y axis
	glLineWidth(1.0);
	glPushMatrix();
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
				sq *p = snake;
				while(p != NULL){
					if (p->snake_face == 0){
						par((p -> x), (p -> x) + 1, (p -> y), (p -> y) + 1, p -> z, p -> z);
						p = p -> next;
					}
					else if (p->snake_face == 1){
						par((p -> x), (p -> x), (p -> y), (p -> y) + 1, p -> z, p -> z + 1);
						p = p->next;
					}
					else if (p->snake_face == 2){
						par((p -> x), (p -> x) + 1, (p -> y), (p -> y) + 1, p -> z + 1, p -> z + 1);
						p = p->next;
					}
					else if (p->snake_face == 3) {
						par((p -> x) + 1, (p -> x) + 1, (p -> y), (p -> y) + 1, p -> z, p -> z + 1);
						p = p->next;
					}				
				}
				if ( (fface == 0) || (fface == 2) ) {
					foodpar(fx, fx + 1, fy, fy + 1, fz, fz);
				}
				else if ( (fface == 1)||(fface == 3) ) {
					foodpar(fx, fx, fy, fy + 1, fz, fz + 1);
				}
				glutSwapBuffers();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void set_over_msg(int game_over_flag) 
{
	cout << "\n          Game Over!!!!\n";
	if (game_over_flag == 0) {
		cout << "          You bited your tail "<< endl;
	}
	else if (game_over_flag == 1) {
		cout << "          You are killed by enemy "<< endl;
	}
	else{
		cout << "          You quited the game "<< endl;
	}
	cout << "          Your final Score is ";
	cout << sc << endl;
	cout << "          You survived ";
	cout << level_str;
	cout << " rounds" << endl;
	cout << "          You killed ";
	cout << kill_enemy_count;
	cout << " enemies\n" << endl;
}

void set_level() 
{
	if (sc % 5 == 0){
		right_arm_degree = 110;
		right_forearm_degree = 15;
	}
	if (sc == 5){
		level = 1.5;
		level_str = 2;
	} 
	if (sc == 10) {
		level = 2.0;
		level_str = 3;
	}
	if (sc == 15) {
		level = 2.5;
		level_str = 4;
	}
	if (sc == 20) {
		level = 3.0;
		level_str = 5;
	}
}




void myIdleFunc(int a) {
	if(!p){
		if(!cheat && tail()) {
			game_over_flag = 0;
			game_over_bool = 2;
		} else if(sc >= 2300) {
			cout << "\nyou win!\n" << endl;
			exit(0);
		} else{ 
			if ( (fface == 0) && (snake -> x + mx == fx && snake -> y + my == fy && snake -> z + mz == fz) ) {
				add(fx, fy, fz , snake->snake_face);
				set_everything();
			}
			else if ( (fface == 1) && (snake -> x + mx == fx && snake -> y + my == fy && snake -> z + mz  == fz) ) {
				add(fx, fy, fz, snake->snake_face);	
				set_everything();
			}
			else if ( (fface == 2) && (snake -> x + mx == fx && snake -> y + my == fy && snake -> z + mz + 1 == fz) ) {
				add(fx, fy, fz - 1, snake->snake_face);	
				set_everything();
			}	
			else if ( (fface == 3) && (snake -> x + mx + 1 == fx && snake -> y + my == fy && snake -> z + mz == fz) ) {
				add(fx - 1, fy, fz, snake->snake_face);	
				set_everything();
			} 
			set_level();
		}
		move();
		if ((sc % 5 == 4) && (bullet_shoot_flag == 0)) {
			bullet_flag = 1;
			bullet_shoot_flag = 1;
		}

		if (sc % 5 == 0) {
			bullet_shoot_flag = 0;
		}
		
		if ( (bullet_flag == 1) and (enemy_down_flag == 0) && (bullet_shoot_flag == 1)){
			bullet_trace -= 1;

			//ENEMY DOWN
			if(enemy_moving_forward - bullet_trace >= 29){
				enemy_down_flag = 1;
				sword_angle = 0;
				enemy_moving = 0;
				bullet_trace = -0.8;
				bullet_flag = 0;
				kill_enemy_count += 1;
			}
		}
		
		if (bullet_trace < -40) {
			bullet_trace = -0.8;
			bullet_flag = 0;
		}

		if ( (enemy_down_flag == 1) and (enemy_down_count > 0) ){
			enemy_down_count -= 1;
			enemy_down_moving -= 4;
			enemy_down_rotation = enemy_down_count * 36;
			if (enemy_down_count == 0) {
				enemy_down_flag = 0;
				enemy_down_count = 20;
				enemy_down_rotation = 0;
				enemy_down_moving = 0;
				enemy_moving_forward = 0;
			}
		}

		else{

			if (enemy_moving >= 2 * PI) {
				enemy_moving = 0;
			}

			enemy_moving += PI/10;

			if (enemy_moving_forward >= 25.5) {
				if (cheat) {
					enemy_down_flag = 1;
					sword_angle = 0;
					enemy_moving = 0;
					bullet_trace = -0.8;
					kill_enemy_count += 1;
				bullet_flag = 0;
				}
				else{
					game_over_flag = 1;
					if (game_over_bool != 1) {
						game_over_bool = 2;
					}
				}
			}
			enemy_moving_forward += 0.1;
			sword_angle += 0.13;

		}
		glutPostRedisplay();
	}
	glutTimerFunc(100/level, myIdleFunc, 0);
}


void set_everything()
{
	sc++;
	right_forearm_degree += 6.8;
	right_arm_degree += 6.8;
	set_f();
}

void init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);	
	glLoadIdentity ();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
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
		set_over_msg(2);
		exit(0);
	}
	else if( (char)key == 'a' ){
		if(!p) {
			if ( (current_face == 0) && (mx != 1) ) {
				mx = -1;
				my =  0;
				mz =  0;
			} else if ( (current_face == 1) && (mz != -1) ) {
				mx = 0;
				my = 0;
				mz = 1;
			} else if ( (current_face == 2) && (mx != -1) ) {
				mx = 1;
				my = 0;
				mz = 0;
			} else if ( (current_face == 3) && (mz != 1) ) {
				mx = 0;
				my = 0;
				mz = -1;
			}
		}	
	}else if( (char)key == 'd' ){
		if(!p){ 
			if ( (current_face == 0) && (mx != -1) ) {
				mx =  1;
				my =  0;
				mz =  0;
			} else if ( (current_face == 1) && (mz != 1) ) {
				mx = 0;
				my = 0;
				mz = -1;
			} else if ( (current_face == 2) && (mx != 1) ) {
				mx = -1;
				my = 0;
				mz = 0;
			} else if ( (current_face == 3) && (mz != -1) ) {
				mx = 0;
				my = 0;
				mz = 1;
			}
		}
	} else if( (char)key == 'w' ){
		if(!p){
			if ( (current_face == 0) && (my != -1) ) {
				mx =  0;
				my =  1;
				mz =  0;
			} else if ( (current_face == 1) && (my != -1) ) {
				mx = 0;
				my = 1;
				mz = 0;
			} else if ( (current_face == 2) && (my != -1) ) {
				mx = 0;
				my = 1;
				mz = 0;
			} else if ( (current_face == 3) && (my != -1) ) {
				mx = 0;
				my = 1;
				mz = 0;
			}
		}
	} else if( (char)key == 's' ){
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
	} else if( (char)key == 'p' ){
		if(p) p = false;
		else p = true;	
	} else if( (char)key == 'r' ){
		if( ((-7 < snake->x) <= 8) && ((-7 < snake->z) <= 8) ) start();
	} else if( (char)key == 'c' ){
		if(!cheat) {
			cheat = true;
			cheat_str = "On";
		} else{
			cheat = false;
			cheat_str = "Off";
		}
	}
}



int main(int argc, char** argv)
{
	string s("800x600:16@16");
	glutInit(&argc,argv);
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutGameModeString(s.c_str());

	glutEnterGameMode();
	init();
	glutTimerFunc(400, myIdleFunc, 0);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	start();
	set_f();
	
	glutMainLoop();
	return 0;
}
