#include<stdlib.h>
#include<GL/glut.h>


//eight 3D coordinate points
GLfloat vertices [][3] = {{-1.0,-1.0,-1.0}, {1.0,-1.0,-1.0}, {1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0}, {1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};
GLfloat normals [][3] = {{-1.0,-1.0,-1.0}, {1.0,-1.0,-1.0}, {1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0}, {1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};
GLfloat colors [][3] = {{0.0,0.0,0.0}, {1.0,-1.0,-1.0}, {1.0,1.0,0.0}, {0.0,1.0,0.0}, {0.0,0.0,1.0}, {1.0,0.0,1.0}, {1.0,1.0,1.0}, {0.0,1.0,1.0}};


void polygon(int a,int b,int c,int d)
{

    //draw a polygon via a list of vertices
    glBegin(GL_POLYGON);
        glColor3fv(colors[a]);
    	glNormal3fv(normals[a]);
    	glVertex3fv(vertices[a]);
    	glColor3fv(colors[b]);
    	glNormal3fv(normals[b]);
    	glVertex3fv(vertices[b]);
    	glColor3fv(colors[c]);
    	glNormal3fv(normals[c]);
    	glVertex3fv(vertices[c]);
    	glColor3fv(colors[d]);
    	glNormal3fv(normals[d]);
    	glVertex3fv(vertices[d]);
    glEnd();
}


void colorcube(void){

//maps vertices to faces

    polygon(0,3,2,1);   
    polygon(2,3,7,6);
    polygon(0,4,7,3);
    polygon(1,2,6,5);
    polygon(4,5,6,7);
    polygon(0,1,5,4);

}

static GLfloat theta[] = {0.0,0.0,0.0};

static GLint axis=2;//max index is 2


//function display first sets a model-view matrix using values of three angles determined by mouse callback, then draws a cube using colorcube
void display(void){

          glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
          glLoadIdentity();
    	  glRotatef(theta[0],1.0,0.0,0.0);//glRotate produces a rotation of angle degrees around the vector x y z .
    	  glRotatef(theta[1],0.0,1.0,0.0);
    	  glRotatef(theta[2],0.0,0.0,1.0);
          colorcube();
          glFlush();
          glutSwapBuffers();//glutSwapBuffers swaps the buffers of the current window if double buffered.

}

//increments angle assosiated with chosen axis by 2
void spinCube(){
         //Select the axis to rotate.
         //Rotate the cube by a small angle every small interval of time.repeat as long as axis is not changed

          theta[axis]+=2.0;
          if(theta[axis]>360.0){
                
               //make it zero again
                  theta[axis]-=360;
           }
          glutPostRedisplay();//marks the current window as needing to be redisplayed.
                 
}


//mouse callback sets axis for rotation
void mouse(int btn,int state,int x,int y)
{
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
        axis=0;
    if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN)
        axis=1;
    if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
        axis=2;
    spinCube();
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
      
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("spin a color cube ");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(spinCube);//If enabled, the idle callback is continuously called when events are not being received
    glutMouseFunc(mouse);// sets the mouse callback for the current window.
    glEnable(GL_DEPTH_TEST);//enable a feature 
    glutMainLoop();
}
