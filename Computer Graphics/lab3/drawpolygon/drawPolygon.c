//dependent on the previous lab dda.c code
#include<stdlib.h>
#include<stdio.h>
#include<GL/glut.h>
#include <GL/gl.h>
#include <math.h>
#define ROUND(x) ((int)(x+0.5))
#define PI 3.14159265
int ptxarr[1000];
int ptyarr[1000];
int tptxarr[1000];
int tptyarr[1000];
int num_points,option,tr_x,tr_y,rt_angle;
float sc_factor;
void dda(int xa,int ya,int xb,int yb,float r,float g, float b){
	float dx,dy,steps,xinc,yinc,x,y;
	dx=xb-xa;
	dy=yb-ya;
	steps=abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	xinc=dx/steps;
	yinc=dy/steps;
	x=xa;
	y=ya;
	// glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (r, g, b);
	// glBegin(GL_POINTS);
	glVertex2s(ROUND(x),ROUND(y));
	printf("The intermediate points are :\n");
	for(int i=0;i<steps;i++){
		x+=xinc;
		y+=yinc;
		glVertex2s(ROUND(x),ROUND(y));
		printf("%d %d\n",ROUND(x),ROUND(y));
	}
}
void display(){
	//x-axis
	dda(-10,0,1490,0,1.0,1.0,1.0);
	//y-axis
	dda(0,-10,0,1490,1.0,1.0,1.0);
	//code
	if(option==1){
		for(int i=0;i<num_points;i++){
			tptxarr[i]=ptxarr[i]+tr_x;
			tptyarr[i]=ptyarr[i]+tr_y;
		}
	}else if(option==2){
		double rt_angler= (double) (rt_angle*PI/180.0);
		double cos_val=cos(rt_angler);
		double sin_val=sin(rt_angler);
		for(int i=0;i<num_points;i++){
			tptxarr[i]=tr_x+(int)((ptxarr[i]-tr_x)*cos_val - (ptyarr[i]-tr_y)*sin_val);
			tptyarr[i]=tr_y+(int)((ptxarr[i]-tr_x)*sin_val + (ptyarr[i]-tr_y)*cos_val);
		}

	}else if(option==3){
		for(int i=0;i<num_points;i++){
			tptxarr[i]=tr_x+(int)((ptxarr[i]-tr_x)*sc_factor);
			tptyarr[i]=tr_y+(int)((ptyarr[i]-tr_x)*sc_factor);
		}
	}
	glClear (GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	for(int i=1;i<num_points;i++){
		dda(ptxarr[i-1],ptyarr[i-1],ptxarr[i],ptyarr[i],1.0,0.0,0.0);
		dda(tptxarr[i-1],tptyarr[i-1],tptxarr[i],tptyarr[i],0.0,0.0,1.0);
	}
	// dda(20,30,40,50,1.0,0.0,1.0);
	glEnd();
	glFlush();
}

void init(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glOrtho(-10.0, 1490.0, -10.0, 1490.0, -1.0, 1.0);
}

int main(int argc, char** argv){
	printf("Start giving points in cyclic or acyclic order :\n");
	for(int i=0;i<1000;i++){
		if(i>3){
			if(ptxarr[i-1]==ptxarr[0] && ptyarr[i-1]==ptyarr[0]){
				num_points=i;
				break;
			}
		}
		scanf("%d %d",&ptxarr[i],&ptyarr[i]);
	}
	printf("Options to trasform a polygon\n1. Tranlsate\n2. Rotate\n3. Scale\n");
	printf("which option: ");
	scanf("%d",&option);
	switch(option){
		case 1:
		printf("Give translating coordinates: ");
		scanf("%d %d",&tr_x,&tr_y);
		break;
		case 2:
		printf("Give reference coordinates: ");
		scanf("%d %d",&tr_x,&tr_y);
		printf("Give angle in degress: ");
		scanf("%d",&rt_angle);
		break;
		case 3:
		printf("Give reference coordinates: ");
		scanf("%d %d",&tr_x,&tr_y);
		printf("Give scaling factor");
		scanf("%f",&sc_factor);
		break;
		default:
		printf("Not a valid OPTION\n");
		return 0;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (1500, 1500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("BAR GRAPH");
	init ();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}