//
//  Mesh.h
//  Ship
//
//  Created by Philip Dougherty on 10/12/11.
//  Copyright 2011 UW Madison. All rights reserved.
//
#ifndef MESH_H
#define MESH_H

#import <OpenGL/OpenGL.h>
#import <GLUT/GLUT.h>
#include <cstdlib>
#include <math.h>
#include <iostream>
#include "Vector3.h"

class Mesh
{
public:
  Vector3 vertex[50];
  Mesh();
  //Uses the first [blocks] entries in 'vertex' to construct a mesh rotated around 0,1,0 with [slices] slices
  void rotationMesh(int slices, int blocks);
};
#endif
