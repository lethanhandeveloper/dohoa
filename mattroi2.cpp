#include <cstdlib>
#include <ctime>
#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <stdio.h>
#include<math.h>

int speed=0;
using namespace std;
//Kim
float xkim=80,ykim=50;
int  speedkim = 4+speed;
bool kim=false;

//Thuy
float xthuy=120,ythuy=80;
int  speedthuy = 5+speed;
bool thuy=false;


//Trai dat
float xtd=180,ytd=0;
int  speedtd = 5+speed;
bool td=false;

//Sao hoa
float xhoa=220,yhoa=150;
int  speedhoa = 5+speed;
bool hoa=false;

//Sao moc
float xmoc=310,ymoc=220;
int  speedmoc = 5+speed;
bool moc=false;

//Sao tho
float xtho=360,ytho=270;
int  speedtho = 5;
bool tho=false+speed;

// thien vuong
float xtv=400,ytv=380;
int  speedtv = 5+speed;
bool tv=false;

//Sao hai vuong
float xhv=500,yhv=460;
int  speedhv = 5+speed;
bool hv=false;



void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); /* thay doi viewport */
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-600.0, 600.0, -600.0, 600.0, -600.0, 600.0);
   
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void put4pixel(int xc, int yc, int x, int y)
{
   glBegin(GL_POINTS);
	   glVertex2i(xc+x,yc+y);
	   glVertex2i(xc-x,yc+y);
	   glVertex2i(xc+x,yc-y);
	   glVertex2i(xc-x,yc-y);
   glEnd();
   glFlush();
}


void midpoint_ellipse(int xc,int yc,int a,int b)
{
   	int x,y; float x0,y0,a2,b2,p;
	a2=a*a; b2=b*b;
	x0=(int)(a2/sqrt(a2+b2)); y0=(int)(b2/sqrt(a2+b2));
	p=b2-a2*b+(1/4)*a2; x=0; y=b;
	while (x<=x0){
		put4pixel(xc,yc,x,y);
		if (p<0) p+=(2*x+3)*b2;
		else{ p+=(2*x+3)*b2-2*a2*(y-1);
			y--;
		}
		x++;
	}
	
	x=a; y=0; p=a2-a*b2+(1/4)*b2;
	while (y<=y0){
		put4pixel(xc,yc,x,y);
		if (p<0)
			p+=a2*(2*y+3);
		else{
			p+=(2*y+3)*a2-2*b2*(x-1);
			x--;
		}
		y++;
	}
}

void Ellipse_Bresenham(int xc, int yc, int a, int b) { 
   	double x,y,p,x0, y0,a2,b2;
	a2=a*a; b2=b*b;
	x=0; y=b; p=-2*b+1+2*b2/(a2);
	x0=a2/(sqrt(a2+b2)); y0=b2/(sqrt(a2+b2));
	
	while (x<=x0){
		put4pixel(xc,yc, x, y);
		if (p<0) p+=2*b2*(2*x+3)/a2;
		else{
			p+=4*(1-y)+ 2*b2 * (2*x+3)/a2;
			y--;
		} 
		
		x++;
	} 
	
	x=a; y=0; p=2*a2/b2 - 2*a+1;
	while (y<=y0){
		put4pixel(xc,yc, x, y);
		if (p<0 ) p+=2*a2*(2*y+3)/b2;
		else{
			p+=4*(1-x) + 2*a2*(2*y+3)/b2;
			x--;
		}
		
		y++;
	}
}

void HinhTron(int tamx, int tamy, int bk)
{
   int i=bk;
   glPointSize(2);
   
   while(i>0)
   {
   		midpoint_ellipse(tamx,tamy,i,i);
   		i--;
   }
}

// quan trong

void Display(void)
{
   
   glClear(GL_COLOR_BUFFER_BIT);
   glPushMatrix();
   glPointSize(20);
   
   
   // Mat troi
   glColor3f(1,0,0);
   HinhTron(0,0,30);

   glPointSize(3);
   // sao Thuy
   

   glColor3f(1,1,1);
         
   Ellipse_Bresenham(0,0,80,50); //quy dao

   

   glColor3f(1,0.5,0);
   
   

   HinhTron(xkim,ykim,4);  // hanh tinh
   
   

   // sao  Kim
   

   glColor3f(1,1,1);

   Ellipse_Bresenham(0,0,120,80); //quy dao



   glColor3f(0.086,0.588,0.753);



   HinhTron(xthuy,ythuy,5);  // hanh tinh


   // Trai dat

   glColor3f(1,1,1);

   Ellipse_Bresenham(0,0,180,100); //quy dao



   glColor3f( 0.204,0.337,0.961);



   HinhTron(xtd,ytd,7);  // hanh tinh

   
   // sao Hoa


   glColor3f(1,1,1);

   Ellipse_Bresenham(0,0,220,150); //quy dao



   glColor3f(1,0.1,0);



   HinhTron(xhoa,yhoa,7);  // hanh tinh
   

   //Sao Moc

   glColor3f(1,1,1);

   Ellipse_Bresenham(0,0,310,220); //quy dao



   glColor3f(1,0.4,0);



   HinhTron(xmoc,ymoc,12);  // hanh tinh

   //Sao Tho

   glColor3f(1,1,1);

   Ellipse_Bresenham(0,0,360,260); //quy dao



   glColor3f(0.753,0.753,0.753);



   HinhTron(xtho,ytho,12);  // hanh tinh


   // thien vuong

   glColor3f(1,1,1);

   Ellipse_Bresenham(0,0,400,390); //quy dao



   glColor3f(1,1,0);



   HinhTron(xtv,ytv,12);  // hanh tinh



   // hai vuong

   glColor3f(1,1,1);

   Ellipse_Bresenham(0,0,500,490); //quy dao



   glColor3f(1,0.6,0.3);



   HinhTron(xhv,yhv,12);  // hanh tinh

   glPopMatrix();
   glutSwapBuffers();
}




void ReDisplay(int ms)
{

   //Sao kim

   float z= float(80*80/(50*50));
   
   if(kim)
   {
      ykim+=speedkim;
      xkim=int(sqrt(80*80-ykim*ykim*z));
      if(ykim>50 )kim=!kim;
   }
   
   if(!kim)
   {
      ykim-=speedkim;
      xkim=-int(sqrt(80*80-ykim*ykim*z));
      if(ykim<-50)
         kim=!kim;
   }
   
   
   //Sao thuy

   float zthuy= float(120*120/(80*80));
   if(thuy)
   {
      ythuy+=speedthuy;
      xthuy=int(sqrt(120*120-ythuy*ythuy*z));
      if(ythuy>80 )
         thuy=!thuy;
   }
   
   if(!thuy)
   {
      ythuy-=speedthuy;
      xthuy=-int(sqrt(120*120-ythuy*ythuy*z));
      if(ythuy<-80)
         thuy=!thuy;
   }

   //Trai dat
   float ztd= float(180*180/(100*100));
   if(td)
   {
      ytd+=speedtd;
      xtd=int(sqrt(180*180-ytd*ytd*ztd));
      if(ytd>100 )
         td=!td;
   }
   if(!td)
   {
      ytd-=speedtd;
      xtd=-int(sqrt(180*180-ytd*ytd*ztd));
      if(ytd<-100)
         td=!td;
   }

   //Sao hoa

   float zhoa= float(220*220/(130*130));
   if(hoa)
   {
      yhoa+=speedhoa;
      xhoa=int(sqrt(220*220-yhoa*yhoa*zhoa));
      if(yhoa>130 )
         hoa=!hoa;
   }
   if(!hoa)
   {
      yhoa-=speedhoa;
      xhoa=-int(sqrt(220*220-yhoa*yhoa*zhoa));
      if(yhoa<-130)
         hoa=!hoa;
   }

   //Sao Moc

   float zmoc= float(310*310/(200*200));
   if(moc)
   {
      ymoc+=speedmoc;
      xmoc=int(sqrt(310*310-ymoc*ymoc*zmoc));
      if(ymoc>220 )
         moc=!moc;
   }
   if(!moc)
   {
      ymoc-=speedmoc;
      xmoc=-int(sqrt(310*310-ymoc*ymoc*zmoc));
      if(ymoc<-220)
         moc=!moc;
   }
   


   //Sao Tho

   float ztho= float(360*360/(240*240));
   if(tho)
   {
      ytho+=speedtho;
      xtho=int(sqrt(360*360-ytho*ytho*ztho));
      if(ytho>270 )
         tho=!tho;
   }
   if(!tho)
   {
      ytho-=speedtho;
      xtho=-int(sqrt(360*360-ytho*ytho*ztho));
      if(ytho<-270)
         tho=!tho;
   }


   //Sao Thien vuong

   float ztv= float(400*400/(283*283));
   if(tv)
   {
      ytv+=speedtv;
      xtv=int(sqrt(400*400-ytv*ytv*ztv));
      if(ytv>299 )
         tv=!tv;
   }
   if(!tv)
   {
      ytv-=speedtv;
      xtv=-int(sqrt(400*400-ytv*ytv*ztv));
      if(ytv<-299)
         tv=!tv;
   }
   
   //Sao Hai vuong

   float zhv= float(480*480/(450*450));
   if(hv){
      yhv+=speedhv;
      xhv=int(sqrt(500*500-yhv*yhv*zhv));
      if(yhv>460 )
         hv=!hv;
   }
   if(!hv)
   {
      yhv-=speedhv;
      xhv=-int(sqrt(500*500-yhv*yhv*zhv));
      if(yhv<-460)
         hv=!hv;
   }
   
   glutPostRedisplay();
   glutTimerFunc(ms,ReDisplay,ms);

}



int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (1300, 700);
   glutInitWindowPosition (0,0);
   glutCreateWindow ("He Mat Troi");
   init();
   glPointSize(5);
   glutDisplayFunc(Display);
   glutReshapeFunc(reshape);
   ReDisplay(1);
   
   glutMainLoop();
   return 0;
}
