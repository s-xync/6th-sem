#include <GL/glut.h>
#include <stdio.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <math.h>
GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_position[] = {12.0, -15.0, 120.0, 0.6};
 GLfloat xRotated, yRotated, zRotated;
 GLsizei xw = 100 , yw =100 ;
void init(void)
{
glClearColor(0,0,0,0);
glOrtho(-100.0, 100.0, -100.0, 100.0, -200.0, 200.0); 
glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
}

typedef GLint vertex3 [3] ;

vertex3 pt [8] = {  {-1,-1,-1} ,{-1,1,-1} ,{1,-1,-1}, {1,1,-1},{-1,-1,1},{-1,1,1},{1,-1,1},{1,1,1} };
void quad (GLint n1 ,GLint n2 ,GLint n3 ,GLint n4,float i,float j,float k )
{
  glBegin (GL_QUADS);
  glColor3f(i,j,k);
  glVertex3iv (pt [n1]);
  glVertex3iv (pt [n2]);  
  glVertex3iv (pt [n3]);
  glVertex3iv (pt [n4]);
 glEnd();
}

void cube ()
{
  quad(6,2,3,7,1.0,0.5,0.5);
  quad(5,1,0,4,1.0,0.0,1.0);
  quad(7,3,1,5,0.0,0.0,1.0);
  quad(4,0,2,6,1.0,1.0,0.0);
  quad(2,0,1,3,0.0,1.0,0.0);
  quad(7,5,4,6,1.0,0.0,0.0);
}

void DrawCube(void)
{

     yRotated = 0;
     xRotated = 0;
     zRotated = 45; 
     glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();
    glTranslatef(0.0,0.0,-12.5);
    glRotatef(xRotated,1.0,0.0,0.0);
    // rotation about Y axis
    glRotatef(yRotated,0.0,1.0,0.0);
    // rotation about Z axis
    glRotatef(zRotated,0.0,0.0,1.0);

    
 
    glBegin(GL_LINES);
// draw line for x axis
glColor3f(1.0, 0.0, 1.0);
glVertex3f(0.0, 0.0, 0.0);
glVertex3f(100.0, 0.0, 0.0);
// draw line for y axis
glColor3f(1.0, 1.0, 1.0);
glVertex3f(0.0, 0.0, 0.0);
glVertex3f(0.0, 100.0, 0.0);
// draw line for Z axis
glColor3f(1.0, 1.0, 1.0);
glVertex3f(0.0, 0.0, 0.0);
glVertex3f(0.0, 0.0, 100.0);
  glEnd();  
  cube();          // End Drawing The Cube
glFlush();
}



 

void reshape(int x, int y)
{
     if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();

    // gluOrtho2D (0.0, (GLdouble) x , 0.0, (GLdouble) y);

    // glClear (GL_COLOR_BUFFER_BIT);
    //Angle of view:40 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0

    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}

int main(int argc, char** argv){

glutInit(&argc, argv);
//we initizlilze the glut. functions
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowPosition(100, 100);
glutCreateWindow(argv[0]);
init();
glutDisplayFunc(DrawCube);
glutReshapeFunc(reshape);
glutMainLoop();
return 0;
}
