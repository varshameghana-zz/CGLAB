#include<stdio.h>
#include<GL/glut.h>


#define outcode int //outcode is defined as int, worduse can be interchanged     

// max,min window boundary values
double xmin=50,ymin=50,xmax=100,ymax=100;

// max,min viewport boundary values
double xvmin=200,yvmin=200,xvmax=300,yvmax=300;

// bitcodes for the right,left,top,bottom
const int RIGHT=8;  // 8 is eq to 1000 in binary
const int LEFT=2;   // 2-->0010
const int TOP=4;    // 4-->0100
const int BOTTOM=1; // 1-->0001

int x2,y2,x3,y3;

outcode ComputeOutcode(double x,double y);//used to compute outcode of a point(x,y)

void cohenClipAndDraw(double x0,double y0,double x1,double y1){


         outcode outcode1,outcode0,outcodeOut;
         bool accept=false, done=false;


        //we are trying to find if a given line with endpoints p1(x0,y0) and p2(x1,y1) lies inside the window...so first we compute outcode of each endpoint  
         outcode0= ComputeOutcode(x0,y0);
         outcode1= ComputeOutcode(x1,y1);

            
         do{


                 //wkt logical OR of outcodes of endpoints is 0000,it is trivially accepted and end there by setting both bool variables to true

                  if(!(outcode1|outcode1)){

                              accept= true;
                              done=true;   
                  }
                 
                  //wkt logical AND is 1111,trivially rejected and end
                   else if(outcode0 & outcode1)
                         done=true;
                     //accept remains false
                       
                   else{
        
                          //if both conditions fail, this means a clipped line segment should be obtained as the line lies partially inside the window

                           double x,y; //the intersection points of the window and line

                          
                    outcodeOut=outcode0?outcode0:outcode1;//finding point which is outside clippind window,since atleast one is outside winow,if both are outside we first pick p0 and then p1 in next round


            //intersection formula y=y0+slope*(x-x0), x=x0+(1/slope)*(y-y0)

            //point lies above clipping rectangle
            if(outcodeOut & TOP) 
            {
                x=x0+(x1-x0)*(ymax-y0)/(y1-y0);
                y=ymax;
            }

            // point lies below the clipping rectangle
            else if(outcodeOut & BOTTOM) 
            {
                x=x0+(x1-x0)*(ymin-y0)/(y1-y0);
                y=ymin;
            }

            // point lies to the right of clipping rectangle
            else if(outcodeOut & RIGHT) 
            {
                y=y0+(y1-y0)*(xmax-x0)/(x1-x0);
                x=xmax;
            }

            // point lies to the left of clipping rectangle
            else
            {   
                y=y0+(y1-y0)*(xmin-x0)/(x1-x0);
                x=xmin;
            }

            // moving outside point to intersection point and clip 
            if(outcodeOut==outcode0)
            {
                x0=x;
                y0=y;
                outcode0=ComputeOutcode(x0,y0);
            }
            else
            {
                x1=x;
                y1=y;
                outcode1=ComputeOutcode(x1,y1);
            }
        }
    }
    while(!done);

                          
               
   if(accept)
    {
        // Window to  viewport mappings

        // scaling parameters
        double sx=(xvmax-xvmin)/(xmax-xmin); 
        double sy=(yvmax-yvmin)/(ymax-ymin);

        double vx0=xvmin+(x0-xmin)*sx;
        double vy0=yvmin+(y0-ymin)*sy;
        double vx1=xvmin+(x1-xmin)*sx;
        double vy1=yvmin+(y1-ymin)*sy;

        //viewport
        glColor3f(0.0,0.0,0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(xvmin,yvmin);
        glVertex2f(xvmax,yvmin);
        glVertex2f(xvmax,yvmax);
        glVertex2f(xvmin,yvmax);
        glEnd();

        // draws blue line
        glColor3f(0.0,0.0,1.0); 
        glBegin(GL_LINES);
        glVertex2d(vx0,vy0);
        glVertex2d(vx1,vy1);
        glEnd();
    }
}


 // compute the outcode for a point(x,y) using the clip rectangle 

outcode ComputeOutcode(double x,double y)
{
    outcode code=0;
    if(y>ymax)
    {
        code|=TOP;//logical OR
    }
    else if(y<ymin)
    {
        code|=BOTTOM;
    }
    if(x>xmax)
    {
        code|=RIGHT;
    }
    else if(x<xmin)
    {
        code|=LEFT;
    }   
    return code;
}


void display()
{
          // double x0=60,y0=20,x1=80,y1=120;
          glClear(GL_COLOR_BUFFER_BIT);

          // line with blue
          glColor3f(0.0,0.0,1.0);

          glBegin(GL_LINES);

    
              //glVertex2d(x0,y0);if values are not entered at run time
              //glVertex2d(x1,y1);

              //using values entered in scanf func
                glVertex2d(x2,y2);
                glVertex2d(x3,y3);
           glEnd();

          // draw black color window
    	  glColor3f(0.0,0.0,0.0);
    
          glBegin(GL_LINE_LOOP);
                  glVertex2f(xmin,ymin);
                  glVertex2f(xmax,ymin);
                  glVertex2f(xmax,ymax);
                  glVertex2f(xmin,ymax);
          glEnd();
    
      cohenClipAndDraw(x2,y2,x3,y3);//func to find whether lines are trivially accepted,rejected or clipped
      
      glFlush();

}

void myinit()
{
      glClearColor(1.0,1.0,1.0,1.0);//white
      glColor3f(1.0,0.0,0.0);
      glPointSize(1.0);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(0.0,500.0,0.0,500.0);//2D viewing rect(left,right,bottom,top)

}


int main(int argc,char **argv)
{   
    printf("Enter End Points:(x0,x1,y0,y1)");
    scanf("%d%d%d%d",&x2,&x3,&y2,&y3);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Cohen Sutherland Line Clipping Algorithm");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
}
