#include <GL/glut.h>
#include <math.h>

typedef struct{
	float x; float y; float z;
}Point;

float theta = 250, phi = 50, D = 6.0f, R = 10.0f;

void initGL()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //R=0,G=0,B=0, anpha=1
	glOrtho(-200, 200,-200,200,-1,1);	
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

void DrawEllipsoid(float R){
	Point P;
	double Delta_U,Delta_V,u,v;
	Delta_U = 0.09; Delta_V = 0.09;
	
	for (u=0; u<2*M_PI ;u+=Delta_U){
		for (v=-M_PI/2 ; v<M_PI/2; v+=Delta_V){
			P.x = R*cos(u)*cos(v); 
			P.y = R*sin(u)*cos(v);
			P.z = R*sin(v); 
			P = transform(P);
			
			drawPoint(P);
		}
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	DrawEllipsoid(50);
}

int main(int argc, char** argv){
	int mode=GLUT_SINGLE | GLUT_RGB;
	glutInitDisplayMode(mode);
	
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Mat Ellipsoid");
	 
	initGL();
	glutDisplayFunc(display);    
	glutMainLoop();
}
