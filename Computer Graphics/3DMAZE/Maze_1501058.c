/**
    gcc Maze_1501058.c -lGL -lGLU -lGLEW -lglut -lm
    ./a.out
**/
#include <GL/glut.h>
#include <math.h>
#include<stdio.h>
const int map[17][17] =	{{1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1},
                    	{1,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,1},
                    	{1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,0,1},
                    	{1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1},
	                    {1,0,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1},
	                    {1,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,1},
	                    {1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1},
	                    {1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1},
	                    {1,0,1,1,1,0,1,0,2,0,1,0,1,1,1,1,1},
	                    {1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,1},
	                    {1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1},
	                    {1,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1},
	                    {1,0,1,0,1,0,1,1,1,0,1,1,1,1,1,0,1},
	                    {1,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1},
	                    {1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1},
	                    {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1},
	                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
int mapi,mapj;
float lx=7.5;
float lz=-0.5;
float langle=0;
const GLfloat light_ambient[]={0.0f,0.0f,0.0f,1.0f};
const GLfloat light_diffuse[]={1.0f,1.0f,1.0f,1.0f};
const GLfloat light_specular[]={1.0f,1.0f,1.0f,1.0f};
const GLfloat light_position[]={8.0f,8.0f,-8.0f,1.0f};
const GLfloat mat_ambient[]={1.0f,1.0f,1.0f,1.0f};
const GLfloat mat_diffuse[]={0.5f,0.5f,0.5f,1.0f};
const GLfloat mat_specular[]={1.0f,1.0f,1.0f,1.0f};
const GLfloat high_shininess[]={50.0f};

void generatemap(){
    for(mapi=0;mapi<17;++mapi){
        for(mapj=0;mapj<17;++mapj){
            if((mapi+mapj)%2==0)
                glColor3ub(0,102,0);
            else
                glColor3ub(0,153,0);
            if(map[mapi][mapj]==1){
                glPushMatrix();
                    glTranslatef((mapj+0.5),0,-1*(mapi+0.5));
                    glutSolidCube(1);
                glPopMatrix();
                glPushMatrix();
                    glTranslatef((mapj+0.5),1,-1*(mapi+0.5));
                    glutSolidCube(1);
                glPopMatrix();
            }
            if(map[mapi][mapj]==2){
                glColor3ub(255,255,0);
                glPushMatrix();
                    glTranslatef((mapj+0.5),-0.35,-1*(mapi+0.5));
                    glutSolidCube(0.3);
                glPopMatrix();
            }
        }
    }
    glColor3ub(255,180,0);
    glPushMatrix();
        glTranslatef(8.5,-9,-8.5);
        glutSolidCube(17);
    glPopMatrix();
}

void init(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glClearColor(1,1,1,1);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT,viewport);
    gluPerspective(90,(double)viewport[2]/(double)viewport[3],0.1,100);
    gluLookAt(lx,5,lz,lx+sin(langle),2,lz-cos(langle),0,1,0);
    glMatrixMode(GL_MODELVIEW);
    generatemap();
    glutSwapBuffers();
}

void specialkeys(int key, int x, int y){
    float fraction = 0.05;
    switch(key){
        case GLUT_KEY_UP:
        lx=lx+fraction*sin(langle);
        lz=lz-fraction*cos(langle);
        break;
        case GLUT_KEY_DOWN:
        lx=lx-fraction*sin(langle);
        lz= lz+fraction*cos(langle);
        break;
        case GLUT_KEY_LEFT:
	    langle-=M_PI/180;
        break;
        case GLUT_KEY_RIGHT:
        langle+=M_PI/180;
        break;
        glutPostRedisplay();
    }
}

void reshape(int w,int h){
    glViewport(0,0,w,h);
}

int main(int argc,char **argv){
    glutInit(&argc,argv);
    glutInitWindowSize(1280,720);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("3D MAZE");
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialkeys);
    init();
    glutMainLoop();
    return 0;
}
