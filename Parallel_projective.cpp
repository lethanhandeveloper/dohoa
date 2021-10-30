#include<GL/Glut.h> 
#include <math.h>
#include<stdio.h>

void initGL()
{
	glClearColor(1, 1, 1, 0);
  	gluOrtho2D(-10, 10, -10, 10);
}

typedef struct{
	float x; float y; float z;
}Point;

typedef struct{
	int beginP;
	int endP;
}EdgeType;

typedef struct{
	int numVertex, numEdge;
	Point vertex[100];
	EdgeType edge[100];
}WireFrame;

WireFrame wf, wf1;
float alpha_degree = 20.0f, phi_degree = 30.0f, R = 10.0f;

float theta = 30, phi = 30, D = 6.0f;
int flag = 1; // bien nhan biet phep chieu

void createWireFrame(){
	wf.numVertex = 8;
	wf.numEdge = 12;
	
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
	
	//create edge list
	wf.edge[0].beginP = 0;
	wf.edge[0].endP = 1;
	
	wf.edge[1].beginP = 1;
	wf.edge[1].endP = 2;
	
	wf.edge[2].beginP = 2;
	wf.edge[2].endP = 3;
	
	wf.edge[3].beginP = 3;
	wf.edge[3].endP = 0;
	
	wf.edge[4].beginP = 4;
	wf.edge[4].endP = 5;
	
	wf.edge[5].beginP = 5;
	wf.edge[5].endP = 6;
	
	wf.edge[6].beginP = 6;
	wf.edge[6].endP = 7;
	
	wf.edge[7].beginP = 7;
	wf.edge[7].endP = 4;
	
	wf.edge[8].beginP = 0;
	wf.edge[8].endP = 4;
	
	wf.edge[9].beginP = 1;
	wf.edge[9].endP = 5;
	
	wf.edge[10].beginP = 2;
	wf.edge[10].endP = 6;
	
	wf.edge[11].beginP = 3;
	wf.edge[11].endP = 7;
	
	wf1 = wf;
}

void transform(){
	wf = wf1;
	
	//theta = theta * M_PI / 180;
	//phi = phi * M_PI / 180;
	
	for(int i = 0 ; i < wf.numVertex; i++){
		wf.vertex[i].x = -wf.vertex[i].x * sin(theta) + wf.vertex[i].y * cos(theta);
		wf.vertex[i].y = -wf.vertex[i].x * cos(theta) * sin(phi) 
							-wf.vertex[i].y * sin(theta) * sin(phi) + wf.vertex[i].z * cos(phi);
							
		wf.vertex[i].z = -wf.vertex[i].x * cos(theta) * cos(phi) - wf.vertex[i].y * sin(theta) * cos(phi)
							- wf.vertex[i].z * sin(phi) + R;
	}
	
	if(flag == 2){
		for(int i = 0 ; i < wf.numVertex; i++){
			wf.vertex[i].x = wf.vertex[i].x * D / wf.vertex[i].z;
			wf.vertex[i].y = wf.vertex[i].y * D / wf.vertex[i].z;
		}
	}
}


void ortho_projection(WireFrame &wf){
	for(int i = 0 ; i < wf.numVertex; i++){
		wf.vertex[i].z = 0;
	}
}

void oblique_projection(){
	float alpha = alpha_degree*M_PI/180;
	float phi = phi_degree*M_PI/180;
	
	printf("alpha %f phi %1f \n", alpha_degree, phi_degree);
	
	for(int i = 0 ; i < wf.numVertex; i++){
		float P1Q =  wf.vertex[i].z / tan(alpha);
		float Xvalue = P1Q * sin(phi);
		wf.vertex[i].x += Xvalue;
		
		float Yvalue = sqrt(pow(P1Q,2) - pow(Xvalue,2));
		wf.vertex[i].y += Yvalue;
		printf("Do doi x, y %0.1f %0.1f\n" , Xvalue, Yvalue);
		wf.vertex[i].z = 0;
	}
	
}

void changetheta_phi(float value){
	theta += value;
	phi += value;
}

//thay doi diem nhin
void changeR(int value){
	R += value;
}

//phong to, thu nho
void changeD(int value){
	D += value;
	printf("%f \n", D);
}


void showWF(){
	for(int i = 0 ; i < wf.numVertex; i++){
		printf("%0.1f - %0.1f - %0.1f \n", wf.vertex[i].x, wf.vertex[i].y, wf.vertex[i].z);
	}
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	
	for(int i = 0 ; i < wf.numEdge; i++){
		glBegin(GL_LINES);
		//printf("%0.1f - %0.1f", wf.vertex[wf.edge[i].beginP].x , wf.vertex[wf.edge[i].beginP].y);
		glVertex2f(wf.vertex[wf.edge[i].beginP].x , wf.vertex[wf.edge[i].beginP].y);
		glVertex2f(wf.vertex[wf.edge[i].endP].x , wf.vertex[wf.edge[i].endP].y);
		glEnd();
  		glFlush();
	}
}

// su kien xoay, phong to, thu nho
void keypressSpecial(int key, int x, int y)
{
	//xoay
	if (key == GLUT_KEY_UP) {
		changetheta_phi(0.1f);
		transform();
		Display();
	}    
	//xoay
	if (key == GLUT_KEY_DOWN) {
		changetheta_phi(-1.0f);
		transform();
		Display();
	} 
	
	//phong to
	if (key == GLUT_KEY_RIGHT){
		changeD(1.0f);
		transform();
		Display();
	}
	
	//thu nho
	if (key == GLUT_KEY_LEFT){
		changeD(-1.0f);
		transform();
		Display();
	}
}

// su kien thay doi phep chieu
void MENU_EVENT(int id){
	if (id == 1){
		flag = 1;
		transform();
		Display();
	}
	else if (id == 2){
		flag = 2;
		transform();
		Display();
	}
		
}

int main(int argc, char** argv)
{
	createWireFrame();
	//oblique_projection();
	transform();
	showWF();
	glutInit(&argc, argv);
	glutInitWindowSize(640, 640);    
	glutInitWindowPosition(100, 50); 
	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutCreateWindow("Bien doi 3d"); 
    initGL();
	glutDisplayFunc(Display);
	glutSpecialFunc(keypressSpecial);
	
	//chuot phai
	glutCreateMenu(MENU_EVENT);
	glutAddMenuEntry("Chieu song song", 1);
	glutAddMenuEntry("Chieu phoi canh", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop(); 
}

