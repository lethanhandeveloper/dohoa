#include <GL/glut.h>
void initGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	//glOrtho(-2,2,-2,2,-1,1);	
}
void mydisplay()
{
  	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f); 
	//glViewport(0,0,400,400);
	
	glBegin(GL_POLYGON);
    		glVertex2f(-0.5f, -0.5f);  
    		glVertex2f( 0.5f, -0.5f);
    		glVertex2f( 0.5f,  0.5f);
    		glVertex2f(-0.5f,  0.5f);
 	glEnd();	
  	glFlush();
}
int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
    glutCreateWindow("Hinh vuong");  
	glutDisplayFunc(mydisplay);
	initGL();
	glutMainLoop();
}
