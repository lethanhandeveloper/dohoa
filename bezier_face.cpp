#include<stdio.h>
#include<GL/glut.h>
#include <stdlib.h>
#include<math.h>

typedef struct {
	float x; float y ; float z;
}CPoint;

int m = 2, n = 2;
CPoint P[3][3];
float theta = 100, phi = 50, D = 6.0f, R = 10.0f;

void initGL()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //R=0,G=0,B=0, anpha=1
	glOrtho(0, 30 , 0 , 30 ,-1,1);	
}

CPoint convert3D(CPoint &p){
	p.x = -p.x * sin(theta) + p.y * cos(theta);
	p.y = -p.x * cos(theta) * sin(phi) 
							-p.y * sin(theta) * sin(phi) + p.z * cos(phi);
							
	p.z = -p.x * cos(theta) * cos(phi) - p.y * sin(theta) * cos(phi)
							- p.z * sin(phi) + R;
	return p;
}


float fact(int n){
	if (n == 0) return 1;
	else return n*fact(n - 1);
}

float BernStein(float t, int n, int k){
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

CPoint TPt(float u, float v){
	//printf("t value : %f \n", t);
	CPoint Pt; float B; int k;
	Pt.x=0; Pt.y=0, Pt.z = 0;
	
	for (int i = 0; i <= m; i++){
		for(int k=0; k<= n; k++){
			B = BernStein(u, m, i) * BernStein(v, n, k);
			Pt.x = Pt.x + P[i][k].x*B;
			Pt.y = Pt.y + P[i][k].y*B;
			Pt.z = Pt.z + P[i][k].z*B;
		}
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

void DrawBezier() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	
	CPoint Pt; 
	float u=0, v = 0, m = 50 , du=1/m, dv = 1/m;
	CPoint beginPoint = P[0][0], Ptc;
	
	beginPoint = convert3D(beginPoint);
	
	
	for(int i =0 ; i<= m ; i++){
		for(int j=0; j<=m ; j++){
			Pt = TPt(u, v);
			Ptc = convert3D(Pt); //chieu 
		
			drawLine(beginPoint, Ptc);
	  		beginPoint = Pt;
	  		u = u + du;
			
	  		//printf("%d \n", i);
	  		printf("%f :x %f : y \n", beginPoint.x, beginPoint.y);
		}
		
		v = v + dv;	
	}
}

int main(int argc, char** argv){
	//khoi tao cac diem 3d
	//P = {{10, 10, 10}, {15, 20, 10}, {20, 6, 10}, {}, {}, {}, {}, {}, {}};
	P[0][0].x = 10;  P[0][0].y = 10;  P[0][0].z = 10;  
	P[0][1].x = 15;  P[0][1].y = 20;  P[0][1].z = 10; 
	P[0][2].x = 20;  P[0][2].y = 6;  P[0][2].z = 10; 
	
	P[1][0].x = 10;  P[1][0].y = 10;  P[1][0].z = 15;  
	P[1][1].x = 15;  P[1][1].y = 20;  P[1][1].z = 15; 
	P[1][2].x = 20;  P[1][2].y = 6;  P[1][2].z = 15; 
	
	P[2][0].x = 10;  P[2][0].y = 10;  P[2][0].z = 20;  
	P[2][1].x = 15;  P[2][1].y = 20;  P[2][1].z = 20; 
	P[2][2].x = 20;  P[2][2].y = 6;  P[2][2].z = 20; 
	
	/*P[0].x = 10;  P[0].y = 10;  P[0].z = 10;  
	P[1].x = 15;  P[1].y = 20;  P[1].z = 10; 
	P[2].x = 20;  P[2].y = 6;  P[2].z = 10; 
	
	P[3].x = 10;  P[3].y = 10;  P[3].z = 15;  
	P[4].x = 15;  P[4].y = 20;  P[4].z = 15; 
	P[5].x = 20;  P[5].y = 6;  P[5].z = 15; 
	
	P[6].x = 10;  P[6].y = 10;  P[6].z = 20;  
	P[7].x = 15;  P[7].y = 20;  P[7].z = 20; 
	P[8].x = 20;  P[8].y = 6;  P[8].z = 20; */
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
    glutCreateWindow("Mat cong bezier"); 
	glutDisplayFunc(DrawBezier);
	initGL();
	glutMainLoop();
}
