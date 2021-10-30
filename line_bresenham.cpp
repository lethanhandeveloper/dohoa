#include <GL/glut.h>
void initGL()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //R=0,G=0,B=0, anpha=1
	glOrtho(-320,320,-240,240,-1,1);	
}

void LineBresTH1(int x1,int y1,int x2,int y2)	
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

void LineBresTH2(int x1,int y1,int x2,int y2)	
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

void LineBresTH3(int x1,int y1,int x2,int y2)	
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
			y--;
			p+= c2;
		}
			
		else{
        	p+=c1;
		}
		x++;
        glVertex2i(x,y);
	}
	glEnd();
  	
}


void LineBresTH4(int x1,int y1,int x2,int y2)	
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
			x--;
			p+= c2;
		}
			
		else{
        	p+=c1;
		}
		y++;
        glVertex2i(x,y);
	}
	glEnd();
  	glFlush();
}

void mydisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	// 0 <= m <= 1
	LineBresTH1(0, 0, 100, 100);
	// m > 1
	LineBresTH2(0, 0, 200, 400);
	//   -1 <= m <= 0
	LineBresTH3(0, 200, 500, 100);
	// m < -1
	//LineBresTH4(0, 100, -100, 300);
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
