//LiangBarsky algorithm

#include<stdio.h>
#include<GL/glut.h>

int x0,y0,y1,x1;
double xmin=50,xmax=100,ymax=100,ymin=50; //min,max values for window boundary
double xvmin=200,yvmin=200,xvmax=300,yvmax=300; //min,max values for viewport boundary


int cliptest(double p,double q,double *t1,double *t2)
{
    double t=q/p;
    if(p<0.0)
    {
        //potentially entry point,update te
      //using pointers since values changed in functions are updated in actual parameters
        if(t>*t1)
            *t1=t;
        if(t>*t2)//t cannot be greater than tl,since tl=1 is max value t can have
            return false;   //line portion is outside
    }
    else if(p>0.0)
    {

        //potentially leaving point,update tl
        if(t<*t2)
            *t2=t;
        if(t<*t1)//t cannot be lesser than te,since te=0 is min.value t can have
            return false; //line portion is outside
    }
    else if(p==0.0) {
            if(q<0.0)
                return false; //line parallel to edge but outside
    } 

    return true;
}


void liang(double x0,double y0,double x1,double y1)
{

   //arguments are endpoints of the line ie..p1(x0,y0) and p2(x1,y1)

    double dx=x1-x0,dy=y1-y0,te=0.0,tl=1.0;//te and tl represent min(entry) and max(exit)
    if(cliptest(-dx,x0-xmin,&te,&tl))   //inside test wrt left edge
        if(cliptest(dx,xmax-x0,&te,&tl))    //inside test wrt Right edge
            if(cliptest(-dy,y0-ymin,&te,&tl))   //inside test wrt Bottom edge
                if(cliptest(dy,ymax-y0,&te,&tl))    //inside test wrt Top edge
                {
                    if(tl<1.0) //means value of tl has been updated after calling cliptest
                    {
                        //new leaving point values ,i.e..p1
                        x1=x0+tl*dx;
                        y1=y0+tl*dy;
                    }
                    if(te>0.0)//te was updated
                    {

                        //new leaving point values ,i.e..p2
                        x0=x0+te*dx;
                        y0=y0+te*dy;
                    }


            //Window to viewport mappings
            //sx and sy is used to scale the line. it zooms the the clipping window 
                    double sx=(xvmax-xvmin)/(xmax-xmin);
                    double sy=(yvmax-yvmin)/(ymax-ymin);

                
                    double vx0=xvmin+(x0-xmin)*sx;
                    double vy0=yvmin+(y0-ymin)*sy;
                    double vx1=xvmin+(x1-xmin)*sx;
                    double vy1=yvmin+(y1-ymin)*sy;
                    // black colored viewport

                    glColor3f(0.0,0.0,0.0);
                    glBegin(GL_LINE_LOOP);      
                        glVertex2f(xvmin,yvmin);
                        glVertex2f(xvmax,yvmin);
                        glVertex2f(xvmax,yvmax);
                        glVertex2f(xvmin,yvmax);
                    glEnd();

                   //blue clipped line
                    glColor3f(0.0,0.0,1.0);
                    glBegin(GL_LINES);         
                        glVertex2d(vx0,vy0);
                        glVertex2d(vx1,vy1);
                    glEnd();
                }
}


void display()
{
    //double x2=60,y2=20,x3=80,y3=120;//line endpoints

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINES);//draw a line that needs to be clipped 
        glVertex2d(x0,y0);
        glVertex2d(x1,y1);
    glEnd();

    //draw blue colo window       
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINE_LOOP);      
        glVertex2f(xmin,ymin);
        glVertex2f(xmax,ymin);
        glVertex2f(xmax,ymax);
        glVertex2f(xmin,ymax);
    glEnd();
    liang(x0,y0,x1,y1);         //function liang() is called by passing line endpoints
    glFlush();
}

void myinit()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(1.0,0.0,0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,499.0,0.0,499.0);
}

int main(int argc,char **argv)
{
    
    prizntf("Enter End Points");
    scanf("%d%d%d%d",&x0,&x1,&y0,&y1);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Liang Barksy Line Clipping algorithm");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
    return 0;
}
