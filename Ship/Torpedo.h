#include "Ship.h"

class Torpedo: public Ship
{
public:
  Torpedo();

  //Getter & Setter for secondaryColor
  void SetSecondaryColor(const Vector3 & newColor);
  Vector3 GetSecondaryColor();

  virtual void Compile(int ship);
  virtual void Draw(int shadeMode, int wire);

protected:
  //Used for spokes
  Vector3 secondaryColor;
  GLfloat secondarySpecular[4];
  GLfloat secondaryAmbient[4];
  GLfloat secondaryDiffuse[4];
  GLfloat silver[4];
};
