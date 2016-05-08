//rotating house

#include<stdio.h>
#include<math.h>
#include<GL/glut.h>

//initialising the 9 vertices of house
GLfloat house[3][9]={{100.0,100.0,175.0,250.0,250.0,150.0,150.0,200.0,200.0}, {100.0,300.0,400.0,300.0,100.0,100.0,150.0,150.0,100.0}, {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0}};

//rotation matrix is a 3*3 matrix
GLfloat rot_mat[3][3]={{0},{0},{0}};

//result matrix is obtained by multiplying the rotation matrix with house matrix
//ie.., (3*3)*(3*9) =(3*9)
GLfloat result[3][9]={{0},{0},{0}};

GLfloat h=100.0;
GLfloat k=100.0;

GLfloat theta;//rotation angle

//Multiply rotation matrix with coordinate points of house.This gives us coordiante points of rotated house

void multiply(){

    //matrix multiplication
    int i,j,k;
    for(i=0;i<3;i++)
    for(j=0;j<9;j++){
        result[i][j]=0;

        for(k=0;k<3;k++)
            result[i][j]=result[i][j]+rot_mat[i][k]*house[k][j];
    }
}

void drawhouse()
{
        //drawing house with initial coordinates,ie..before rotation
         int i;

       //draws the bigger rectangle in blue,i=2 is not considered as it lies outside this rectangle(i.e.. it is tip of the triangle)
         glColor3f(0.0,0.0,1.0);
         glBegin(GL_LINE_LOOP);
            for(i=0;i<=4;i++)
                if(i!=2)
                  glVertex2f(house[0][i],house[1][i]);
         glEnd();

         //door-->set to red color
         glColor3f(1.0,0.0,0.0);
         glBegin(GL_LINE_LOOP);
         
            for(i=5;i<=8;i++)
               glVertex2f(house[0][i],house[1][i]);
         glEnd();

       //upper triangle of house,set to blue
         glColor3f(0.0,0.0,1.0);

         glBegin(GL_LINE_LOOP);

            for(i=1;i<=3;i++)
                  glVertex2f(house[0][i],house[1][i]);
          glEnd();
}


void rotate(){

         GLfloat m,n;

         m=-h*(cos(theta)-1)+k*(sin(theta));// of form x-xcos(theta)+ysin(theta)
         n=-k*(cos(theta)-1)-h*(sin(theta));// of form y-ycos(theta)-xsin(theta)

         rot_mat[0][0]=cos(theta);
         rot_mat[0][1]=-sin(theta);
         rot_mat[0][2]=m;
         rot_mat[1][0]=sin(theta);
    	 rot_mat[1][1]=cos(theta);
    	 rot_mat[1][2]=n;
    	 rot_mat[2][0]=0;
         rot_mat[2][1]=0;
    	 rot_mat[2][2]=1;
         multiply();
}



// func to draw rotated house,after being rotated by specified angle 
void drawrotatedhouse()
{
        //drawing house with final coordinates,ie..after rotation
          int i;

       //draws the bigger rectangle in blue,i=2 is not considered as it lies  outside this rectangle(i.e.. it is tip of the triangle)
         glColor3f(0.0,0.0,1.0);
         glBegin(GL_LINE_LOOP);
            for(i=0;i<=4;i++)
                if(i!=2)
                  glVertex2f(result[0][i],result[1][i]);
         glEnd();

         //door-->set to red color
         glColor3f(1.0,0.0,0.0);
         glBegin(GL_LINE_LOOP);
         
            for(i=5;i<=8;i++)
               glVertex2f(result[0][i],result[1][i]);
         glEnd();

       //upper triangle of house,set to blue
         glColor3f(0.0,0.0,1.0);

         glBegin(GL_LINE_LOOP);

            for(i=1;i<=3;i++)
                  glVertex2f(result[0][i],result[1][i]);
          glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawhouse();//draw before rotation
    rotate();//function to rotate
    drawrotatedhouse();//after rotation
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
    printf("Enter the rotation angle\n");
    scanf("%f",&theta);
    theta=theta*(3.14/180);//converting angle entered in degrees to radian measure
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("house rotation");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
}
