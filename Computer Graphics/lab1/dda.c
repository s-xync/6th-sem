#include<stdlib.h>
#include<stdio.h>
#include<GL/glut.h>
#include <GL/gl.h>
#define ROUND(x) ((int)(x+0.5))
int xa;
int ya;
int xb;
int yb;	
void display(){
	float dx,dy,steps,xinc,yinc,x,y;
	dx=xb-xa;
	dy=yb-ya;
	steps=abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	xinc=dx/steps;
	yinc=dy/steps;
	x=xa;
	y=ya;
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2s(ROUND(x),ROUND(y));
	printf("The intermediate points are :\n");
	for(int i=0;i<steps;i++){
		x+=xinc;
		y+=yinc;
		glVertex2s(ROUND(x),ROUND(y));
		printf("%d %d\n",ROUND(x),ROUND(y));
	}
	glEnd();
	glFlush();
}

void init(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
}

int main(int argc, char** argv){
	printf("Enter X1 : ");
	scanf("%d",&xa);
	printf("Enter Y1 : ");
	scanf("%d",&ya);
	printf("Enter X2 : ");
	scanf("%d",&xb);
	printf("Enter Y2 : ");
	scanf("%d",&yb);
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("DDA Algorithm");
	init ();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}