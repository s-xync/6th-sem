/*
**** gcc cubicInterpolation.c -lGL -lGLU -lGLEW -lglut
**** ./a.out
Use the pointer to move the control points around.
*/

#include <stdio.h>
#include <GL/glut.h>
#define N 4
#define D 2
#define T 2000
static GLfloat ctrlPoints[N][3] = {{200, 200, 0}, {300, 350, 0}, {400,300, 0}, {480,250,0}};
int windowWidth = 700;
int windowHeight = 600;
int MOVENAME = -1;
int pickRadius = 50;
void cubicInterpolationCurve(){
	glLineWidth(2.0);
	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < N; i++){
		glVertex2i(ctrlPoints[i][0],ctrlPoints[i][1]);
	}
	glEnd();
	glFlush();
	glPointSize(10.0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < N; i++){
		glVertex2i(ctrlPoints[i][0],ctrlPoints[i][1]);
	}
	glEnd();
	glFlush();
	glLineWidth(5.0);
	glColor3f(0.4f, 1.0f, 0.4f);
	GLfloat bu[N];
	glBegin(GL_LINE_STRIP);
	for (int uInt = 0; uInt <= T; uInt++){
		GLfloat u = uInt/(GLfloat)T;
		bu[0] = (-9.0/2.0)*(u-(1.0/3.0))*(u-(2.0/3.0))*(u-1.0);
		bu[1] = (27.0/2.0)*u*(u-(2.0/3.0))*(u-1.0);
		bu[2] = (-27.0/2.0)*u*(u-(1.0/3.0))*(u-1.0);
		bu[3] = (9.0/2.0)*u*(u-(1.0/3.0))*(u-(2.0/3.0));
		GLfloat x = 0.0;
		GLfloat y = 0.0;
		for (int i = 0; i < N; i++){
			x += bu[i]*ctrlPoints[i][0];
			y += bu[i]*ctrlPoints[i][1];
		}
		glVertex2i(x,y);
	}
	glEnd();
	glFlush();
}
void displayFunction(){
	glClear(GL_COLOR_BUFFER_BIT);
	cubicInterpolationCurve();
	glFlush();
}
void init(){
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
}
void pickerFunction(int button, int state, int xPosition, int yPosition){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		GLuint newX = xPosition;
		GLuint newY = windowHeight - yPosition;
		int choiceFound = 0;
		for (int i = 0; i < N && !choiceFound; i++){
			if ((abs(ctrlPoints[i][0] - newX) <= pickRadius)&&(abs(ctrlPoints[i][1] - newY) <= pickRadius)){
				MOVENAME = i;
				choiceFound = 1;
			}
		}
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
		MOVENAME = -1;
	}
	glutPostRedisplay();
}
void mouseMoveFunction(int xPosition, int yPosition){
	if (MOVENAME > -1){
		GLuint newX = xPosition;
		GLuint newY = windowHeight - yPosition;
		ctrlPoints[MOVENAME][0] = newX;
		ctrlPoints[MOVENAME][1] = newY;
		glutPostRedisplay();
	}
}
void reshape(int width, int height){
	glViewport(0, 0, (GLsizei) width, (GLsizei) height);
	windowWidth = width;
	windowHeight = height;
}
int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Cubic Cardinal Interpolation Curve");
	glutDisplayFunc(displayFunction);
	glutMouseFunc(pickerFunction);
	glutMotionFunc(mouseMoveFunction);
	glutReshapeFunc(reshape);
	init();
	glutMainLoop();
	return 0;
}