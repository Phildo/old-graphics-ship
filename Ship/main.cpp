#import <OpenGL/OpenGL.h>
#import <GLUT/GLUT.h>
#include <cstdlib>
#include <math.h>
#include <iostream>

#include "Vector3.h"
#include "Ship.h"
#include "Torpedo.h"
#include "Saucer.h"
#include "highprecisiontime.h"

#define NUM_SHIPS 100

//VARIABLES
int height = 700;
int width = 1000;

double mouseX = 0;
double mouseY = 0;

//Modes
int shadeMod = 0;
int wire = 0;
int mode = 0;
bool paused = true;

//Ships
Ship *sArray[NUM_SHIPS];
Torpedo *torpedoCloseup;
Saucer *saucerCloseup;

//HighPrecisionTime *time = new HighPrecisionTime();

//Updates ship variables to determine position/rotation
//NOTE-DOES NOT DRAW
void updateShips()
{
  if(mode == 0) for(int x = 0; x < NUM_SHIPS; x++) sArray[x]->UpdatePosition(1.0);
  if(mode == 1) torpedoCloseup->UpdatePosition(1.0);
  if(mode == 2) saucerCloseup->UpdatePosition(1.0);
}

//Draws ship(s) depending on mode
void drawShips()
{
  if(mode == 0) for(int x = 0; x < NUM_SHIPS; x++) sArray[x]->Draw(shadeMod, wire); //Draw all ships
  else if(mode == 1) torpedoCloseup->Draw(shadeMod, wire); //Draw just closeup for Torpedo
  else if(mode == 2) saucerCloseup->Draw(shadeMod, wire); //Draw just closeup for Saucer
}

//Draws a star
void drawStar()
{
  glBegin(GL_POINTS);
  glVertex3d(0.0,0.0,0.0);
  glEnd();
}

//Populates Star Field randomly via latitude&longitude
void drawStars(int n)
{
  srand(1);
  double rX;//Angle around X axis
  double rY;//Angle around Y axis
  float rC;//Color (0-1)

  //Used to correct rotation
  Vector3 resetYAxis;
    resetYAxis.setVector3(0.0,0.0,0.0);

  for(int x = 0; x < n; x++)
  {
    glPushMatrix();
    //Sets vector as 'y'
    resetYAxis.setVector3(0.0,1.0,0.0);
        rX = (180*(rand()/(double)RAND_MAX))-90; //Random x rotation
    rY = (180*(rand()/(double)RAND_MAX))-90; //Random y rotation
    rC = rand()/(float)RAND_MAX; //Random color
    glColor3f(rC,rC,rC);
    //Rotate y axis(latitude)
    glRotatef((float)rX, 1.0f, 0.0f, 0.0f);
    //Rotate the correction vector the opposite of what the matrix was just rotated,
    //effectively giving us the 'old' y
    resetYAxis.rotateMeVector3(1.0,0.0,0.0,-1*rX);
        //Rotate x axis(longitude) around 'old' y axis
    glRotatef((float)rY,0.0f,(float)resetYAxis.y,(float)resetYAxis.z);
    glTranslatef(0,0,-10);
        drawStar();
    glPopMatrix();
  }
}

//Draws a small dot at a point
void drawPoint(double x, double y, double z, double size)
{
  glPushMatrix();
  glTranslatef((float)x,(float)y,(float)z);
  gluSphere(gluNewQuadric(),0.05,10,10);
  glPopMatrix();
}

//Draws the xyz axis at current frame of reference
void drawAxis(double size)
{
  glPushMatrix();

  //z
  gluCylinder(gluNewQuadric(),0.01*size,0.01*size,1*size,10,1);

  //y
  glRotatef(-90, 1.0f, 0.0f, 0.0f);
  gluCylinder(gluNewQuadric(),0.01*size,0.01*size,1*size,10,1);

  //x
  glRotatef(90, 0.0f, 1.0f, 0.0f);
  gluCylinder(gluNewQuadric(),0.01*size,0.01*size,1*size,10,1);

  glPopMatrix();
}

//Called when mouse dragged (sets mouseX and mouseY from -1 to 1)
//(only needs to 'look' correct)
void MotionFunc(int x, int y)
{
  mouseX = -2.0*(x-(width/2.0))/width;
  mouseY = 2.0*(y-(height/2.0))/height;
}

//Called to update display
void DisplayFunc()
{
  //Clear screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  //Set camera to look relative to position of mouse on screen
  gluLookAt(0.0f,0.0f,-5.0f,mouseX*10,mouseY*10,-10.0f,0.0f,1.0f,0.0f);

  //Draw Stars
  drawStars(10000);

  //Aim Light
  GLfloat pos[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, pos);

  //Enable depth, lighting, and fog ONLY AFTER stars are drawn
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_FOG);

  //Deal with Ships
  if(!paused) updateShips();
  drawShips();

  /*
  glPushMatrix();
  glTranslated(0.0, 0.0, -20.0);
  drawAxis(10.0);
  glPopMatrix();
  */

  //Disable depth, lighting, and fog for stars to be drawn next time
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glDisable(GL_FOG);

  //DoubleBuffering
  glutSwapBuffers();
}

//Gets key input
//s- toggle Shading (smooth/flat)
//w- toggle Wire (wireframe/filled polys)
//p- pause/unpause
void KeyboardFunc(unsigned char key, int x, int y)
{
  switch(key)
  {
    case 's':
      shadeMod = (shadeMod - 1) * -1;
      break;
    case 'w':
      wire = (wire - 1) * -1;
      break;
    case 'p':
      paused = !paused;
      break;
  }
}

//Gets special keys (only utilized for F1)
void SpecialFunc(int key, int x, int y)
{
    if(key == GLUT_KEY_F1){
    //Switch mode between 0-Screen Saver, 1-Torpedo Closeup, 2-Saucer Closeup
        mode++;
    }
    if(mode > 2) mode = 0;
}

//Called on Window Resize
void ReshapeFunc(int w, int h)
{
  if (h <= 0)
    return;
  height = h;
  width = w;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0 , ((double) w) / ((double) h) , 1.0f , 1000.0);
  glViewport(0 , 0 , w , h);
}

//Inits Ships (duh). CALL THIS ONLY ONCE
void initShips()
{  
  //Specifically allocated for modes 2 & 3
  torpedoCloseup = new Torpedo();
  saucerCloseup = new Saucer();

  //Re-Used Vectors to be assigned to each ship
  Vector3 pos;
  Vector3 vel;
  Vector3 col;
  Vector3 scol;
  Vector3 rot;
  Vector3 initRot;
  initRot.setVector3(0.0,0.0,0.0);
  double r; //random rotation (also used to specify type)

  for(int n = 0; n < NUM_SHIPS; n++)
  {
    //Random position: -500 < x < 500; -500 < y < 500; -1000 < z < 200
    pos.setVector3(1000*(rand()/(float)RAND_MAX)-500,1000*(rand()/(float)RAND_MAX)-500,-1200*(rand()/(float)RAND_MAX)+200);
    //Random color: .3 < x(red) < .7; .3 < y(green) < .7; .3 < z(blue) < .7
    col.setVector3(((rand()/(float)RAND_MAX)*.7)+.3,((rand()/(float)RAND_MAX)*.7)+.3,((rand()/(float)RAND_MAX)*.7)+.3);
    //Random Secondary Color: (Same specs as color)
    scol.setVector3(((rand()/(float)RAND_MAX)*.7)+.3,((rand()/(float)RAND_MAX)*.7)+.3,((rand()/(float)RAND_MAX)*.7)+.3);

    //Random Velocity: 0 < z < 5; (x and y set to 0)
    vel.setVector3(0,0,5*(rand()/(float)RAND_MAX));

    //Random rotation constant between 0 and 20
    r = (rand()/(float)RAND_MAX)*20;

    //Chose type
    if((int)r%2 == 0)
    {
      //Type = TORPEDO
      sArray[n] = new Torpedo();
      ((Torpedo *)sArray[n])->SetSecondaryColor(scol);
      rot.setVector3(0.0,0.0,r);
    }
    else
    {
      //Type = SAUCER
      sArray[n] = new Saucer();
      rot.setVector3(0.0,r,0.0);
    }

    //Drunk Ship
    if(n%10 == 0) rot.setVector3(2*r/10,4*r/10,3*r/10);

    //Apply vectors to ship
    sArray[n]->SetType((int)r%2);
    sArray[n]->SetPosition(pos);
    sArray[n]->SetColor(col);
    sArray[n]->SetVelocity(vel);
    sArray[n]->SetRotation(initRot);
    sArray[n]->SetRotVel(rot);
  }

  //Set control vectors for closeups
  pos.setVector3(0.0, 0.0, -20.0);
  col.setVector3(0.3, 0.4, 0.5);
  scol.setVector3(0.5, 0.4, 0.3);
  vel.setVector3(0.0, 0.0, 0.0);
  rot.setVector3(0.2,0.3,0.4);

  //Setup closeup Torpedo
  torpedoCloseup->SetType(0);
  torpedoCloseup->SetPosition(pos);
  torpedoCloseup->SetColor(col);
  torpedoCloseup->SetSecondaryColor(scol);
  torpedoCloseup->SetVelocity(vel);
  torpedoCloseup->SetRotation(initRot);
  torpedoCloseup->SetRotVel(rot);

  //Setup closeup Saucer
  saucerCloseup->SetType(1);
  saucerCloseup->SetPosition(pos);
  saucerCloseup->SetColor(col);
  saucerCloseup->SetVelocity(vel);
  saucerCloseup->SetRotation(initRot);
  saucerCloseup->SetRotVel(rot);

  //Compile parts of necessary ships
  torpedoCloseup->Compile(0);
  torpedoCloseup->Compile(1);
  torpedoCloseup->Compile(2);
  saucerCloseup->Compile(3);
}

int main(int argc, char * argv[])
{
  //Set up Window
  glutInit(&argc , argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
  glutInitWindowPosition(0 , 0);
  glutInitWindowSize(width,height);
  glutCreateWindow("OpenGL Star Field");

  //One-Time setups
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_LIGHT0);
  glShadeModel(GL_FLAT);
  glEnable(GL_NORMALIZE);

  //Fog data
  float fogColor[] = { 0.0f, 0.0f, 0.0f, 1 };
  glFogfv(GL_FOG_COLOR, fogColor);
  glFogf(GL_FOG_START, 500);
  glFogf(GL_FOG_END, 1000);
  glFogf (GL_FOG_DENSITY, 0.9f);
  glHint (GL_FOG_HINT, GL_FASTEST);
  glFogi(GL_FOG_MODE, GL_LINEAR);

  //Callback Functions
  glutDisplayFunc(DisplayFunc);
  glutReshapeFunc(ReshapeFunc);
  glutIdleFunc(DisplayFunc);
  glutMotionFunc(MotionFunc);
  glutKeyboardFunc(KeyboardFunc);
  glutSpecialFunc(SpecialFunc);

  //Create ships to be used
  initShips();

  //Initiate program
  glutMainLoop();
  return 0;
}
