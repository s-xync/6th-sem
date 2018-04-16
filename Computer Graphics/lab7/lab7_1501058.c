#include <GL/glut.h>
#include <stdlib.h>
GLfloat red[]={1.0, 0.0, 0.0,0.2};
GLfloat white[]={1.0,1.0,1.0,0.2};
GLfloat density=0.23;
GLfloat fogColor[4] = {0.0, 0.0, 1.0, 0.02};
void init(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Light Sources");
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	//to use the light source enable this
	glEnable(GL_LIGHT0);
	//to use fog enable this
	glEnable (GL_FOG);
	glFogi (GL_FOG_MODE, GL_EXP2);
	glFogfv (GL_FOG_COLOR, fogColor);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glClearColor(0.0,0.2,0.2,0.2);
	glFogf (GL_FOG_DENSITY, density);
	glHint (GL_FOG_HINT, GL_NICEST);
	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 0.0f };
	GLfloat diffuseLight[] = { 0.8f, 1.0f, 0.8, 0.0f };
	GLfloat specularLight[] = { 0.5f, 1.0f, 1.0f, 0.2f };
	GLfloat position[] = { -1.5f, -10.0f, 4.0f, 0.5f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
    //to use the spotlight enable the whole spotlight block below
    //spotlight start
	GLfloat spot_pos[] = { 0.0, 5.0, 0.0, 1.0 };
	GLfloat spot_dir[] = { 0.0, -1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, spot_pos);
	GLfloat angle[]={45.0f};
	glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, angle);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_dir);
    //spotlight end
}
void handleResize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(double)w / (double)h,1.0,200.0);
}
void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMaterialfv(GL_FRONT,GL_DIFFUSE,red);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,red);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
	glTranslatef(0.0,0.0,-2.0);
	gluLookAt(1.0f, 1.0f, 1.0f, 0.2f,0.2f,0.2f, 0.0, 1.0, 0.0);
	glutSolidCube(1.0);
	glutSwapBuffers();
}
int main(int argc, char** argv) {
	init(argc, argv);
	glutDisplayFunc(draw);
	glutReshapeFunc(handleResize);
	glutMainLoop();
	return 0;
}

