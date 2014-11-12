#ifndef VECTOR3_H
#define VECTOR3_H
#include <math.h>

class Vector3
{
public:
  double x;
  double y;
  double z;
  Vector3();
  void setVector3(double x, double y, double z);

  //SELF OPERATIONS::
  //Rotate current vector about vector u,v,w
  void rotateMeVector3(double u, double v, double w, double angle);
  //Normalizes current vector
  void normalizeMeVector3();

  //CLONE OPERATIONS:: (DOES NOT CHANGE SELF'S VARIABLES)
  //Return instance of rotated current vector about vector u,v,w
  Vector3 rotateVector3(double u, double v, double w, double angle);
  //Return instance of normalized current vector
  Vector3 normalizeVector3();

  //Returns vector magnitude
  double getLength();

  //Returns a unit vector bisecting this vector and the one input
  Vector3 bisectOf(const Vector3 &that);

  //Returns a copy of this vector
  Vector3 copy();

  Vector3 cross(const Vector3 &that); //Cross Product
  //Overloaded Operators
  Vector3 operator+(const Vector3 &that);
  Vector3 operator-(const Vector3 &that);
  double operator*(const Vector3 &that);// Dot Product
  Vector3 operator*(int that);
  Vector3 operator*(double that);

protected:
  //Self explanitory conversions
  double degToRad(double deg);
  double radToDeg(double rad);
};

#endif
