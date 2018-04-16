#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define ROUND(a) ((int)(a+0.5))

int a;
int t;
float s;
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}
void display(){

	glClearColor (0, 0, 0, 0);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	gluPerspective(40.0f, 1.0f, -4.0f, 2.0f);
	gluLookAt(3*(a+t),3*(a+t),3*(a+t),	a+t,a+t,a+t,-1,1,-1);



	glBegin(GL_QUADS);

	
	glColor3f(1, 0, 0);//red
	glVertex3i(ROUND(s*(0+t)),ROUND(s*(0+t)),ROUND(s*(0+t)));
	glVertex3i(ROUND(s*(a+t)),ROUND(s*(0+t)),ROUND(s*(0+t)));
	glVertex3i(ROUND(s*(a+t)),ROUND(s*(a+t)),ROUND(s*(0+t)));
	glVertex3i(ROUND(s*(0+t)),ROUND(s*(a+t)),ROUND(s*(0+t)));

	glColor3f(0, 1, 0);//green
	glVertex3i(ROUND(s*(0+t)),ROUND(s*(0+t)),ROUND(s*(0+t)));
	glVertex3i(ROUND(s*(0+t)),ROUND(s*(a+t)),ROUND(s*(0+t)));
	glVertex3i(ROUND(s*(0+t)),ROUND(s*(a+t)),ROUND(s*(a+t)));
	glVertex3i(ROUND(s*(0+t)),ROUND(s*(0+t)),ROUND(s*(a+t)));

	glColor3f(0, 0, 1);//blue
	glVertex3i(ROUND(s*(0+t)),ROUND(s*(0+t)),ROUND(s*(a+t)));
	glVertex3i(ROUND(s*(a+t)),ROUND(s*(0+t)),ROUND(s*(a+t)));
	glVertex3i(ROUND(s*(a+t)),ROUND(s*(a+t)),ROUND(s*(a+t)));
	glVertex3i(ROUND(s*(0+t)),ROUND(s*(a+t)),ROUND(s*(a+t)));

	glColor3f(0, 1, 1);//teal
	glVertex3i(ROUND(s*(a+t)),ROUND(s*(0+t)),ROUND(s*(0+t)));
	glVertex3i(ROUND(s*(a+t)),ROUND(s*(a+t)),ROUND(s*(0+t)));
	glVertex3i(ROUND(s*(a+t)),ROUND(s*(a+t)),ROUND(s*(a+t)));
	glVertex3i(ROUND(s*(a+t)),ROUND(s*(0+t)),ROUND(s*(a+t)));
	
	glColor3f(1, 1, 1);//white
	glVertex3i(ROUND(s*(a+t)),ROUND(s*(a+t)),ROUND(s*(a+t)));
	glVertex3i(ROUND(s*(a+t)),ROUND(s*(a+t)),ROUND(s*(0+t)));
	glVertex3i(ROUND(s*(0+t)),ROUND(s*(a+t)),ROUND(s*(0+t)));
	glVertex3i(ROUND(s*(0+t)),ROUND(s*(a+t)),ROUND(s*(a+t)));

	glColor3f(1, 1, 0);//yellow
	glVertex3i(ROUND(s*(0+t)),ROUND(s*(0+t)),ROUND(s*(0+t)));
	glVertex3i(ROUND(s*(0+t)),ROUND(s*(0+t)),ROUND(s*(a+t)));
	glVertex3i(ROUND(s*(a+t)),ROUND(s*(0+t)),ROUND(s*(a+t)));
	glVertex3i(ROUND(s*(a+t)),ROUND(s*(0+t)),ROUND(s*(0+t)));

	glEnd();
//axes
	glBegin(GL_LINES);
		glColor3f(1,0,0);
		glVertex3i(0,0,0);
		glVertex3i(100,0,0);
		glColor3f(1,0,0);
		glVertex3i(0,100,0);
		glVertex3i(0,0,0);
		glColor3f(1,0,0);
		glVertex3i(0,0,100);
		glVertex3i(0,0,0);
	glEnd();

	glFlush();
	glutSwapBuffers();
}


int main(int argc, char **argv)
{
	printf("Length of a side : ");
	scanf("%d",&a);
	t=10;
	printf("Translate : ");
	scanf("%d",&t);
	s=1;
	printf("Scale Factor : ");
	scanf("%f",&s);
	a=ROUND(a);
	t=ROUND(t);

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Cube");

	glutDisplayFunc(display);
	initGL();
	glutMainLoop();

	return 0;
}