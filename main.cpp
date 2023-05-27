#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include <windows.h>
#include <GL/glut.h>
#include<vector>
using namespace std;
#define pi (2*acos(0.0))

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;
double map_angle;
double Block_size=40;
double Block_distance=38,size_cube=38;
int slices_spehere=30, stacks_spehere=30;
int segments_cylinder=24;
double temp=0;
double move_pos=2;
double ar=0;
double car=0;
double X=10,Y=40,Z=10;
double leftRightMove=0;
double sky=-1000;
std::string text = "Hello, OpenGL!";
vector< pair<int,pair<int,int> > > CARS;
int NumberOfCar;
struct point
{
	double x,y,z;
};
point l,u,r,pos;
void drive(){
	for(int i=200;i<=40000;i+=200)
	{
        int I = rand()%1000;
        int J = rand()%30;
        int K = rand()%2;
		CARS.push_back( make_pair(K,make_pair(I+i,J) ) );
	}
}
void otherCar(){
    glPushMatrix();
        {
          glColor3f(.3,.8,1);
          glScalef(2,1,.4);    /*******lower part********/
          glutSolidCube(10);
        }glPopMatrix();

        glPushMatrix();
        {
           glTranslatef(0,0,3);
           glColor3f(.45,.56,.67);   /******* upper part********/
           glScalef(1,1,.6);
           glutSolidCube(10);
        }glPopMatrix();

        glPushMatrix();
       {
          glTranslatef(4,5,-2);
          glColor3f(0,0,1);   /******* front wheel left part********/
          glScalef(2,.7,1);
          glutSolidSphere(2,100,100);
        }glPopMatrix();


       glPushMatrix();
       {
          glTranslatef(-4,5,-2);
          glColor3f(0,0,1);   /******* front wheel right part********/
          glScalef(1,.7,1);
          glutSolidSphere(2,100,100);
      }glPopMatrix();

      glPushMatrix();
      {
         glTranslatef(4,-5,-2);
         glColor3f(0,0,1);   /******* behind wheel left part********/
         glScalef(1,.7,1);
         glutSolidSphere(2,100,100);
      }glPopMatrix();


      glPushMatrix();
      {
         glTranslatef(-4,-5,-2);
         glColor3f(0,0,1);   /******* behind wheel right part********/
         glScalef(1,.7,1);
         glutSolidSphere(2,100,100);
      }glPopMatrix();
}
void drawRoad(){
    glPushMatrix();
    glColor3f(0.245, 0.245, 0.245);

      glBegin(GL_POLYGON);

        glVertex3f(100,0,-30);
        glVertex3f(-100,0,-30);

        glVertex3f(-100,-5000,-30);
        glVertex3f(100,-5000,-30);

      glEnd();

    glPopMatrix();
}
void DrawMiddle(){

    glPushMatrix();
    glColor3f(1, 1, 1);

      glTranslatef(0,0,3);

      glBegin(GL_POLYGON);

        glVertex3f(-2,0,-30);
        glVertex3f(2,0,-30);

        glVertex3f(-2,-5000,-30);
        glVertex3f(2,-5000,-30);

      glEnd();

    glPopMatrix();
}
void sideRoad(){
    glPushMatrix();
    glColor3f(0.245, 0.245, 0.245);

      glBegin(GL_POLYGON);

        glVertex3f(100,0,-30);
        glVertex3f(-100,0,-30);

        glVertex3f(-100,-300,-30);
        glVertex3f(100,-300,-30);

      glEnd();

    glPopMatrix();
}
void drawMainCar(){
    glPushMatrix();
    cout<<car<<endl;


    glTranslatef(leftRightMove,car,0);
    glRotatef(90,0,0,1);

    glPushMatrix();
    {
        glColor3f(1,.8,3);
        glScalef(2,1,.4);    /*******lower part********/
         glutSolidCube(10);
    }glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0,0,3);
        glColor3f(.87,.87,.87);   /******* upper part********/
        glScalef(1,1,.6);
         glutSolidCube(10);
    }glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(4,5,-2);
        glColor3f(1,.3,8);   /******* front wheel left part********/
        glScalef(2,.7,1);
        glutSolidSphere(2,100,100);
    }glPopMatrix();


    glPushMatrix();
    {
        glTranslatef(-4,5,-2);
        glColor3f(1,0,1);   /******* front wheel right part********/
        glScalef(1,.7,1);
        glutSolidSphere(2,100,100);
    }glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(4,-5,-2);
        glColor3f(1,.6,8);   /******* behind wheel left part********/
        glScalef(1,.7,1);
        glutSolidSphere(2,100,100);
    }glPopMatrix();


    glPushMatrix();
    {
        glTranslatef(-4,-5,-2);
        glColor3f(1,.3,8);   /******* behind wheel right part********/
        glScalef(1,.7,1);
        glutSolidSphere(2,100,100);
    }glPopMatrix();

     glPushMatrix();
}
void Tal(){
     glPushMatrix();
                glColor3f(.5,.5,.3);
                glScalef(.01,.4,5);
                glutSolidSphere(7,10,10);
                glPopMatrix();

                glPushMatrix();
                glTranslatef(5,0,1);
                glColor3f(0,.5,.3);
                glutSolidSphere(10,10,10);
                glPopMatrix();

                glPushMatrix();
                glTranslatef(-5,0,1);
                glColor3f(0,.5,.3);
                glutSolidSphere(10,10,10);
                glPopMatrix();

                glPushMatrix();
                glTranslatef(0,0,20);
                glColor3f(0,.5,.2);
                glutSolidSphere(15,10,10);
                glPopMatrix();
}
void Sbrd(){
             glPushMatrix();
             glColor3f(0,1,0);
             glutSolidCone(20,30,20,20);

             glPopMatrix();

             glPushMatrix();
             glColor3f(.5,.5,.3);
             glScalef(.01,.4,5);
             glutSolidSphere(7,10,10);

             glPopMatrix();
}
void NarcalG(){
    glPushMatrix();

               glTranslatef(0,0,30);
               glRotatef(45,0,1,0);
               glColor3f(0,.674,.543);
               glScalef(.5,1,5);
               glutSolidSphere(4,10,10);

              glPopMatrix();

              glPushMatrix();

              glTranslatef(0,0,30);
              glRotatef(315,0,1,0);
              glColor3f(0,.674,.543);
              glScalef(.5,1,5);
              glutSolidSphere(4,10,10);

              glPopMatrix();

              glPushMatrix();

              glTranslatef(0,0,30);

              glColor3f(0,.674,.543);

              glScalef(.5,1,5);

              glutSolidSphere(4,10,10);

             glPopMatrix();



             glPushMatrix();

             glTranslatef(0,0,0);

             glPushMatrix();

             glPushMatrix();
             glColor3f(.5,.5,.3);
             glScalef(.01,.4,5);
             glutSolidSphere(7,10,10);

            glPopMatrix();
}
void drawN(float j) {
    glPushMatrix();
    glTranslatef(120, -j, 0);
    NarcalG();
    glPopMatrix();
}
void drawT(float j) {
    glPushMatrix();
    glTranslatef(-120, -j, 0);
    Tal();
    glPopMatrix();
}
void drawS(float j) {
    glPushMatrix();
    glTranslatef(-120, -j, 0);
    Sbrd();
    glPopMatrix();
}
void drawObjects(int i, float j){
    if (i % 3 == 0) {
        drawN(j);
    } else if (i % 1 == 0) {
        drawT(j);
    } else {
        drawS(j);
    }
}
void drawPolygon(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4){
    glBegin(GL_POLYGON);

    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y2, z2);
    glVertex3f(x3, y3, z3);
    glVertex3f(x4, y4, z4);

    glEnd();

    glPopMatrix();
}
void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(.345, 0.4, 0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,Y,Z,	0,-40000,0,	0,0,1);
	glMatrixMode(GL_MODELVIEW);

    if(abs(car)<=4000)
    {
        car-=1;
        Y-=1;
        sky-=1;
        int j=0;
        for(int i=1;i<=100;i++,j+=40){
             drawObjects(i, j);
        }
         j=0;
       for(int i=1;i<=100;i++,j+=40){
              drawObjects(i, j);
        }
    drawRoad();
    DrawMiddle();
    }

    else if(abs(car)<=8000)
    {
        car-=2;
        Y-=2;
        sky-=2;
    glPushMatrix();
    glColor3f(0.245, 0.245, 0.245);
    drawPolygon(100, -4000, -30, -100, -4000, -30, -100, -9500, -30, 100, -9500, -30);
    }
    else if(abs(car)<=12000)
    {
       car-=3;
       Y-=3;
       sky-=3;
        for(int i=1,j=8000;i<=5;i++,j+=200)
        {
          drawObjects(i, j);
        }
        for(int i=1,j=8000;i<=5;i++,j+=200)
        {
           drawObjects(i, j);
        }
        for(int i=1,j=12000;i<=5;i++,j+=200)
        {
           drawN(j);
        }
        for(int i=1,j=12000;i<=5;i++,j+=200)
        {
          drawT(j);
        }
        glPushMatrix();
        glColor3f(1, 1, 1);
        glTranslatef(0,0,3);
        drawPolygon(-2, -8000, -30, 2, -8000, -30, -2, -13500, -30, 2, -13500, -30);
        glPushMatrix();
        glColor3f(0.245, 0.245, 0.245);
        drawPolygon(100, -8000, -30, -100, -8000, -30, -100, -13500, -30, 100, -13500, -30);
    }

    else if(abs(car)<=16000)
    {
        car-=4;
        Y-=4;
        sky-=4;

        for(int i=1,j=12000;i<=20;i++,j+=200)
        {
            drawN(j);
        }
        for(int i=1,j=12000;i<=20;i++,j+=200)
        {
            drawT(j);
        }
        glPushMatrix();
        glColor3f(1, 1, 1);
        glTranslatef(0,0,3);
        drawPolygon(-2, -12000, -30, 2, -12000, -30, -2, -17500, -30, 2, -17500, -30);
        glPushMatrix();
        glColor3f(0.245, 0.245, 0.245);
        drawPolygon(100, -12000, -30, -100, -12000, -30, -100, -17500, -30, 100, -17500, -30);
    }
    else if(abs(car)<=20000)
    {
        car-=5;
        Y-=5;
        sky-=5;
        for(int i=1,j=16000;i<=20;i++,j+=200)
        {
         drawObjects(i, j);
        }
        for(int i=1,j=16000;i<=20;i++,j+=200)
        {
          drawObjects(i, j);
        }
        glPushMatrix();
        glColor3f(1, 1, 1);
        glTranslatef(0,0,3);
        drawPolygon(-2, -16000, -30, 2, -16000, -30, -2, -21500, -30, 2, -21500, -30);
        glPushMatrix();
        glColor3f(0.245, 0.245, 0.245);
        drawPolygon(100, -16000, -30, -100, -16000, -30, -100, -21500, -30, 100, -21500, -30);
    }

    else if(abs(car)<=24000)
    {
        car-=6;
        Y-=6;
        sky-=6;
        for(int i=1,j=20000;i<=5;i++,j+=200)
        {
            drawObjects(i, j);
        }

        for(int i=1,j=20000;i<=5;i++,j+=200)
        {
            drawObjects(i, j);
        }
        glPushMatrix();
        glColor3f(1, 1, 1);
        glTranslatef(0,0,3);
        drawPolygon(-2, -20000, -30, 2, -20000, -30, -2, -30000, -30, 2, -30000, -30);
        glPushMatrix();
        glColor3f(0.245, 0.245, 0.245);
        drawPolygon(100, -20000, -30, -100, -20000, -30, -100, -30000, -30, 100, -30000, -30);
    }
    else if(abs(car)<=28000)
    {
        car-=7;
        Y-=7;
        sky-=7;
        glPushMatrix();
        glColor3f(1, 1, 1);
        glTranslatef(0,0,3);
        drawPolygon(-2, -24000, -30, 2, -4000, -30, -2, -31500, -30, 2, -31500, -30);
        glPushMatrix();
        glColor3f(0.245, 0.245, 0.245);
        drawPolygon(100, -24000, -30, -100, -24000, -30, -100, -31500, -30, 100, -31500, -30);

    }

    else if(abs(car)<=32000)
    {
        car-=8;
        Y-=8;
        sky-=8;
        int j=28000;
        for(int i=1;i<=100;i++,j+=40) {
          drawObjects(i, j);
        }
         j=28000;
       for(int i=1;i<=100;i++,j+=40){
            drawObjects(i, j);
        }
        glPushMatrix();
        glColor3f(1, 1, 1);
        glTranslatef(0,0,3);
        drawPolygon(-2, -28000, -30, 2, -28000, -30, -2, -33500, -30, 2, -33500, -30);
        glPushMatrix();
        glColor3f(0.245, 0.245, 0.245);
        drawPolygon(100, -28000, -30, -100, -28000, -30, -100, -33500, -30, 100, -33500, -30);
    }

    else if(abs(car)<=36000)
    {
        car-=9;
        Y-=9;
        sky-=9;
        glPushMatrix();
        glColor3f(1, 1, 1);
        glTranslatef(0,0,3);
        drawPolygon(-2, -32000, -30, 2, -32000, -30, -2, -37500, -30, 2, -37500, -30);
        glPushMatrix();
        glColor3f(0.245, 0.245, 0.245);
        drawPolygon(100, -32000, -30, -100, -32000, -30, -100, -37500, -30, 100, -37500, -30);
    }
    else if(abs(car)<=40000)
    {
        car-=10;
        Y-=10;
        sky-=10;

        for(int i=1,j=36000;i<=5;i++,j+=200)
        {
           drawObjects(i, j);
        }
        for(int i=1,j=36000;i<=5;i++,j+=200)
        {
            drawObjects(i, j);
        }
        for(int i=1,j=40000;i<=5;i++,j+=200)
        {
           drawN(j);
        }
        for(int i=1,j=40000;i<=5;i++,j+=200)
        {
           drawT(j);
        }
        glPushMatrix();
        glColor3f(1, 1, 1);
        glTranslatef(0,0,3);
        drawPolygon(-2, -36000, -30, 2, -36000, -30, -2, -41500, -30, 2, -41500, -30);
        glPushMatrix();
        glColor3f(0.245, 0.245, 0.245);
        drawPolygon(100, -36000, -30, -100, -36000, -30, -100, -41500, -30, 100, -41500, -30);
    }
    else if(abs(car)<=44000)
    {
        car-=11;
        Y-=11;
        sky-=11;
        for(int i=1,j=40000;i<=20;i++,j+=200)
        {
           drawN(j);
        }

        for(int i=1,j=40000;i<=20;i++,j+=200)
        {
           drawT(j);
        }
        glPushMatrix();
        glColor3f(1, 1, 1);
        glTranslatef(0,0,3);
        drawPolygon(-2, -40000, -30, 2, -40000, -30, -2, -45500, -30, 2, -45500, -30);
        glPushMatrix();
        glColor3f(0.245, 0.245, 0.245);
        drawPolygon(100, -40000, -30, -100, -40000, -30, -100, -45500, -30, 100, -45500, -30);
    }
    else if(abs(car)<=48000)
    {
        car-=12;
        Y-=12;
        sky-=12;
        for(int i=1,j=44000;i<=20;i++,j+=200)
        {
           drawObjects(i, j);
        }
        for(int i=1,j=44000;i<=20;i++,j+=200)
        {
          drawObjects(i, j);
        }
        glPushMatrix();
        glColor3f(1, 1, 1);
        glTranslatef(0,0,3);
        drawPolygon(-2, -44000, -30, 2, -44000, -30, -2, -49500, -30, 2, -49500, -30);
        glPushMatrix();
        glColor3f(0.245, 0.245, 0.245);
        drawPolygon(100, -44000, -30, -100, -44000, -30, -100, -49500, -30, 100, -49500, -30);
    }
    else if(abs(car)<=52000)
    {
        car-=13;
        Y-=13;
        sky-=13;
        for(int i=1,j=48000;i<=5;i++,j+=200)
        {
           drawObjects(i, j);
        }
        for(int i=1,j=48000;i<=5;i++,j+=200)
        {
           drawObjects(i, j);
        }
        glPushMatrix();
        glColor3f(1, 1, 1);
        glTranslatef(0,0,3);
        drawPolygon(-2, -48000, -30, 2, -48000, -30, -2, -53500, -30, 2, -53500, -30);
        glPushMatrix();
        glColor3f(0.245, 0.245, 0.245);
        drawPolygon(100, -48000, -30, -100, -48000, -30, -100, -53500, -30, 100, -53500, -30);
    }
    cout<<leftRightMove<<"------\n";
    drawMainCar();
    /*********************************************************/
    int II=0;
    int Len=CARS.size();
    for(int I=NumberOfCar;I<Len;I++){
        if(CARS[I].second.first-abs(car)>=700)
        {
            break;
        }
        if(abs(car)>CARS[I].second.first+700)
        {
            NumberOfCar++;
        }
        else{
          glPushMatrix();
          if(CARS[I].first==0)
           glTranslatef(CARS[I].second.second,-CARS[I].second.first++,0);
          else
           glTranslatef(-CARS[I].second.second,-CARS[I].second.first++,0);
           glRotatef(90,0,0,1);
           glColor3f(1,0,0);
           otherCar();
           glPopMatrix();
        }
  }
/*********************************************************************************************/
    for(int I=0;I<Len;I++){

         if(CARS[I].first==0 && car-20<=-CARS[I].second.first &&car>=-CARS[I].second.first-20 && leftRightMove >=CARS[I].second.second-10 && leftRightMove <= CARS[I].second.second+10)
         {
            exit(0);
         }
          else if(CARS[I].first==1 && car-20<=-CARS[I].second.first &&car>=-CARS[I].second.first-20 && leftRightMove <=-CARS[I].second.second+10 && leftRightMove >= -CARS[I].second.second-10)
         {
            exit(0);
         }
     }

     glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 720, 1080, 0, -1, 1);  // Set orthographic projection
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2f(10, 20);  // Set the position of the text
	glColor3f(0.0f, 0.0f, 1.0f);  // Set text color (blue)
	const char* text = "For change camera use page up and page down";
	for (const char* c = text; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);  // Render each character of the text
	}
	glRasterPos2f(10, 40);  // Set the position of the text
	glColor3f(0.0f, 0.0f, 1.0f);  // Set text color (blue)
	const char* text1 = "for quit press insert";
	for (const char* c = text1; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);  // Render each character of the text
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glutSwapBuffers();
}
void animate(){
	angle+=0.05;
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}
void init(){
	//codes for initialization
	drawgrid=0;
	drawaxes=1;
	cameraHeight=150.0;
	cameraAngle=1.0;
	angle=0;

	u.x=0;
    u.y=0;
    u.z=1;


    r.x=-1/sqrt(2);
    r.y=1/sqrt(2);
    r.z=0;

    l.x=-1/sqrt(2) ;
    l.y=-1/sqrt(2) ;
    l.z=0;

    pos.x=100;
    pos.y=100;
    pos.z=0;


	map_angle=90;

	glClearColor(0,0,0,0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(80,	1,	1,	70000.0);

}
void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_UP:		// up arrow key
			//cameraHeight += 3.0;
			car-=10;
			Y-=10;
			X-=3;
            sky-=10;
			if(Y==-20000){
                Y=50;car=0;sky=-1000;
			}
			pos.x+=l.x*move_pos;
			pos.y+=l.y*move_pos;
			pos.z+=l.z*move_pos;
			break;
		case GLUT_KEY_RIGHT:
               if(leftRightMove>=-30){
               leftRightMove-=5;
		       car-=5;
			   Y-=5;
			   sky-=5;
            }
			cameraAngle += 0.03;
			pos.x+=r.x*move_pos;
			pos.y+=r.y*move_pos;
			pos.z+=r.z*move_pos;
			break;
		case GLUT_KEY_LEFT:
            if(leftRightMove<=30){
		    leftRightMove+=5;
		    car-=5;
			Y-=5;
			sky-=5;
        }
			cameraAngle -= 0.03;
			pos.x-=r.x*move_pos;
			pos.y-=r.y*move_pos;
			pos.z-=r.z*move_pos;
			break;
		case GLUT_KEY_PAGE_UP:
		    Z+=7.5;
		    Y+=10;
			break;
		case GLUT_KEY_PAGE_DOWN:
            Z-=7.5;
            Y-=10;
			break;
		case GLUT_KEY_INSERT:
		    exit(0);
			break;
		default:
			break;
	}
}
int main(int argc, char **argv) {
    drive();
    glutInit(&argc, argv);
    glutInitWindowSize(720, 1080);
    glutInitWindowPosition(500, 100);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("3D Car Game");
    init();
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutSpecialFunc(specialKeyListener);


    glutMainLoop(); // Start the main loop of OpenGL

    return 0;
}


