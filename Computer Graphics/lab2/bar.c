//dependent on the previous lab dda.c code
#include<stdlib.h>
#include<stdio.h>
#include<GL/glut.h>
#include <GL/gl.h>
#define ROUND(x) ((int)(x+0.5))
int inha,inhaxa,inhaxb,inhb,inhbxa,inhbxb,inhc,inhcxa,inhcxb,inhd,inhdxa,inhdxb,inhe,inhexa,inhexb;
void dda(int xa,int ya,int xb,int yb,float r,float g, float b){
	float dx,dy,steps,xinc,yinc,x,y;
	dx=xb-xa;
	dy=yb-ya;
	steps=abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	xinc=dx/steps;
	yinc=dy/steps;
	x=xa;
	y=ya;
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (r, g, b);
	glBegin(GL_POINTS);
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
	dda(-10,0,490,0,1.0,1.0,1.0);
	//y-axis
	dda(0,-10,0,490,1.0,1.0,1.0);
	//five bars
	for(int i=inhaxa;i<=inhaxb;i++){
		dda(i,0,i,inha,1.0,0.0,0.0);
	}
	for(int i=inhbxa;i<=inhbxb;i++){
		dda(i,0,i,inhb,0.0,1.0,0.0);
	}
	for(int i=inhcxa;i<=inhcxb;i++){
		dda(i,0,i,inhc,0.0,0.0,1.0);
	}
	for(int i=inhdxa;i<=inhdxb;i++){
		dda(i,0,i,inhd,1.0,1.0,0.0);
	}
	for(int i=inhexa;i<=inhexb;i++){
		dda(i,0,i,inhe,0.0,1.0,1.0);
	}				
	// dda(20,30,40,50,1.0,0.0,1.0);
	glEnd();
	glFlush();
}

void init(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glOrtho(-10.0, 490.0, -10.0, 490.0, -1.0, 1.0);
}

int main(int argc, char** argv){
	printf("Height of the first bar :");
	scanf("%d",&inha);
	printf("XA XB of the first bar :");
	scanf("%d %d",&inhaxa,&inhaxb);
	printf("Height of the second bar :");
	scanf("%d",&inhb);
	printf("XA XB of the second bar :");
	scanf("%d %d",&inhbxa,&inhbxb);
	printf("Height of the third bar :");
	scanf("%d",&inhc);
	printf("XA XB of the third bar :");
	scanf("%d %d",&inhcxa,&inhcxb);
	printf("Height of the fourth bar :");
	scanf("%d",&inhd);
	printf("XA XB of the fourth bar :");
	scanf("%d %d",&inhdxa,&inhdxb);
	printf("Height of the fifth bar :");
	scanf("%d",&inhe);
	printf("XA XB of the fifth bar :");
	scanf("%d %d",&inhexa,&inhexb);
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("BAR GRAPH");
	init ();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}