/*
* to run the program
** gcc pyramid.c -lGL -lGLU -lGLEW -lglut
** ./a.out
* use UP DOWN LEFT RIGHT arrow keys to rotate the pyramid
*/
#include <stdio.h>
#include <GL/glut.h>
double rotate_y=0;
double rotate_x=0;
void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
   glTranslatef(0.0f,0.0f,-7.0f); //deep into the viewport
   glRotatef(rotate_x,1.0,0.0,0.0);
   glRotatef(rotate_y,0.0,1.0,0.0);
   glBegin(GL_TRIANGLES); //Begin drawing the pyramid with 4 triangles
	  //Define vertices in counter-clockwise (CCW) order with normal pointing out
	  //Front
	  glColor3f(1.0f,0.0f,0.0f); //Red
	  glVertex3f(0.0f,1.0f,0.0f);
	  glVertex3f(-1.0f,-1.0f,1.0f);
	  glVertex3f(1.0f,-1.0f,1.0f);
	  //Right
	  glColor3f(0.0f,0.0f,1.0f); //Blue
	  glVertex3f(0.0f,1.0f,0.0f);
	  glVertex3f(1.0f,-1.0f,1.0f);
	  glVertex3f(1.0f,-1.0f,-1.0f);
	  //Back
	  glColor3f(0.0f,1.0f,0.0f); //Green
	  glVertex3f(0.0f,1.0f,0.0f);
	  glVertex3f(1.0f,-1.0f,-1.0f);
	  glVertex3f(-1.0f,-1.0f,-1.0f);
	  //Left
	  glColor3f(1.0f,1.0f,0.0f); //Yellow
	  glVertex3f(0.0f,1.0f,0.0f);
	  glVertex3f(-1.0f,-1.0f,-1.0f);
	  glVertex3f(-1.0f,-1.0f,1.0f);
	  glEnd();
   glutSwapBuffers();  //Swap the front and back frame buffers (double buffering)
}
void reshape(GLsizei width,GLsizei height){
	if(height==0){
		height=1;
	}
	GLfloat aspect=(GLfloat)width/(GLfloat)height;
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,aspect,0.1f,100.0f);
}
void initGL(){
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClearDepth(1.0f);      
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
}
void specialKeys(int key,int x,int y){
	if(key==GLUT_KEY_RIGHT){
		rotate_y+=5;
	}
	else if(key==GLUT_KEY_LEFT){
		rotate_y -=5;
	}
	else if(key==GLUT_KEY_UP){
		rotate_x+=5;
	}
	else if(key==GLUT_KEY_DOWN){
		rotate_x-=5;
	}
	glutPostRedisplay();
}
int main(int argc,char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(50,50);
	glutCreateWindow("3D Pyramid");
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	initGL();
	glutSpecialFunc(specialKeys);
	glutMainLoop();
	return 0;
}