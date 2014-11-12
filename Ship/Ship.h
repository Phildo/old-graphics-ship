#ifndef SHIP_H
#define SHIP_H
#include "Vector3.h"

/*
Based off Perry Kivolowitz's Skeleton
*/

enum {TORPEDO, SAUCER}; //For ease w/ 'SetType()'
enum {FILLED, WIRE};    //'' '' '' '' 'DisplayType()'
enum {FLAT, SMOOTH};    //'' '' '' '' 'ShadingType()'

class Ship
{
  public:
  Ship();

  //Sets variables in how the ship is displayed. Getters unnecessary.
  void SetType(int t);

  void SetPosition(const Vector3 & newPosition);
  Vector3 GetPosition();

  void SetVelocity(const Vector3 & newVelocity);
  Vector3 GetVelocity();

  void SetRotation(const Vector3 & newRotation);
  Vector3 GetRotation();

  void SetRotVel(const Vector3 & newRotVel);
  Vector3 GetRotVel();

  void SetColor(const Vector3 & newColor);
  Vector3 GetColor();

  //Updates variables used in determining display of ship based on time elapsed
  void UpdatePosition(double elapsedTime); //NOTE: DOES NOT DRAW. ONLY UPDATES DATA.

  //Compiles ship into memory for quick recall later
  virtual void Compile(int ship);

  //Calls ship instance to be drawn *REQUIRES Compile() TO BE CALLED FIRST
  virtual void Draw(int shadeMode, int wire);

  protected:
  static GLuint shipList;
  static bool first;
  Vector3 position;
  Vector3 velocity;
  Vector3 rotation;
  Vector3 rotVel;
  Vector3 color;
  GLfloat specular[4];
  GLfloat ambient[4];
  GLfloat diffuse[4];
  int type;
};

#endif
