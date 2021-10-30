#include <GL/glut.h>
#include<stdio.h>
void initGL()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //R=0,G=0,B=0, anpha=1
	glOrtho(-320,320,-240,240,-1,1);	
}

void put8pixel(int xc,int yc, int x, int y){
	glVertex2f( x+xc, y+yc,color);
	putglVertex2fpixel( y+xc, x+yc,color);
	putpixel( y+xc,-x+yc,color);
	putpixel( x+xc,-y+yc,color);
	putpixel(-x+xc,-y+yc,color);
	putpixel(-y+xc,-x+yc,color);
	putpixel(-y+xc, x+yc,color);
	putpixel(-x+xc, y+yc,color);
}

void LineBres(int x, int y, int r)	
{
	int x, y, p;
	x =0; y = r; p=3-2*r;
	while(x <=y){
		glVertex2f(x , y);  
	}
	
   	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f); 
  	glBegin(GL_POINTS);	
	
	
	glEnd();
  	glFlush();
}

void mydisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	LineBres(0, 200, 100, 100);
	glViewport(0,0,480,480);
	glFlush();

}

int main(int argc, char** argv){
	int mode=GLUT_SINGLE | GLUT_RGB;
	glutInitDisplayMode(mode);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Thuat toan ve doan thang bresenham");
	 
	initGL();  
	glutDisplayFunc(mydisplay);    
	glutMainLoop();
}
