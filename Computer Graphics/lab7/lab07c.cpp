#include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>
GLfloat red[]={1.0, 0.0, 0.0,0.2};
GLfloat white[]={1.0,1.0,0.0,0.2};
GLfloat density=0.23;

GLfloat fogColor[4] = {0.5, 0.5, 0.0, 0.02};
void init(int argc, char** argv)
{
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400); //Window size
	glutCreateWindow("Introduction to OpenGL"); //Create a window
	glEnable(GL_DEPTH_TEST); //Make sure 3D drawing works when one object is in front of another
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
   // glEnable (GL_FOG);
   // glFogi (GL_FOG_MODE, GL_EXP2);
   // glFogfv (GL_FOG_COLOR, fogColor); //set the fog color to
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glClearColor(0.0,0.2,0.2,0.2);
    glFogf (GL_FOG_DENSITY, density); //set the density to the
    glHint (GL_FOG_HINT, GL_NICEST); // set the fog to look the
    // Create light components
    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 0.0f };
    GLfloat diffuseLight[] = { 0.8f, 1.0f, 0.8, 0.0f };
    GLfloat specularLight[] = { 0.5f, 1.0f, 1.0f, 0.2f };
    GLfloat position[] = { -1.5f, 1.0f, -4.0f, 0.5f };

    // Assign created components to GL_LIGHT0
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    GLfloat spot_pos[] = { 0.0, 5.0, 0.0, 1.0 };
    GLfloat spot_dir[] = { 0.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, spot_pos);
    GLfloat angle[]={45.0f};
    glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, angle);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_dir);
}
//Called when the window is resized
void handleResize(int w, int h)
{
	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective

	//Set the camera perspective
	glLoadIdentity(); //Reset the camera
	gluPerspective(45.0,				  //The camera angle
				   (double)w / (double)h, //The width-to-height ratio
				   1.0,				   //The near z clipping coordinate
				   200.0);				//The far z clipping coordinate
}

//Draws the 3D scene
void draw()
{
	 //Clear screen
	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	 glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	 glLoadIdentity(); //Reset the drawing perspective
	 glMaterialfv(GL_FRONT,GL_DIFFUSE,red);
     glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,red);
     glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
	 glTranslatef(0.0,0.0,-2.0);
     gluLookAt(1.0f, 1.0f, 1.0f, 0.2f,0.2f,0.2f, 0.0, 1.0, 0.0);
     glColor4f(1.0f,0.5f,1.0f,0.5);
       glutSolidCube(1.0);
       glTranslatef(0.0,0.0,-2.0);
       glColor4f(0.0f,0.0f,1.0f,0.2);
       glutSolidCube(1.5);

	glutSwapBuffers(); //Send scene to the screen to be shown
}

int main(int argc, char** argv) {
	init(argc, argv); //Initialize rendering
     //  GLfloat ambient[] = { 0.0f, 1.0f, 1.0f };
   // glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    //glEnable(GL_LIGHT0);
	//Set functions for glutMainLoop to call
	glutDisplayFunc(draw);
	glutReshapeFunc(handleResize);

	glutMainLoop(); //Start the main loop. glutMainLoop doesn't return.
	return 0; //This line is never reached
}

