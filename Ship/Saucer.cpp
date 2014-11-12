#import <OpenGL/OpenGL.h>
#import <GLUT/GLUT.h>
#include "Vector3.h"
#include "Ship.h"
#include "Saucer.h"
#include "Mesh.h"

Saucer::Saucer()
{

}

void Saucer::Compile(int ship)
{
  if(ship == 3)
  {
    Mesh sauce;
    //Setting arbitrary points- running out of time because I'm an idiot :(
    sauce.vertex[0].x = 0.0;
    sauce.vertex[0].y = 8.0;
    sauce.vertex[0].z = 0.0;

    sauce.vertex[1].x = 1.0;
    sauce.vertex[1].y = 7.0;
    sauce.vertex[1].z = 0.0;

    sauce.vertex[2].x = 2.0;
    sauce.vertex[2].y = 6.0;
    sauce.vertex[2].z = 0.0;

    sauce.vertex[3].x = 3.0;
    sauce.vertex[3].y = 5.0;
    sauce.vertex[3].z = 0.0;

    sauce.vertex[4].x = 4.0;
    sauce.vertex[4].y = 4.0;
    sauce.vertex[4].z = 0.0;

    sauce.vertex[5].x = 5.0;
    sauce.vertex[5].y = 3.0;
    sauce.vertex[5].z = 0.0;

    sauce.vertex[6].x = 6.0;
    sauce.vertex[6].y = 2.0;
    sauce.vertex[6].z = 0.0;

    sauce.vertex[7].x = 7.0;
    sauce.vertex[7].y = 1.0;
    sauce.vertex[7].z = 0.0;

    sauce.vertex[8].x = 8.0;
    sauce.vertex[8].y = 0.0;
    sauce.vertex[8].z = 0.0;

    sauce.vertex[9].x = 7.0;
    sauce.vertex[9].y = -1.0;
    sauce.vertex[9].z = 0.0;

    sauce.vertex[10].x = 6.0;
    sauce.vertex[10].y = -2.0;
    sauce.vertex[10].z = 0.0;

    sauce.vertex[11].x = 5.0;
    sauce.vertex[11].y = -3.0;
    sauce.vertex[11].z = 0.0;

    sauce.vertex[12].x = 4.0;
    sauce.vertex[12].y = -4.0;
    sauce.vertex[12].z = 0.0;

    sauce.vertex[13].x = 3.0;
    sauce.vertex[13].y = -5.0;
    sauce.vertex[13].z = 0.0;

    sauce.vertex[14].x = 2.0;
    sauce.vertex[14].y = -6.0;
    sauce.vertex[14].z = 0.0;

    sauce.vertex[15].x = 1.0;
    sauce.vertex[15].y = -7.0;
    sauce.vertex[15].z = 0.0;

    sauce.vertex[16].x = 0.0;
    sauce.vertex[16].y = -8.0;
    sauce.vertex[16].z = 0.0;


    glNewList(shipList+ship, GL_COMPILE);
    sauce.rotationMesh(20,20);
    glEndList();
  }

}

void Saucer::Draw(int shadeMode, int wire)
{
  if(shadeMode == SMOOTH) glShadeModel(GL_SMOOTH);
  else glShadeModel(GL_FLAT);
  if(wire == WIRE) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  //Move to ships position/rotation to begin drawing
  glPushMatrix();

  glTranslated(position.x, position.y, position.z);
  glRotated((GLdouble)rotation.x, 1.0, 0.0, 0.0);
  glRotated((GLdouble)rotation.y, 0.0, 1.0, 0.0);
  glRotated((GLdouble)rotation.z, 0.0, 0.0, 1.0);

  //Set Color & Draw Body
  glMaterialf(GL_FRONT, GL_SHININESS, 200.0f);
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glCallList(shipList+3);

  glPopMatrix();
}
