#include <GL/glut.h>
#include<stdio.h>
void initGL()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //R=0,G=0,B=0, anpha=1
	glOrtho(-320,320,-240,240,-1,1);	
}

void draw8point(int xc, int yc, int x, int y)
{
	//x;y y;x -x;y -y;x x;-y y;-x; -x;-y -y;-x
	glBegin(GL_POINTS);
		glVertex2i(xc + x, yc + y);
		glVertex2i(xc + y, yc + x);
		glVertex2i(xc + y, yc - x);
		glVertex2i(xc + x, yc - y);
		glVertex2i(xc - x, yc - y);
		glVertex2i(xc - y, yc - x);
		glVertex2i(xc - y, yc + x);
		glVertex2i(xc - x, yc + y);
	glEnd();
}

void CircleMidpoint(int xc,int yc,int R )	
{	 

   	float P;
	int y = R; 
	int x = 0;
	P = 5/4 - R;
	draw8point(xc,yc,x,y);
	while (x < y) 
    	{
		if (P <0)	// Chon diem P
            {
			P += 2*x + 3;
            
            }
        else      // Chon diem S
            {	
            P += 2*(x - y) + 5;
            y--;
	        }
   
		x++;
        draw8point(xc,yc,x,y);
		}
}

void CircleBres(int xc, int yc, int r){
	int x =0 , y = r, p = 3-2*r;
	
	while (x<=y) {
		draw8point(xc,yc,x,y);
		if (p<0) p+=4*x+6;
		else{ 
			p+=4*(x-y)+10;
			y--;
		}
		x++;
	}
}

void mydisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	CircleBres(0, 0, 200); //Tâm C(0,0) bán kính 200
	glViewport(0,0,640,480);
	glFlush();

}

int main(int argc, char** argv){
	int mode=GLUT_SINGLE | GLUT_RGB;
	glutInitDisplayMode(mode);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Thuat toan ve duong tron");
	 
	initGL();  
	glutDisplayFunc(mydisplay);    
	glutMainLoop();
}
