/*
Implementation based on Perry Kivolowit's Skeleton Code
*/
#import <OpenGL/OpenGL.h>
#import <GLUT/GLUT.h>
#include "Vector3.h"
#include "Ship.h"

bool Ship::first = true;
GLuint Ship::shipList;

Ship::Ship()
{
  //Used to instantiate the one-time-only DisplayList for ALL ships
  if(first) {
    shipList = glGenLists(3);
    first = false;
  }
}

void Ship::SetType(int t){
  //0- Torpedo
  //1- Saucer
  type = t;
}

void Ship::SetPosition(const Vector3 & newPosition)
{
  position.x = newPosition.x;
  position.y = newPosition.y;
  position.z = newPosition.z;
}

Vector3 Ship::GetPosition()
{
  return position;
}

void Ship::SetVelocity(const Vector3 & newVelocity)
{
  velocity.x = newVelocity.x;
  velocity.y = newVelocity.y;
  velocity.z = newVelocity.z;
}

Vector3 Ship::GetVelocity()
{
  return velocity;
}

void Ship::SetRotation(const Vector3 & newRotation)
{
  rotation.x = newRotation.x;
  rotation.y = newRotation.y;
  rotation.z = newRotation.z;
}

Vector3 Ship::GetRotation()
{
  return rotation;
}

void Ship::SetRotVel(const Vector3 & newRotVel)
{
  rotVel.x = newRotVel.x;
  rotVel.y = newRotVel.y;
  rotVel.z = newRotVel.z;
}

Vector3 Ship::GetRotVel()
{
  return rotVel;
}

void Ship::SetColor(const Vector3 & newColor)
{
  //Sets specular, ambient, and diffuse
  color.x = newColor.x;
  color.y = newColor.y;
  color.z = newColor.z;
  specular[0] = 0.6f;
  specular[1] = 0.6f;
  specular[2] = 0.6f;
  specular[3] = 1.0f;
  ambient[0] = (float)color.x;
  ambient[1] = (float)color.y;
  ambient[2] = (float)color.z;
  ambient[3] = 1.0f;
  diffuse[0] = (float)color.x;
  diffuse[1] = (float)color.y;
  diffuse[2] = (float)color.z;
  diffuse[3] = 1.0f;
}

Vector3 Ship::GetColor()
{
  return color;
}

void Ship::UpdatePosition(double elapsedTime)
{
  //Uses overloaded operators to update position and rotation
  position = position + velocity * elapsedTime;
  rotation = rotation + rotVel * elapsedTime;
  if(position.z > 200) position.z = -1000;
}

//To be overloaded by children- Draws the ship and puts code in memory via DisplayList 'shipList'
void Ship::Compile(int ship)
{
  return;
}

//To be overloaded by children- Goes to ships position/rotation, sets color, and draws ship
void Ship::Draw(int shadeMode, int wire)
{
  return;
}

