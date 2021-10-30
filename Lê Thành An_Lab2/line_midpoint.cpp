#include <GL/glut.h>
void initGL()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //R=0,G=0,B=0, anpha=1
	glOrtho(-320,320,-240,240,-1,1);	
}

void LineMidPointTH1(int x1,int y1,int x2,int y2)	
{
	
   	int Dx = x2-x1; 
	int Dy = y2-y1;
   	int p = 2*Dy-Dx;
  	int x = x1;	
	int y = y1;
	
	int c1 = 2*Dy;
	int c2 = 2*(Dy-Dx);
	
  	glBegin(GL_POINTS);
	glVertex2i(x,y);
	
	
	while (x < x2)  
	{
		if (p <0)	 
            p+= c1;
		else
            {
            	p+=c2;
			    y++;
			}
		x++;
        glVertex2i(x,y);
	}
	glEnd();
  	
}

void LineMidPointTH2(int x1,int y1,int x2,int y2)	
{
	
   	int Dx = x2-x1; 
	int Dy = y2-y1;
   	int p = 2*Dx-Dy;
  	int x = x1;	
	int y = y1;
	
	int c1 = 2*Dx;
	int c2 = 2*(Dx-Dy);
	
  	glBegin(GL_POINTS);
	glVertex2i(x,y);
	
	
	while (x < x2)  
	{
		if (p < 0)
			p+=c1;
		else
            {
        		p+=c2;
            	x++;
			}
		y++;
        glVertex2i(x,y);
	}
	glEnd();
  	
}

void LineMidPointTH3(int x1,int y1,int x2,int y2)	
{
	
   	int Dx = x2-x1; 
	int Dy = y2-y1;
   	int p = 2*Dy+Dx;
  	int x = x1;	
	int y = y1;
	
	int c1 = 2*Dy;
	int c2 = 2*(Dx+Dy);
	
  	glBegin(GL_POINTS);
	glVertex2i(x,y);
	
	
	while (x < x2)  
	{
		if (p < 0){
			p+= c2;
			y--;
		}
		else{
        	p+=c1;
		}
		x++;
        glVertex2i(x,y);
	}
	glEnd();
  	
}


void LineMidPointTH4(int x1,int y1,int x2,int y2)	
{
	
   	int Dx = x2-x1; 
	int Dy = y2-y1;
   	int p = 2*Dx+Dy;
  	int x = x1;	
	int y = y1;
	
	int c1 = 2*Dx;
	int c2 = 2*(Dx+Dy);
	
  	glBegin(GL_POINTS);
	glVertex2i(x,y);
	
	
	while (x < x2)  
	{
		if (p < 0){
			p+= c1;
		}
			
		else{
        	p+=c2;
        	x++;
		}
		
		y--;
		
        glVertex2i(x,y);
	}
	glEnd();
  	glFlush();
}

void drawX(int x1, int x2){	
	glBegin(GL_POINTS);
	while(x1 <= x2){
		glVertex2i(x1++,0);
	}
	glEnd();
  	glFlush();
}


void drawY(int y1, int y2){	
	glBegin(GL_POINTS);
	while(y1 <= y2){
		glVertex2i(0, y1++);
	}
	glEnd();
  	glFlush();
}

void mydisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	//he toa do
	drawX(-320, 320);
	drawY(-240, 240);
	// 0 <= m <= 1
	LineMidPointTH1(0, 0, 400, 170);
	// m > 1
	LineMidPointTH2(0, 0, 180, 220);
	//   -1 <= m <= 0
	LineMidPointTH3(0, 0, 500, -100);
	// m < -1
	LineMidPointTH4(0, 0, 100, -200);
	glViewport(0,0,640,480);
	glFlush();

}

int main(int argc, char** argv){
	int mode=GLUT_SINGLE | GLUT_RGB;
	glutInitDisplayMode(mode);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("THUAT TOAN VE DOAN THANG");
	 
	initGL();  
	glutDisplayFunc(mydisplay);    
	glutMainLoop();
}
