//
//  Torpedo.cpp
//  Ship
//
//  Created by Philip Dougherty on 10/8/11.
//  Copyright 2011 UW Madison. All rights reserved.
//
#import <OpenGL/OpenGL.h>
#import <GLUT/GLUT.h>
#include "Vector3.h"
#include "Ship.h"
#include "Torpedo.h"

Torpedo::Torpedo()
{

}

void Torpedo::SetSecondaryColor(const Vector3 & newColor)
{
  //Sets ambient and Diffuse amounts on set
  secondaryColor.x = newColor.x;
  secondaryColor.y = newColor.y;
  secondaryColor.z = newColor.z;
  secondarySpecular[0] = 0.6f;
  secondarySpecular[1] = 0.6f;
  secondarySpecular[2] = 0.6f;
  secondarySpecular[3] = 1.0f;
  secondaryAmbient[0] = (float)secondaryColor.x;
  secondaryAmbient[1] = (float)secondaryColor.y;
  secondaryAmbient[2] = (float)secondaryColor.z;
  secondaryAmbient[3] = 1.0f;
  secondaryDiffuse[0] = (float)secondaryColor.x;
  secondaryDiffuse[1] = (float)secondaryColor.y;
  secondaryDiffuse[2] = (float)secondaryColor.z;
  secondaryDiffuse[3] = 1.0f;
  silver[0] = .7f;
  silver[1] = .7f;
  silver[2] = .7f;
  silver[3] = 1.0f;
}

Vector3 Torpedo::GetSecondaryColor()
{
  return secondaryColor;
}

void Torpedo::Compile(int ship)
{
  if(ship == 0)
  {
    //Draw Body
    glNewList(shipList+ship, GL_COMPILE);
    glPushMatrix();
    glScalef(0.1f,0.1f,1.0f);
    gluSphere(gluNewQuadric(), 5, 40, 40);
    glPopMatrix();
    glEndList();
  }

  else if(ship == 1)
  {
    //Draw Ring
    glNewList(shipList+ship, GL_COMPILE);
    glPushMatrix();
    glTranslated(0.0, 0.0, -3.0);
    glutSolidTorus(.5, 5, 30, 80);
    glPopMatrix();
    glEndList();
  }

  else if(ship == 2)
  {
    //Draw Spokes
    glNewList(shipList+ship, GL_COMPILE);
    glPushMatrix();
    glTranslated(0.0, 0.0, -3.0);
    glRotated(90.0, 1.0, 0.0, 0.0);
    glScalef(.5f, .9f, 1.0f);
    gluCylinder(gluNewQuadric(), .5, .5, 5, 40, 40);
    glPopMatrix();
    glEndList();
  }
}

void Torpedo::Draw(int shadeMode, int wire)
{

  if(shadeMode == SMOOTH) glShadeModel(GL_SMOOTH);
  else glShadeModel(GL_FLAT);
  if(wire == WIRE) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else glPolygonMode(GL_FRONT, GL_FILL);

  //Move to ships position/rotation to begin drawing
  glPushMatrix();

  glTranslated(position.x, position.y, position.z);
  glRotated((GLdouble)rotation.x, 1.0, 0.0, 0.0);
  glRotated((GLdouble)rotation.y, 0.0, 1.0, 0.0);
  glRotated((GLdouble)rotation.z, 0.0, 0.0, 1.0);

  //Draw Body
  glMaterialf(GL_FRONT, GL_SHININESS, 200.0f);
  glMaterialfv(GL_FRONT, GL_AMBIENT, silver);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, silver);
  glMaterialfv(GL_FRONT, GL_SPECULAR, silver);
  glCallList(shipList+type);

  //Draw Ring
  glMaterialf(GL_FRONT, GL_SHININESS, 200.0f);
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glCallList(shipList+type+1);

  //Draw Spokes
  glMaterialf(GL_FRONT, GL_SHININESS, 20.0f);
  glMaterialfv(GL_FRONT, GL_AMBIENT, secondaryAmbient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, secondaryDiffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, secondarySpecular);
  glPushMatrix();
  glCallList(shipList+type+2);
  glRotatef(120.0f, 0.0f, 0.0f, 1.0f);
  glCallList(shipList+type+2);
  glRotatef(120.0f, 0.0f, 0.0f, 1.0f);
  glCallList(shipList+type+2);
  glPopMatrix();

  glPopMatrix();
}
