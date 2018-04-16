//-lfreeglut -lopengl32 -lglu32
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
double rotate_y=0; 
double rotate_x=0;
float round_value(float v)
{
  return floor(v + 0.5);
}

void draw_pixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
}
void drawLine(double X1,double Y1,double X2,double Y2)
{
  double dx=(X2-X1);
  double dy=(Y2-Y1);
  double steps;
  float xInc,yInc,x=X1,y=Y1;
  /* Find out whether to increment x or y */
  steps=(abs(dx)>abs(dy))?(abs(dx)):(abs(dy));
  xInc=dx/(float)steps;
  yInc=dy/(float)steps;
  /* Clears buffers to preset values */
  glClear(GL_COLOR_BUFFER_BIT);

  /* Plot the points */
	glPointSize(2.0f);
	draw_pixel(x,y); 
	int k;
  /* For every step, find an intermediate vertex */
  for(k=0;k<steps;k++)
  {
    x+=xInc;
    y+=yInc;
    /* printf("%0.6lf %0.6lf\n",floor(x), floor(y)); */
    draw_pixel(x, y);
  }

}
void display(void){
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glRotatef( rotate_x, 1.0, 0.0, 0.0 );
  glRotatef( rotate_y, 0.0, 1.0, 0.0 );
  glBegin(GL_POLYGON);
 
  glColor3f( 0.0, 0.5, 0.0 );     glVertex3f(  0.5, -0.5, -0.5 );      // P1 is red
  glColor3f( 0.0, 0.5, 0.0 );     glVertex3f(  0.5,  0.5, -0.5 );      // P2 is green
  glColor3f( 0.0, 0.5, 0.0 );     glVertex3f( -0.5,  0.5, -0.5 );      // P3 is blue
  glColor3f( 0.0, 0.5, 0.0 );     glVertex3f( -0.5, -0.5, -0.5 );      // P4 is purple
 
  glEnd();
 
  // White side - BACK
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  1.0, 0.0 );
  glVertex3f(  0.5, -0.5, 0.5 );
  glVertex3f(  0.5,  0.5, 0.5 );
  glVertex3f( -0.5,  0.5, 0.5 );
  glVertex3f( -0.5, -0.5, 0.5 );
  glEnd();
 
  // Purple side - RIGHT
  glBegin(GL_POLYGON);
  glColor3f(  1.0,  0.0,  1.0 );
  glVertex3f( 0.5, -0.5, -0.5 );
  glVertex3f( 0.5,  0.5, -0.5 );
  glVertex3f( 0.5,  0.5,  0.5 );
  glVertex3f( 0.5, -0.5,  0.5 );
  glEnd();
 
  // Green side - LEFT
  glBegin(GL_POLYGON);
  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -0.5, -0.5,  0.5 );
  glVertex3f( -0.5,  0.5,  0.5 );
  glVertex3f( -0.5,  0.5, -0.5 );
  glVertex3f( -0.5, -0.5, -0.5 );
  glEnd();
 
  // Blue side - TOP
  glBegin(GL_POLYGON);
  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  0.5,  0.5,  0.5 );
  glVertex3f(  0.5,  0.5, -0.5 );
  glVertex3f( -0.5,  0.5, -0.5 );
  glVertex3f( -0.5,  0.5,  0.5 );
  glEnd();
 
  // Red side - BOTTOM
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  0.5, -0.5, -0.5 );
  glVertex3f(  0.5, -0.5,  0.5 );
  glVertex3f( -0.5, -0.5,  0.5 );
  glVertex3f( -0.5, -0.5, -0.5 );
  glEnd();
 
  glFlush();
  glutSwapBuffers();
 
}
void specialKeys( int key,int state, int x, int y ) {
 
  //  Right arrow - increase rotation by 5 degree
  if (key == GLUT_LEFT_BUTTON)
    rotate_y += 5;
 
  //  Left arrow - decrease rotation by 5 degree
  //else if (key == GLUT_KEY_LEFT)
    //rotate_y -= 5;
 
  //else if (key == GLUT_KEY_UP)
    //rotate_x += 5;
 
  else if (key == GLUT_RIGHT_BUTTON)
    rotate_x -= 5;
 
  //  Request display update
  glutPostRedisplay();
 
}
void Init()
{
  /* Set clear color to white */
  glClearColor(0.0,0.0,0.0,0);
  /* Set fill color to black */
  /* glViewport(0 , 0 , 640 , 480); */
  /* glMatrixMode(GL_PROJECTION); */
  /* glLoadIdentity(); */
  gluOrtho2D(0 , 640 , 0 , 480);
  glEnable(GL_DEPTH_TEST);

}
void main(int argc, char **argv)
{
  /* Initialise GLUT library */
  glutInit(&argc,argv);
  /* Set the initial display mode */
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  /* Set the initial window position and size */
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  /* Create the window with title "DDA_Line" */
  glutCreateWindow("DDA_Line");
  /* Initialize drawing colors */
  Init();
  /* Call the displaying function */
  glutDisplayFunc(display);
  glutMouseFunc(specialKeys);
  /* Keep displaying untill the program is closed */
  glutMainLoop();
}
