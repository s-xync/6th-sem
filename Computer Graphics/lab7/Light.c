#include<stdio.h>
#include <GL/glut.h>
#include<math.h>
int width=500;
int height=500;
int fps=30;
float x2=0.01;
static float fog_color[] = {0.8, 0.8, 0.8, 1.0};
static float diffuse[] = {1.0, 1.0, 1.0, 1.0};
static void
  Key(unsigned char key, int x, int y)
{
  switch (key) {
  case 'd':
    x2 *= 1.10;
    glFogf(GL_FOG_DENSITY, x2);
    glutPostRedisplay();
    break;
  case 'D':
    x2 /= 1.10;
    glFogf(GL_FOG_DENSITY, x2);
    glutPostRedisplay();
    break;
  case 27:
    exit(0);
  }
}

void drawcube(){
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_POLYGON);
glColor4f( 1.0, 0.0, 0.0,0.4 );
	glNormal3d(0,0,1);
     glVertex3f(  50.0f, -50.0f, -50.0f );      // P1 is red
       glVertex3f(  50.0f,  50.0f, -50.0f );      // P2 is green
       glVertex3f( -50.0f,  50.0f, -50.0f );      // P3 is blue
      glVertex3f( -50.0f, -50.0f, -50.0f );      // P4 is purple
 
  glEnd();
 	glDisable(GL_BLEND);

  // White side - BACK
  glBegin(GL_POLYGON);
	glNormal3d(0,0,-1);

  glColor3f(   0.0,  0.0, 1.0 );
  glVertex3f(  50.0f, -50.0f, 50.0f );
  glVertex3f(  50.0f,  50.0f, 50.0f );
  glVertex3f( -50.0f,  50.0f, 50.0f );
  glVertex3f( -50.0f, -50.0f, 50.0f );
  glEnd();
 
  // Purple side - RIGHT
  glBegin(GL_POLYGON);
  glColor3f(  1.0,  1.0,  0.0 );
  	glNormal3d(1,0,0);

  glVertex3f( 50.0f, -50.0f, -50.0f );
  glVertex3f( 50.0f,  50.0f, -50.0f );
  glVertex3f( 50.0f,  50.0f,  50.0f );
  glVertex3f( 50.0f, -50.0f,  50.0f );
  glEnd();
 
  // Green side - LEFT
  glBegin(GL_POLYGON);
  	glNormal3d(-1,0,0);

  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -50.0f, -50.0f,  50.0f );
  glVertex3f( -50.0f,  50.0f,  50.0f );
  glVertex3f( -50.0f,  50.0f, -50.0f );
  glVertex3f( -50.0f, -50.0f, -50.0f );
  glEnd();
 
  // Blue side - TOP
  glBegin(GL_POLYGON);
  	glNormal3d(0,1,0);

  glColor3f(   1.0,  0.0,  1.0 );
  glVertex3f(  50.0f,  50.0f,  50.0f );
  glVertex3f(  50.0f,  50.0f, -50.0f );
  glVertex3f( -50.0f,  50.0f, -50.0f );
  glVertex3f( -50.0f,  50.0f,  50.0f );
  glEnd();
 
  // Red side - BOTTOM
  glBegin(GL_POLYGON);
  	glNormal3d(0,-1,0);

  glColor3f(   1.0,  1.0,  1.0 );
  glVertex3f(  50.0f, -50.0f, -50.0f );
  glVertex3f(  50.0f, -50.0f,  50.0f );
  glVertex3f( -50.0f, -50.0f,  50.0f );
  glVertex3f( -50.0f, -50.0f, -50.0f );
  glEnd();
	
}
float x=0;
void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINES);
	glVertex3f(0,0,0);
	glVertex3f(0,0,400);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(0,0,0);
	glVertex3f(0,400,0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(0,0,0);
	glVertex3f(400,0,0);
	glEnd();
	
	glTranslatef(-10,-10,-20);
	glRotatef(x,0,1,0);
	glRotatef(2*x,0,0,1);
	glRotatef(3*x,1,0,0);
	drawcube();
	glLoadIdentity();
	
	glutSwapBuffers();
	//glFlush();
	x+=0.5;
}

void init (void){
	glClearColor (0.0, 0.0, 0.0, 0.0); // Set display-window color to white.
	glMatrixMode (GL_PROJECTION); // Set projection parameters.
	int w=width;
	int h=height;
	glOrtho(-1*w/2, w/2, -1*h/2, h/2, -100.0, 200.0);
	//glFrustum (-200,200,-200,200, -200,200);
	glEnable(GL_COLOR_MATERIAL);
}
void reshape(int w, int h)
{
	
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1*w/2, w/2, -1*h/2, h/2, -100.0, 200.0);
	//glFrustum (-200,200,-200,200, -200,200);
  glMatrixMode(GL_MODELVIEW);
}
void FPS(int s){
	glutPostRedisplay();
	glutTimerFunc(1000/fps,FPS,0);
}

void initLighting()
{

	
    // Enable lighting
	GLfloat lightpos[] = {120, 0, 0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    
}	
int main(int argc ,char **argv){
	glutInit (&argc, argv); // Initialize GLUT.
	glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE); // Set display mode.
	glutInitWindowSize (width, height); // Set display-window width and height.
	glutReshapeFunc(reshape);
	glViewport(0,0,width,height);
	glutCreateWindow ("Welcome"); // Create display window.
	init ( ); // Execute initialization procedure.
	initLighting(); 
	glMatrixMode( GL_PROJECTION );
	glEnable( GL_DEPTH_TEST );
	glMatrixMode( GL_MODELVIEW );	
	glutTimerFunc(0,FPS,0);	
	glEnable(GL_FOG);
  glFogf(GL_FOG_DENSITY, x2);
  glFogfv(GL_FOG_COLOR, fog_color);
  glutKeyboardFunc(Key);

	glutDisplayFunc (display); // Send graphics to display window.
	glutMainLoop ( ); // Display everything and wait.
	return 0;
}