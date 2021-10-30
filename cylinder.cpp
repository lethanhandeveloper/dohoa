#include <GL/glut.h>
#include <math.h>

typedef struct{
	float x; float y; float z;
}Point;

float theta = 250, phi = 50, D = 6.0f, R = 10.0f;

void initGL()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //R=0,G=0,B=0, anpha=1
	glOrtho(-40, 40,-80,80,-1,1);	
}

//chieu song song
Point transform(Point &p){
	p.x = -p.x * sin(theta) + p.y * cos(theta);
	p.y = -p.x * cos(theta) * sin(phi) 
							-p.y * sin(theta) * sin(phi) + p.z * cos(phi);
							
	p.z = -p.x * cos(theta) * cos(phi) - p.y * sin(theta) * cos(phi)
							- p.z * sin(phi) + R;
	return p;
}

void drawPoint(Point P){
	glBegin(GL_POINTS);
		glVertex2f(P.x, P.y);
	glEnd();
	glFlush();	
}

void DrawCylinder(float R, float h){
	Point P;
	double Delta_U = 0.01 ,Delta_V = 0.03,u,v;

	for (u=0; u<2*M_PI; u+=Delta_U){
		for (v=0; v<1; v+=Delta_V){
			P.x = R*cos(u) ; 
			P.y = R*sin(u) ;
			P.z = v*h; 
			P = transform(P);
			
			drawPoint(P);
		}
	}
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	DrawCylinder(50, 30);
}

int main(int argc, char** argv){
	int mode=GLUT_SINGLE | GLUT_RGB;
	glutInitDisplayMode(mode);
	
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Mat tru");
	 
	initGL();
	glutDisplayFunc(display);    
	glutMainLoop();
}
