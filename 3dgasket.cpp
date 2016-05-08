//A tetrahedron has 4 eq.triangular faces and 4 vertices
#include<stdlib.h>
#include<stdio.h>
#include<GL/glut.h>

typedef float point[3]; //typedef-used to create alias name...hence point is alias for type float


//the four vertices of a tetrahedron..considering 3d(x,y,z)
point v[] = {{0.0,0.0,0.0},{0.0,0.9,-0.3},{-.8,-.4,-.3},{.8,-.4,-.3}};

int n;//no. of divisions

static GLfloat theta[] = {0.0,0.0,0.0}; //??

void triangle(point a, point b, point c){

    //generates a triangle
                
       glBegin(GL_POLYGON);
             
            glVertex3fv(a);
            glVertex3fv(b);
            glVertex3fv(c);
       
        glEnd();
}

void divide_triangle(point a,point b,point c,int m){

    
    //divides a 2D triangle(one face of a tetrahedron) recursively
            point v1,v2,v3;
            int j;

     //perform the division specified no. of times(m),else draw the triangle
             if(m>0){

                    for(j=0;j<3;j++)
                         v1[j]= (a[j] + b[j])/2; //midpoint of 1st edge of triangle
                    
                    for(j=0;j<3;j++)
                          v2[j]= (a[j]+ c[j])/2; //midpoint of 2nd edge
                     
                    for(j=0;j<3;j++)
                          v3[j]=(b[j] + c[j])/2; //midpoint of 3rd edge

                    divide_triangle(a,v1,v2,m-1);
                    divide_triangle(c,v2,v3,m-1);
                    divide_triangle(b,v3,v1,m-1);

             }

          else triangle(a,b,c);
}
                        
                
void tetrahedron(int m){
     
     //v[i] indicates each of vertex from i=0->3
               glColor3f(1.0,0.0,0.0);//red
               divide_triangle(v[0],v[1],v[2],m);// to recursively divide  first face of the tetrahedron

               glColor3f(0.0,0.0,1.0);//blue
               divide_triangle(v[3],v[2],v[1],m);// recursively divides second face of the tetrahedron

               glColor3f(0.0,1.0,0.0);//green
               divide_triangle(v[0],v[3],v[1],m);//recursively divides third face of the tetrahedron

               glColor3f(0.0,0.0,0.0);//black
               divide_triangle(v[0],v[2],v[3],m);//recursively divides fourth face of the tetrahedron

}


void display(void){

             glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//Bitwise OR of masks that indicate the buffers to be cleared              
             //GL_COLOR_BUFFER_BIT:Indicates the buffers currently  
             //GL_DEPTH_BUFFER_BIT:Indicates the depth buffer.

             glLoadIdentity();//sets current transformation matrix to an identity matrix
             
             tetrahedron(n);//passing no. of divisions
             glFlush();//forces any buffered openGL commands to be executed

}
                
           
// function is executed when the window size is changed. 
void myReshape(int w,int h)
{
       glViewport(0,0,w,h);//sets the viewport here x,y=0,0 indicating lower left corner of viewport and w,h representing width,height
       
       glMatrixMode(GL_PROJECTION);//indicates which matrix is current matrix (projection stack)
 
       glLoadIdentity();//sets current matrix to an identity matrix
       
        if(w<=h) 
              //to get exact aspect ratio
              glOrtho(-2.0,2.0,-2.0*(GLfloat)h/(GLfloat)w,2.0*(GLfloat)h/(GLfloat)w,-10.0,10.0); //width is smaller than height
        else
              glOrtho(-2.0*(GLfloat)w/(GLfloat)h,2.0*(GLfloat)w/(GLfloat)h,-2.0,2.0,-10.0,10.0); //height is smaller
  
       glMatrixMode(GL_MODELVIEW); // indicates matrix is modelview matrix
       glutPostRedisplay(); //requests display callback to be executed after current callback returns
}

                
int main(int argc,char **argv)
{
        
        
  	printf("no. of divisions \n");
  	scanf("%d",&n);
 
  	glutInit(&argc,argv);//initializes  GLUT
  	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);//logical OR od display options
  	glutInitWindowSize(500,500);
  	glutCreateWindow("3DGasket"); //window with a title
  	glutReshapeFunc(myReshape);   
  	glutDisplayFunc(display);//registers the display function func that is executed when the window needs to be drawn

  	glEnable(GL_DEPTH_TEST);//indicate features which are to enabled
  	glClearColor(1.0,1.0,1.0,1.0);
  	glutMainLoop(); //cause the prgrm to enter an event-processing loop
}
