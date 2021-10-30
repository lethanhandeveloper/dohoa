#include<stdio.h>
#include<GL/glut.h>
#include <stdlib.h>
#include<math.h>

//https://github.com/detel/bezier-curve/blob/master/bezeir-curves.cpp
typedef struct {
	float x; float y ;
}CPoint;

int n = 3;
CPoint P[3];

void initGL()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //R=0,G=0,B=0, anpha=1
	glOrtho(0, 20 , 0 , 20 ,-1,1);	
}


float fact(int n){
	if (n == 0) return 1;
	else return n*fact(n - 1);
}

float BernStein(float t, int k){
	//printf("t value : %f \n", t);
	float ckn,kq;
	ckn = fact(n)/(fact(k)*fact(n - k));
	kq = ckn*pow(1 - t, n - k)*pow(t,k);
	return kq;
}

int factorial(int n)
{
    if (n<=1)
        return(1);
    else
        n=n*factorial(n-1);
    return n;
}

CPoint TPt(float t){
	//printf("t value : %f \n", t);
	CPoint Pt; float B; int k;
	Pt.x=0; Pt.y=0;
	for (k = 0; k <= n; k++){
		B = BernStein(t, k);
		Pt.x = Pt.x + P[k].x*B;
		Pt.y = Pt.y + P[k].y*B;
	}
	return Pt;
}

void drawLine(CPoint A, CPoint B){
	glBegin(GL_LINES);
		//printf("%d :x %d : y \n", beginPoint.x, beginPoint.y);
		glVertex2f(A.x, A.y);
		glVertex2f(B.x, B.y);
	glEnd();
	glFlush();
}

void drawDot(){
	glPointSize(10);
	for(int i = 0; i <= n; i++){
		glBegin(GL_POINTS);
    		glVertex2i(P[i].x, P[i].y);
    	glEnd();
    	glFlush();
	}
	
}

void DrawBezier() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	
	CPoint Pt; float dt,t,m; int i;
	t=0; m= 100;dt=1/m;
	CPoint beginPoint = P[0];
	
	for(i = 0 ; i<= m ; i++){
		Pt=TPt(t);
		t = t + dt;
		drawLine(beginPoint, Pt);
  		beginPoint = Pt;
  		printf("%f :x %f : y \n", beginPoint.x, beginPoint.y);
	}
	
	
	//drawLine(beginPoint, P[n]);
	printf("%f :PNx %f : PNy \n", P[n].x, P[n].y);
	
	drawDot(); 
}

int main(int argc, char** argv){
	P[0].x = 0.0f;  P[0].y = 0.0f;
	P[1].x = 10.0f;  P[1].y = 10.0f;
	//P[2].x = 20.0f;  P[2].y = 20.0f;
	P[3].x = 20.0f;  P[3].y = 0.0f;
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
    glutCreateWindow("Duong cong bezier"); 
	glutDisplayFunc(DrawBezier);
	initGL();
	glutMainLoop();
}
