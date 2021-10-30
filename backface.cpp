#include<GL/Glut.h> 
#include <math.h>
#include<stdio.h>
#define MAX 20

void initGL()
{
	glClearColor(1, 1, 1, 0);
  	gluOrtho2D(-3, 3, -3, 3);
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


float theta = 200*180/M_PI, phi = 10*180/M_PI, D = 10.0f, R = 1.0f;


void showWF(){
	for(int i = 0 ; i < wf.numFace; i++){
		for(int j = 0; j < wf.face[i].nFace; j++){
			printf("%f - %f - %f  \n", wf.vertex[wf.face[i].indexFace[j]].x, 
			wf.vertex[wf.face[i].indexFace[j]].y, wf.vertex[wf.face[i].indexFace[j]].z);
		}
		
		printf("\n");
			
	}
}

void createPolygon(){
	wf.numVertex = 5;
	wf.numFace = 5;
	
	//create vertex list
	wf.vertex[0].x = 1.0f;
	wf.vertex[0].y = 0.0f;	
	wf.vertex[0].z = 0.0f;	
	
	wf.vertex[1].x = 0.0f;
	wf.vertex[1].y = 0.0f;	
	wf.vertex[1].z = -1.0f;	
	
	wf.vertex[2].x = -1.0f;
	wf.vertex[2].y = 0.0f;	
	wf.vertex[2].z = 0.0f;	
	
	wf.vertex[3].x = 0.0f;
	wf.vertex[3].y = 0.0f;	
	wf.vertex[3].z = 1.0f;	
	
	wf.vertex[4].x = 0.0f;
	wf.vertex[4].y = 1.0f;	
	wf.vertex[4].z = 0.0f;	
	
	//A : 0 B: 1 C : 2 , D :3 , E : 4	
		
	// mat AED
	wf.face[0].nFace = 3;
	
	wf.face[0].indexFace[0] = 0;
	wf.face[0].indexFace[1] = 4;
	wf.face[0].indexFace[2] = 3;
	//ABE
	wf.face[1].nFace = 3;
	
	wf.face[1].indexFace[0] = 0;
	wf.face[1].indexFace[1] = 1;
	wf.face[1].indexFace[2] = 4;
	
	//mat CEB
	wf.face[2].nFace = 3;
	
	wf.face[2].indexFace[0] = 2;
	wf.face[2].indexFace[1] = 4;
	wf.face[2].indexFace[2] = 1;
	
	//mat CDE
	wf.face[3].nFace = 3;
	
	wf.face[3].indexFace[0] = 2;
	wf.face[3].indexFace[1] = 3;
	wf.face[3].indexFace[2] = 4;
	//mat ADCB
	wf.face[4].nFace = 4;
	
	wf.face[4].indexFace[0] = 0;
	wf.face[4].indexFace[1] = 3;
	wf.face[4].indexFace[2] = 2;
	wf.face[4].indexFace[3] = 1;
	
	//showWF();
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

void removeFace(int indexFace){
	for(int i = indexFace ; i < wf.numFace -1 ; i++){
		wf.face[i] = wf.face[i+1];	
	}
	
	wf.numFace--;
}

void backface(){
	Point normalvector;
	Point viewvector = {5, 5, 5};
	Point vector1, vector2;
	
	int removeFaces[100], indexRemoveFaces = 0, totalRemoveFaces = 0;
	for(int i = 0 ; i < wf.numFace; i++){
		//vector 1
		vector1.x = wf.vertex[wf.face[i].indexFace[1]].x - wf.vertex[wf.face[i].indexFace[0]].x; 
		vector1.y = wf.vertex[wf.face[i].indexFace[1]].y - wf.vertex[wf.face[i].indexFace[0]].y;
		vector1.z = wf.vertex[wf.face[i].indexFace[1]].z - wf.vertex[wf.face[i].indexFace[0]].z;
		//vector 2 
		vector2.x = wf.vertex[wf.face[i].indexFace[2]].x - wf.vertex[wf.face[i].indexFace[0]].x; 
		vector2.y = wf.vertex[wf.face[i].indexFace[2]].y - wf.vertex[wf.face[i].indexFace[0]].y;
		vector2.z = wf.vertex[wf.face[i].indexFace[2]].z - wf.vertex[wf.face[i].indexFace[0]].z;
		
		// toa do vector phap tuyen
		normalvector.x = vector1.y * vector2.z - vector2.y * vector1.z;
		normalvector.y = -(vector1.x * vector2.z - vector2.x * vector1.z);
		normalvector.z = vector1.x * vector2.y - vector2.x * vector1.y;
		
		//printf("Normal vector X %f Y %f Z %f\n", normalvector.x, normalvector.y, normalvector.z);
		float result = normalvector.x * viewvector.x + normalvector.y * viewvector.y 
						+ normalvector.z * viewvector.z;
		
		
		//printf("Vector 1 X : %f Y : %f Z %f\n", vector1.x, vector1.y, vector1.z);
		if(result < 0){
			printf("Mat so %i co ket qua %f", i, result);
			//printf("%f \n", result);
			totalRemoveFaces++;
			removeFaces[indexRemoveFaces++] = i;
		}
		
	}
	
	if(totalRemoveFaces > 0){
		
		for(int i = 0; i < totalRemoveFaces; i++){
			printf("REMOVE : %d", removeFaces[i]);
			removeFace(removeFaces[i]);
		}
	}
}

void Display()
{
	printf("có %d mat", wf.numFace);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	//printf("So mat %d", wf.numFace);
	for(int i = 0 ; i < wf.numFace ; i++){
		glBegin(GL_LINE_LOOP);
		for(int j = 0; j < wf.face[i].nFace ; j++){
			//printf("X :%f Y : %f \n", wf.vertex[wf.face[i].indexFace[j]].x, wf.vertex[wf.face[i].indexFace[j]].y);
			glVertex2f(wf.vertex[wf.face[i].indexFace[j]].x, wf.vertex[wf.face[i].indexFace[j]].y);
		}
		
		//printf("\n");
		glEnd();
		glFlush();
			
	}
	
	Point O, E;
	O.x = 0, E.y = 0, E.z =0;
	E.x = 5 , E.y = 5, E.z=5;
	
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
		glVertex2f(0.0 , 0.0);
		glVertex2f(5.0 , 5.0);
	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{
	createPolygon();
	//oblique_projection();
	backface();
	transform();
	
	showWF();
	glutInit(&argc, argv);
	glutInitWindowSize(640, 640);    
	glutInitWindowPosition(100, 50); 
	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutCreateWindow("Thuat toan back - face"); 
    initGL();
    
    printf("-------------------");
    showWF();
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

