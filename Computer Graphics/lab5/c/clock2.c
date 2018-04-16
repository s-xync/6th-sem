/*
Title:	Clock
Author:	Wizche
*/

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include <GL/gl.h>
#include <GL/glut.h>

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500
#define PI 3.141592653589793

GLfloat secAngle=0.0;
GLfloat minAngle=0.0;
GLfloat hourAngle=0.0;
GLfloat hour=0.0;

void draw();
void reshape(int width, int height);
void init();
void keyboard(unsigned char, int, int);
void drawClock();
void rotateSeconds();
void Synchronize();
void outputText(double x,double y,double z,double scale,char *s);
	
int main(int argc, char** argv) {

	glutInit(&argc, argv);
 	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("Clock using OpenGL - Wizche");
	init();
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(1000, rotateSeconds, 0);
	Synchronize();
	glutMainLoop();

	return 0;
}

void Synchronize()
{
	GLfloat h,m,s;

	time_t rawtime;
	struct tm * timeinfo;
	char buffer [80];
	
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	strftime(buffer, 80, "System time: %I:%S", timeinfo);

	if(timeinfo->tm_hour > 12) // Converting from 25h to 12h
	{	
		h=(timeinfo->tm_hour-12)-(hourAngle/30.0);
	}
	else
	{
		h=(timeinfo->tm_hour)-(hourAngle/30.0);
	}
	
	m=timeinfo->tm_min-(minAngle/6.0);
	s=timeinfo->tm_sec-(secAngle/6.0);

	printf("System time: %d : %d :%d\n", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	printf("Adapting clock to system time...\n");
	secAngle = timeinfo->tm_sec * 6.0;
	minAngle = timeinfo->tm_min * 6.0;

	if(timeinfo->tm_hour > 12) // Converting from 25h to 12h
	{	
		hourAngle = ((timeinfo->tm_hour-12) * 30.0) + (float)((float)1/12.0 * minAngle);
		hour = ((timeinfo->tm_hour-12) * 30.0);
	}
	else
	{
		hourAngle = ((timeinfo->tm_hour) * 30.0) + (float)((float)1/12.0 * minAngle);		
		hour = ((timeinfo->tm_hour-12) * 30.0);
	}
	printf("Hour angle: %3.2f [%3.1f]\n", hourAngle, (float)((float)1/12 * minAngle));
	printf("Min angle: %3.2f\n", minAngle);
	printf("Clock deviation: %3.1f h:%3.1fm:%3.1fs\n", h,m,s); 
}



void rotateSeconds(int extra)
{
secAngle += 6.0;

if(secAngle == 360.0)
{
	secAngle = 0.0;
	minAngle += 6.0;
	hourAngle = hour + ((float)1.0/12.0 * minAngle);
	Synchronize();
	if(minAngle == 360.0)
	{
		minAngle = 0.0;
		hourAngle+=6.0;

		if(hourAngle == 360.0)
		{
			hourAngle = 0.0;
		}
	}
}
printf("Time: %3dh:%3.0fm:%3.0fs [%3.1f-%3.1f-%3.1f]\n", (int)(hour/30.0), minAngle/6, secAngle/6, hourAngle, minAngle, secAngle);
glutPostRedisplay();
glutTimerFunc(1000, rotateSeconds, 0);
}
void keyboard(unsigned char key, int x, int y)
{
   switch (key) 
   {
      	case 27:
         	exit(0);
         	break;
   }
}


void init()
{
}	


void outputText(double x,double y,double z,double scale,char *s)
{
   int i;

   glPushMatrix();
   glTranslatef(x,y,z);
   glScalef(scale,scale,scale);
   for (i=0;i<strlen(s);i++)
      glutStrokeCharacter(GLUT_STROKE_ROMAN,s[i]);
   glPopMatrix();
}

void drawClock() {

char buff[100];
GLfloat x1=0.0;
GLfloat y1=0.0;
GLfloat z1=0.0;
GLfloat radius = 10.0;
GLfloat smallradius = 3.0;
int angle;

	glLoadIdentity();
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glOrtho(0.0, 20.0, 0.0, 20.0, -10.0, 10.0);

	// Draw circle
	glPushMatrix();
	glTranslatef(10.0, 10.0, 0.0);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0,0.2,1.0);
	glVertex3f(x1, y1, z1);
	for(angle=0; angle <= 360; angle +=1)
		glVertex3f(x1 + cos(angle * PI/180.0f)* radius, y1 + sin(angle * PI/180.0f) * radius, z1);
	glEnd();
	glPopMatrix();

	//draw smaller circle
	glPushMatrix();
	glTranslatef(14.0, 6.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.4,0.8,0.2);
	glVertex3f(x1, y1, z1);
	for(angle=0; angle <= 360; angle +=1)
		glVertex3f(x1 + cos(angle * PI/180.0f)* smallradius, y1 + sin(angle * PI/180.0f) * smallradius, z1+0.5);
	glEnd();
	glPopMatrix();

	// draw ticks
	glPushMatrix();
	glTranslatef(10.0, 10.0, 0.0);
	glColor3f(0.2,0.2,0.2);
	glLineWidth(2);
	for(angle=0; angle <= 360; angle +=30)
	{
	glBegin(GL_LINES);
	//printf("Angle: %d\n", angle);
		if(angle == 0.0 || angle==90.0 || angle == 180.0 || angle == 270.0 || angle == 360.0 )
		{
		glColor3f(1.0,0.2,0.2);
		glVertex3f(x1 + cos(angle * PI/180.0f)* (radius-1.2), y1 + sin(angle * PI/180.0f) * (radius-1.2), z1+0.1);
		glVertex3f(x1 + cos(angle * PI/180.0f)* radius, y1 + sin(angle * PI/180.0f) * radius, z1+0.1);
		}
		else
		{
		glColor3f(0.2,0.2,0.2);
		glVertex3f(x1 + cos(angle * PI/180.0f)* (radius-0.5), y1 + sin(angle * PI/180.0f) * (radius-0.5), z1);
		glVertex3f(x1 + cos(angle * PI/180.0f)* radius, y1 + sin(angle * PI/180.0f) * radius, z1);
		}
	glEnd();
	}
	glPopMatrix();

	// Draw mini seconds line
	glColor3f(1.0,1.0,0.0);
	glLineWidth(1);
	glPushMatrix();

	glTranslatef(14.0, 6.0, 0.0);
	glRotatef(-secAngle, 0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 2.5, 1.0);
	glEnd();
	glPopMatrix();

	// Draw seconds line
	glColor3f(1.0,1.0,0.0);
	glLineWidth(1);
	glPushMatrix();

	glTranslatef(10.0, 10.0, 0.0);
	glRotatef(-secAngle, 0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 2.0);
	glVertex3f(0.0, 8.5, 2.0);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.3, 8.5, 1.0);
	glVertex3f(0.3, 8.5, 1.0);
	glVertex3f(0.0, 8.8, 1.0);
	glEnd();
	glPopMatrix();

	// Draw minutes line
	glColor3f(1.0,0.0,0.0);
	glLineWidth(2);
	glPushMatrix();

	glTranslatef(10.0, 10.0, 0.0);
	glRotatef(-minAngle, 0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 9.0, 1.0);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.3, 9.0, 1.0);
	glVertex3f(0.3, 9.0, 1.0);
	glVertex3f(0.0, 9.5, 1.0);
	glEnd();
	glPopMatrix();

	// Draw hour line
	glColor3f(0.0,1.0,0.0);
	glLineWidth(3);
	glPushMatrix();

	glTranslatef(10.0, 10.0, 0.0);
	glRotatef(-hourAngle, 0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 6.5, 0.0);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.3, 6.5, 1.0);
	glVertex3f(0.3, 6.5, 1.0);
	glVertex3f(0.0, 6.8, 1.0);
	glEnd();
	glPopMatrix();

	// Draw central point
	glColor3f(0.0,0.0,0.0);
	glPointSize(10.0);
	glPushMatrix();
	glTranslatef(10.0, 10.0, 0.0);
	glBegin(GL_POINTS);
	glVertex3f(0.0, 0.0, 4.0);
	glEnd();
	glPopMatrix();

	sprintf(buff, "%2dh:%2.0fm:%2.0fs", (int)(hour/30.0), minAngle/6, secAngle/6, hourAngle, minAngle, secAngle); 

	outputText(6.0,12.0,3.0,0.01, buff); // NOT WORKING WHY?????

	glFlush();
}

void reshape(int w, int h) {

	//glutReshapeWindow(width, width);

	glViewport(0, 0, (GLsizei) w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 
	if (w <= h)
		glOrtho(0.0, 20.0, 0.0, 20.0*((double)h/(double)w), -10.0, 10.0);
	else
		glOrtho(0.0, 20.0*((double)w/(double)h), 0.0, 20.0, -10.0, 10.0);
	glutDisplayFunc(drawClock);
}
