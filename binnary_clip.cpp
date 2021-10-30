#include<GL/glut.h>

#include<math.h>

#include<stdio.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

typedef struct Point{
	float x;
	float y;
}Point;

float xmin = -100; // Bien luu toa do 4 dinh hinh chu nhat
float ymin = -100;
float xmax = 200;
float ymax = 150;
Point A, B;
int draw = 1;



void initGL(void) {
  glClearColor(1, 1, 1, 0);
  gluOrtho2D(-300, 300, -300, 300);
}

void swap(Point &A, Point &B){
	Point T = B;
	B = A;
	A = T;
}
// Ve hinh chu nhat va doan thang
void display() {
	  glClear(GL_COLOR_BUFFER_BIT);
	  glColor3f(0.0, 1.0, 0.0);
	  glBegin(GL_LINE_LOOP); 
	  glVertex2i(xmin, ymin);
	  glVertex2i(xmin, ymax);
	  glVertex2i(xmax, ymax);
	  glVertex2i(xmax, ymin);
	  glEnd();
	  
	  if(draw){
	  	//printf("draw :%d", draw);
	  	
	  	glColor3f(1.0, 0.0, 0.0);
	  	glBegin(GL_LINES); 
	  	glVertex2i(A.x, A.y);
	  	glVertex2i(B.x, B.y);
	  	glEnd();
	
	  	glFlush();
	  }
}

void drawLine(Point A, Point B){
	  printf("Ax : %f Ay : %f \n", A.x , A.y);
	  printf("Bx : %f By : %f", B.x , B.y);
	  glColor3f(0.0, 1.0, 0.0);
	  glBegin(GL_LINE_LOOP); 
	  glVertex2i(xmin, ymin);
	  glVertex2i(xmin, ymax);
	  glVertex2i(xmax, ymax);
	  glVertex2i(xmax, ymin);
	  glEnd();
	  
	  if(draw){
	  	//printf("draw :%d", draw);
	  	
	  	glColor3f(1.0, 0.0, 0.0);
	  	glBegin(GL_LINES); 
	  	glVertex2i(A.x, A.y);
	  	glVertex2i(B.x, B.y);
	  	glEnd();
	
	  	glFlush();
	  }
}

int Ma(Point M) //Tinh Code cua diem
{
	  int c = 0;
	  if (M.y > ymax) c = 8;
	  if (M.y < ymin) c = 4;
	  if (M.x > xmax) c = 2;
	  if (M.x < xmin) c = 1;
	  return c;
}

void binnary_Line(Point A, Point B) {
	Point P,Q,M;
	
  	if ((Ma(A) | Ma(B)) == 0) drawLine(A, B);
	if ((Ma(A) & Ma(B)) != 0){
		draw = 0;
		display();
	} 
	if ((Ma(A) != 0) && (Ma(B) == 0)) swap(A, B);
	if ((Ma(A) == 0) && (Ma(B) != 0)){
		Point P = A, Q = B;
		while ((abs(P.x-Q.x)+abs(P.y-Q.y)) > 2){
			M.x=(P.x+Q.x)/2; M.y=(P.y+Q.y)/2;
			if (Ma(M)==0) P=M;
			else Q = M;
		}
		
		drawLine(A, P);
	}
	
	if (((Ma(A) != 0) && (Ma(B) != 0)) && ((Ma(A) & Ma(B))==0)){
		P = A; Q = B;
		M.x = (P.x + Q.x)/ 2; 
		M.y=(P.y + Q.y) / 2;
		while ((Ma(M)!=0) && ((abs(P.x - Q.x) + abs(P.y - Q.y)) > 2)){
			if ((Ma(P) & Ma(M))!=0) P = M;
			else Q = M;
			M.x=(P.x + Q.x)/2; 
			M.y=(P.y + Q.y)/2;
		}
		
		if(Ma(M) == 0){
			//printf("Px : %f Py : %f", P.x , P.y);
			glClear(GL_COLOR_BUFFER_BIT);
			binnary_Line(P,M);
			binnary_Line(M,Q);
		}
	}
}



void mykey(unsigned char key, int x, int y) {
  if (key == 'c') //Nhan phim c de xen (ve lai doan thang)
  {
    binnary_Line(A, B);
    glFlush();
  }
}

int main(int argc, char ** argv) {
  printf("Nhap toa do 2 diem A(xd1,yd1) và B(xd2,yd2):");
  cin >> A.x >> A.y >> B.x >> B.y;
  
  glutInit( & argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(600, 600);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("DEMO XEN DOAN THANG BANG HCN - BINNARY");
  glutDisplayFunc(display);
  glutKeyboardFunc(mykey); //goi ham xu ly xu kien nhan phim
  initGL();
  glutMainLoop();
  return 0;
}
