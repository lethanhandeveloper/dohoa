#include<GL/Glut.h> 
#include <math.h>
#include<stdio.h>
#define MAX 20

void initGL()
{
	glClearColor(1, 1, 1, 0);
  	gluOrtho2D(-7, 7, -7, 7);
}

typedef struct{
	float x; float y; float z;
}Point;

typedef struct{
	int nFace;
	int indexFace[MAX];
}FaceType;

typedef struct{
	int numVertex, numFace;
	Point vertex[MAX];
	FaceType face[MAX];
}FaceModel;

FaceModel wf, wf1;


float theta = 150*180/M_PI, phi = 10*180/M_PI, D = 10.0f, R = 1.0f;
void createPolygon(){
	wf.numVertex = 8;
	wf.numFace = 6;
	
	//create vertex list
	wf.vertex[0].x = 1.0f;
	wf.vertex[0].y = 1.0f;	
	wf.vertex[0].z = -3.0f;	
	
	wf.vertex[1].x = -1.0f;
	wf.vertex[1].y = 1.0f;	
	wf.vertex[1].z = -3.0f;	
	
	wf.vertex[2].x = -1.0f;
	wf.vertex[2].y = -1.0f;	
	wf.vertex[2].z = -3.0f;	
	
	wf.vertex[3].x = 1.0f;
	wf.vertex[3].y = -1.0f;	
	wf.vertex[3].z = -3.0f;	
	
	wf.vertex[4].x = 1.0f;
	wf.vertex[4].y = 1.0f;	
	wf.vertex[4].z = 0.0f;	
	
	wf.vertex[5].x = -1.0f;
	wf.vertex[5].y = 1.0f;	
	wf.vertex[5].z = 0.0f;	
	
	wf.vertex[6].x = -1.0f;
	wf.vertex[6].y = -1.0f;	
	wf.vertex[6].z = 0.0f;	
	
	wf.vertex[7].x = 1.0f;
	wf.vertex[7].y = -1.0f;	
	wf.vertex[7].z = 0.0f;	
	
	// mat 1 
	wf.face[0].nFace = wf.face[1].nFace = wf.face[2].nFace = wf.face[3].nFace = 4; // so dinh 1 mat
	
	wf.face[0].indexFace[0] = 0;
	wf.face[0].indexFace[1] = 4;
	wf.face[0].indexFace[2] = 7;
	wf.face[0].indexFace[3] = 3;
	//mat 2

	wf.face[1].indexFace[0] = 0;
	wf.face[1].indexFace[1] = 1;
	wf.face[1].indexFace[2] = 5;
	wf.face[1].indexFace[3] = 4;
	
	//mat 3
	wf.face[2].indexFace[0] = 1;
	wf.face[2].indexFace[1] = 2;
	wf.face[2].indexFace[2] = 6;
	wf.face[2].indexFace[3] = 5;
	
	//mat 4
	wf.face[3].indexFace[0] = 2;
	wf.face[3].indexFace[1] = 3;
	wf.face[3].indexFace[2] = 7;
	wf.face[3].indexFace[3] = 6;
	//mat 5
	
	wf1 = wf;
}

Point convert3D(Point &p){	
	p.x = -p.x * sin(theta) + p.y * cos(theta);
	p.y = -p.x * cos(theta) * sin(phi) 
							-p.y * sin(theta) * sin(phi) + p.z * cos(phi);
							
	p.z = -p.x * cos(theta) * cos(phi) - p.y * sin(theta) * cos(phi)
							- p.z * sin(phi) + R;
	return p;
}

void transform(){
	for(int i = 0 ; i < wf.numFace; i++){
		for(int j = 0; j < wf.face[i].nFace; j++){	
			wf.vertex[wf.face[i].indexFace[j]] = convert3D(wf.vertex[wf.face[i].indexFace[j]]);
		}
	}
}

void showWF(){
	for(int i = 0 ; i < wf.numFace; i++){
			for(int j = 0; j < wf.face[i].nFace; j++){
				printf("%f %f %f - ", wf.vertex[wf.face[i].indexFace[j]].x, 
				wf.vertex[wf.face[i].indexFace[j]].y, wf.vertex[wf.face[i].indexFace[j]].z);
			}
			
			printf("\n");
	}
}

void removeFace(int indexFace){
	for(int i = indexFace ; i < wf.numFace -1 ; i++){
		wf.face[i] = wf.face[i+1];	
	}
	wf.numFace -= 1;
}

void backface(){
	//phai chieu ra toa do vector huong nhin
	Point normalvector;
	Point viewvector = {5, 5, 5};
	Point vector1, vector2;
	viewvector = convert3D(viewvector);
	
	for(int i = 0 ; i < wf.numFace; i++){
		//vector 1
		vector1.x = wf.vertex[wf.face[i].indexFace[1]].x - wf.vertex[wf.face[i].indexFace[0]].x; 
		vector1.y = wf.vertex[wf.face[i].indexFace[1]].x - wf.vertex[wf.face[i].indexFace[0]].y;
		vector1.z = wf.vertex[wf.face[i].indexFace[1]].z - wf.vertex[wf.face[i].indexFace[0]].z;
		//vector 2 
		vector2.x = wf.vertex[wf.face[i].indexFace[2]].x - wf.vertex[wf.face[i].indexFace[0]].x; 
		vector2.y = wf.vertex[wf.face[i].indexFace[2]].x - wf.vertex[wf.face[i].indexFace[0]].y;
		vector2.z = wf.vertex[wf.face[i].indexFace[2]].x - wf.vertex[wf.face[i].indexFace[0]].y;
		
		// toa do vector phap tuyen
		normalvector.x = vector1.y * vector2.z - vector2.y * vector1.z;
		normalvector.y = -(vector1.x * vector2.z - vector2.x * vector1.z);
		normalvector.z = vector1.x * vector2.y - vector2.y * vector1.y;
		
		float result = normalvector.x * viewvector.x + normalvector.y * viewvector.y 
						+ normalvector.z * viewvector.z;
		
		if(result < 0){
			removeFace(i);
		}
		
	}
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	printf("So mat %d", wf.numFace);
	for(int i = 0 ; i < wf.numFace; i++){
		printf("%d \n", i);
		glBegin(GL_LINE_LOOP);
		for(int j = 0; j < wf.face[i].nFace ; j++){
			glVertex2f(wf.vertex[wf.face[i].indexFace[j]].x, wf.vertex[wf.face[i].indexFace[j]].y);
		}
		//printf("%0.1f - %0.1f", wf.vertex[wf.edge[i].beginP].x , wf.vertex[wf.edge[i].beginP].y);
		glEnd();
		glFlush();
		
	}
	
	Point O, E;
	O.x = 0, E.y = 0, E.z =0;
	E.x = 5 , E.y = 5, E.z=5;
	
	
	/*glBegin(GL_LINES);
		glVertex2f(0.0 , 0.0);
		glVertex2f(5.0 , 5.0);
	glEnd();
	glFlush();*/
}

void printfdkdkdk(){
	printf("oke");
}
int main(int argc, char** argv)
{
	createPolygon();
	//oblique_projection();
	transform();
	//showWF();
	glutInit(&argc, argv);
	glutInitWindowSize(640, 640);    
	glutInitWindowPosition(100, 50); 
	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutCreateWindow("Bien doi 3d - Mo hinh mat da giac"); 
    initGL();
    
	glutDisplayFunc(Display);
	//glutSpecialFunc(keypressSpecial);
	
	//chuot phai
	/*glutCreateMenu(MENU_EVENT);
	glutAddMenuEntry("Chieu song song", 1);
	glutAddMenuEntry("Chieu phoi canh", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutKeyboardFunc(keyPressed);  */
	glutMainLoop(); 
}

