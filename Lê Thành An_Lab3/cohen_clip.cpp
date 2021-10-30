#include<GL/glut.h>

#include<math.h>

#include<stdio.h>

#include<iostream>

using namespace std;
float xmin = -100; // Bien luu toa do 4 dinh hinh chu nhat
float ymin = -100;
float xmax = 200;
float ymax = 150;
float xA, yA, xB, yB; // Bien luu toa do diem A và B
int draw = 1;

void initGL(void) {
  glClearColor(1, 1, 1, 0);
  gluOrtho2D(-300, 300, -300, 300);
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
	  	glVertex2i(xA, yA);
	  	glVertex2i(xB, yB);
	  	glEnd();
	
	  	glFlush();
	  }
}


int code(float x, float y) //Tinh Code cua diem
{
	  int c = 0;
	  if (y > ymax) c = 8;
	  if (y < ymin) c = 4;
	  if (x > xmax) c = 2;
	  if (x < xmin) c = 1;
	  return c;
}

void cohen_Line(float &xA, float &yA, float &xB, float &yB) {
  	int cA = code(xA, yA); // Code cua diem A
  	int cB = code(xB, yB); // Code cua diem B
  	int escape = 0;
  	double m;
  	
	while(escape == 0){
		if((code(xA, yA) | code(xB, yB)) == 0){
			escape = 1;
		} 
		else if((code(xA, yA) & code(xB, yB)) != 0){
			escape = 1;
			draw = 0 ;
		}else{
			
			if(code(xA, yA) == 0){
				float temp;
				temp = xB;
				xB = xA;
				xA = temp;
				
				temp = yB;
				yB = yA;
				yA = temp;
			}
			if(xA == xB){
				if(yA > ymax) yA = ymax;
				else yA = ymin;
			}else{
				//printf("xA:%f yA:%f xB:%f yB:%f----", xA, yA, xB, yB);
				//printf("xMin:%f yMin:%f xMax:%f yMax:%f----", xmin, ymin, xmax, ymax);
				
				m=(double) (yB - yA)/(xB - xA);
				if (xA < xmin)
				{ 
					
					yA = yA + (xmin - xA ) * m; 
					xA = xmin; 
					//printf("xA : %f", xA);
				}
				else if (xA > xmax){
				 	yA = yA + (xmax - xA)*m; 
					xA = xmax; 
				}
				else if (yA < ymin) { 
					xA = xA + (ymin - yA) / m; 
					yA= ymin; 
				}
				else if (yA > ymax){
				 	xA = xA + (ymax - yA)/m; 
					yA= ymax; 
				}
			}
		}
	}
	
	//printf("xA:%f yA:%f xB:%f yB:%f----", xA, yA, xB, yB);
	
	display();
}



void mykey(unsigned char key, int x, int y) {
  if (key == 'c') //Nhan phim c de xen (ve lai doan thang)
  {
    cohen_Line(xA, yA, xB, yB);
    glFlush();
  }
}

int main(int argc, char ** argv) {
  printf("Nhap toa do 2 diem A(xd1,yd1) và B(xd2,yd2):");
  cin >> xA >> yA >> xB >> yB;
  glutInit( & argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(600, 600);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("DEMO XET DOAN THANG BANG HCN - Cohen - Sutherland");
  glutDisplayFunc(display);
  glutKeyboardFunc(mykey); //goi ham xu ly xu kien nhan phim
  initGL();
  glutMainLoop();
  return 0;
}
