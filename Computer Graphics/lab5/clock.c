/*
** Author : SaiKumar Immadi (1501058)
** gcc clock.c -lGL -lGLU -lGLEW -lglut -lm -o clock
** ./clock
*/
#include<stdlib.h>
#include<stdio.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include<math.h>
#include<time.h>

#define ROUND(x) ((int)(x+0.5))
#define PI 3.14159265

int radius=100;
double xh,yh,xm,ym,xs,ys,xhourmark,yhourmark,hourmarkangle,hour_angle,min_angle,sec_angle;
int hour=0;
int min=0;
int sec=0;

void drawLine(int xa,int ya,int xb,int yb,float r,float g, float b){
	float dx,dy,steps,xinc,yinc,x,y;
	dx=xb-xa;
	dy=yb-ya;
	steps=abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	xinc=dx/steps;
	yinc=dy/steps;
	x=xa;
	y=ya;
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (r,g,b);
	glBegin(GL_POINTS);
	glVertex2s(ROUND(x),ROUND(y));
	// printf("The intermediate points are :\n");
	for(int i=0;i<steps;i++){
		x+=xinc;
		y+=yinc;
		glVertex2s(ROUND(x),ROUND(y));
		// printf("%d %d\n",ROUND(x),ROUND(y));
	}
}

void drawCircle(int xa,int ya,int radius,float r,float g, float b){
	int x = radius;
	int y = 0;
	int err = 0;
	while (x >= y){
		glClear (GL_COLOR_BUFFER_BIT);
		glColor3f (r,g,b);
		glBegin(GL_POINTS);
		glVertex2s(xa + x, ya + y);
		glVertex2s(xa + y, ya + x);
		glVertex2s(xa - y, ya + x);
		glVertex2s(xa - x, ya + y);
		glVertex2s(xa - x, ya - y);
		glVertex2s(xa - y, ya - x);
		glVertex2s(xa + y, ya - x);
		glVertex2s(xa + x, ya - y);
		if (err <= 0){
			y += 1;
			err += 2*y + 1;
		}
		else if (err > 0){
			x -= 1;
			err -= 2*x + 1;
		}
	}
}

void display(){
	drawCircle(0,0,radius,1.0,0.0,0.0);
	drawLine(0,0,ROUND(xh),ROUND(yh),0.0,1.0,0.0);
	drawLine(0,0,ROUND(xm),ROUND(ym),0.0,1.0,1.0);
	drawLine(0,0,ROUND(xs),ROUND(ys),0.5,0.5,0.5);
	for(int i=0;i<12;i++){
		hourmarkangle=((double)i*30.0)*(PI/180);
		xhourmark=-1*(radius-7)*sin(-hourmarkangle);
		yhourmark=(radius-7)*cos(hourmarkangle);
		drawCircle(xhourmark,yhourmark,2.0,1.0,1.0,1.0);
	}
	glEnd();
	glFlush();
}

void init(void){
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glOrtho(-250.0, 250.0, -250.0, 250.0, -1.0, 1.0);
}

void animation(void){
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	hour=(timeinfo->tm_hour)%12;
	min=timeinfo->tm_min;
	sec=timeinfo->tm_sec;
	hour_angle=((double)hour*30.0)*(PI/180.0);
	hour_angle+=((double)min*0.5)*(PI/180.0);
	min_angle=((double)min*6.0)*(PI/180.0);
	sec_angle=((double)sec*6.0)*(PI/180.0);
	xh=-1*(radius-40)*sin(-hour_angle);
	yh=(radius-40)*cos(hour_angle);
	xm=-1*(radius-30)*sin(-min_angle);
	ym=(radius-20)*cos(min_angle);
	xs=-1*(radius-20)*sin(-sec_angle);
	ys=(radius-20)*cos(sec_angle);
	display();
}

int main(int argc,char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Simple Analog Clock");
	init ();
	glutDisplayFunc(display);
	glutIdleFunc(animation);
	glutMainLoop();
	return 0;
}