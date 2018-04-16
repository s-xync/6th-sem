#include<stdlib.h>
#include<stdio.h>
#include<GL/glut.h>
#include <GL/gl.h>
int xa,ya,radius;
void drawcircle(){
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y){
        glClear (GL_COLOR_BUFFER_BIT);
        glColor3f (1.0, 0.0, 1.0);
        glBegin(GL_POINTS);
        glVertex2s(xa + x, ya + y);
        glVertex2s(xa + y, ya + x);
        glVertex2s(xa - y, ya + x);
        glVertex2s(xa - x, ya + y);
        glVertex2s(xa - x, ya - y);
        glVertex2s(xa - y, ya - x);
        glVertex2s(xa + y, ya - x);
        glVertex2s(xa + x, ya - y);

        if (err <= 0)
        {
            y += 1;
            err += 2*y + 1;
        }
        else if (err > 0)
        {
            x -= 1;
            err -= 2*x + 1;
        }
    }
    glEnd();
    glFlush();
}

void init(void){
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glOrtho(0.0, 500.0, 0.0, 500.0, -1.0, 1.0);
}

int main(int argc, char** argv){
    printf("Radius: ");
    scanf("%d", &radius);

    printf("Center: ");
    scanf("%d %d", &xa, &ya);
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("CIRCLE");
    init ();
    glutDisplayFunc(drawcircle);
    glutMainLoop();
    return 0;
    return 0;
}