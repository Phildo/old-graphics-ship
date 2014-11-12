//
//  Saucer.h
//  Ship
//
//  Created by Philip Dougherty on 10/8/11.
//  Copyright 2011 UW Madison. All rights reserved.
//
#include "Ship.h"

class Saucer: public Ship
{
public:
  Saucer();
  virtual void Compile(int ship);
  virtual void Draw(int shadeMode, int wire);
};
