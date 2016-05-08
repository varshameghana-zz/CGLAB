//rectangular mesh
#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>

#define maxx 25 //no. of rectangles in x direction
#define maxy 20 //no. of rectangles in y direction

#define dx 15 //size of each box is 15*10
#define dy 10

GLfloat x[maxx]={0,0} ,y[maxx]={0,0};  
GLfloat x0=50, y0=50; //initial coordinates of the rectangle

GLint i,j;

void init(){

	 glClearColor(1.0,1.0,1.0,1.0);//clears old background and resets new one
	 //glColor3f(1.0,0.0,0.0);
	 glPointSize(5.0);

	 glMatrixMode(GL_PROJECTION);//specifies which matrix will be effected by susequent transformations
	 glLoadIdentity();//sets current transformation matrix to an identity matrix


	 gluOrtho2D(0.0,499.0,0.0,399.0); //defines a 2D viewing rectangle in the plane z=0
	 //glPostRedisplay(); //requests display callback to be executed after current callback returns

}

void display(void){

	
	      glClear(GL_COLOR_BUFFER_BIT);//BUFFER IS CLEARED

		  glColor3f(0.0,0.0,1.0); //always recently used color has effect

		  for(i=0;i<maxx;i++)
			   
			      x[i]= x0 + i*(dx);//starting point for each rectangle horizantally

		  for(j=0;j<maxy;j++)
			    
			      y[j]= y0 + j*(dy);//starting point of each rectangle vertically

		  glColor3f(0.0,0.0,1.0);

		      for(i=0;i<maxx-1;i++)
				for(j=0;j<maxy-1;j++){

					  glColor3f(0.0,0.0,1.0);

					  glBegin(GL_LINE_LOOP);

					       glVertex2f(x[i],y[j]);
                           glVertex2f(x[i],y[j+1]);
						   glVertex2f(x[i+1],y[j+1]);
						   glVertex2f(x[i+1],y[j]);
					  glEnd();

					  glFlush();//forces any buffered openGL commands to b e executed
			 
				}

		glFlush();
}

int main(int argc ,char** argv){

	glutInit(&argc,argv); //initializes  GLUT
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB); //requests a display with properties in mode(logical OR of options including colormodel and buffering.

	glutInitWindowSize(500,400); //specifies initial height and width of windows in pixels
	glutInitWindowPosition(0,0); //specifies the initial position of the top-left corner of window in pixels

	glutCreateWindow("Rectangular Mesh"); //creates a window on the display,title used to label the window

	glutDisplayFunc(display); //registers the display function func that is executed when the window needs to be drawn

	init();

	glutMainLoop(); //cause the prgrm to enter an event-processing loop.should  be last statemewnt in  main
}
