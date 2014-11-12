#include "Vector3.h"
#import <math.h>

Vector3::Vector3()
{
}

void Vector3::setVector3(double x, double y, double z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

void Vector3::rotateMeVector3(double u, double v, double w, double angle)
{
  Vector3 about;
  about.setVector3(u, v, w);
  about.normalizeVector3();

  //Math from www/blitzmax.com/Community/posts.php?topic=57616 posted by user "JoshK"
  double dotProd = copy() * about;
  double rad = degToRad(angle);
  this->x = (u * dotProd) + (((x*((v*v)+(w*w)))-(u*((v*y)+(w*z))))*(cos(rad))) + (((-1*w*y)+(v*z))*(sin(rad)));
  this->y = (v * dotProd) + (((y*((u*u)+(w*w)))-(v*((u*x)+(w*z))))*(cos(rad))) + (((w*x)-(u*z))*(sin(rad)));
  this->z = (w * dotProd) + (((z*((u*u)+(v*v)))-(w*((u*x)+(v*y))))*(cos(rad))) + (((-1*v*x)+(u*y))*(sin(rad)));
}

void Vector3::normalizeMeVector3()
{
  double length = getLength();
  x/=length;
  y/=length;
  z/=length;
}

Vector3 Vector3::rotateVector3(double u, double v, double w, double angle)
{
  Vector3 copy = this->copy();
  copy.rotateMeVector3(u,v,w,angle);
  return copy;
}

Vector3 Vector3::normalizeVector3()
{
  Vector3 copy = this->copy();
  copy.normalizeMeVector3();
  return copy;
}

double Vector3::getLength()
{
  return sqrt((x*x) + (y*y) + (z*z));
}

Vector3 Vector3::bisectOf(const Vector3 &that)
{
  Vector3 copy = this->copy();
  Vector3 copy2;
  Vector3 bi;
  copy2.x = that.x;
  copy2.y = that.y;
  copy2.z = that.z;
  copy.normalizeVector3();
  copy2.normalizeVector3();
  bi = copy+copy2;
  bi.normalizeVector3();
  return bi;
}

Vector3 Vector3::copy()
{
  Vector3 copy;
  copy.setVector3(x, y, z);
  return copy;
}

Vector3 Vector3::cross(const Vector3 &that)
{
  Vector3 cross = this->copy();
  cross.x = (cross.y*that.z) - (cross.z*that.y);
  cross.y = -1*((cross.x*that.z)-(cross.z*that.x));
  cross.z = (cross.x*that.y) - (cross.y*that.x);
  return cross;
}

//Overloaded Operators
Vector3 Vector3::operator+(const Vector3 &that)
{
  Vector3 sum;
  sum.setVector3(x+that.x, y+that.y, z+that.z);
  return sum;
}

Vector3 Vector3::operator-(const Vector3 &that)
{
  Vector3 sum;
  sum.setVector3(x-that.x, y-that.y, z-that.z);
  return sum;
}

//DOT product
double Vector3::operator*(const Vector3 &that)
{
  return ((x*that.x) + (y*that.y) + (z*that.z));
}

Vector3 Vector3::operator*(int that)
{
  Vector3 prod;
  prod.setVector3(x*that, y*that, z*that);
  return prod;
}

Vector3 Vector3::operator*(double that)
{
  Vector3 prod;
  prod.setVector3(x*that, y*that, z*that);
  return prod;
}

//Helpers
double Vector3::degToRad(double deg)
{
  return (deg*3.14159265/180);
}

double Vector3::radToDeg(double rad)
{
  return (rad*180/3.14159265);
}
