#include "Mesh.h"

Mesh::Mesh()
{

}

//Note: All normals are computed via the vector to generate the point itself. Given my method of
//placing these points, if there are no/few concave surfaces, the normals will look pretty darn
//good.
//...hey, in graphics, all that matters is that it LOOKS correct ;)
void Mesh::rotationMesh(int slices, int blocks)
{
  Vector3 copyVect;
  Vector3 rotVect;
  Vector3 norma;
  Vector3 normb;
  Vector3 normal;
  norma.setVector3(0.0, 1.0, 0.0);
  normb.setVector3(0.0, 1.0, 0.0);
  normal.setVector3(0.0, 1.0, 0.0);

  //Finds amount of rotation each slice should cover
  float sliceSize = (float)360/slices;

  for(int i = 0; i < slices; i++)
  {
    glPushMatrix();

    //Rotates to current slice
    glRotatef(i*sliceSize, 0.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLE_STRIP);
    //Places first point
    glNormal3d(0, 1, 0);
    glVertex3d(vertex[0].x, vertex[0].y, vertex[0].z);

    //Rotates one slice over,
    rotVect = vertex[0].rotateVector3(0.0, 1.0, 0.0, sliceSize);
    //Places jth point (same x,y data as previously place point)
    glNormal3d(0, 1, 0);
    glVertex3d(rotVect.x, rotVect.y, rotVect.z);

    //Places next point under initial point
    copyVect = vertex[0].rotateVector3(0.0, 1.0, 0.0, sliceSize);
    norma = (vertex[1]-vertex[0]).cross(copyVect-vertex[0]);
    copyVect = vertex[1].rotateVector3(0.0, 1.0, 0.0, sliceSize);
    normb = (vertex[2]-vertex[1]).cross(copyVect-vertex[1]);
    normal = norma.bisectOf(normb);
    normal.rotateMeVector3(0.0, 1.0, 0.0, -.5*sliceSize);
    glNormal3d(normal.x, normal.y, normal.z);
    glVertex3d(vertex[1].x, vertex[1].y, vertex[1].z);

    for(int j = 1; j < blocks; j++)
    {
      //Rotates one slice over,
      rotVect = vertex[j].rotateVector3(0.0, 1.0, 0.0, sliceSize);
      //Places jth point (same x,y data as previously place point)
      copyVect = vertex[j-1].rotateVector3(0.0, 1.0, 0.0, sliceSize);
      norma = (vertex[j]-vertex[j-1]).cross(copyVect-vertex[j-1]);
      copyVect = vertex[j].rotateVector3(0.0, 1.0, 0.0, sliceSize);
      normb = (vertex[j+1]-vertex[j]).cross(copyVect-vertex[j]);
      normal = norma.bisectOf(normb);
      normal.rotateMeVector3(0.0, 1.0, 0.0, -.5*sliceSize);
      glNormal3d(normal.x, normal.y, normal.z);
      glVertex3d(rotVect.x, rotVect.y, rotVect.z);

      //Places next point under initial point
      copyVect = vertex[j].rotateVector3(0.0, 1.0, 0.0, sliceSize);
      norma = (vertex[j+1]-vertex[j]).cross(copyVect-vertex[j]);
      copyVect = vertex[j+1].rotateVector3(0.0, 1.0, 0.0, sliceSize);
      normb = (vertex[j+2]-vertex[j+1]).cross(copyVect-vertex[j+1]);
      normal = norma.bisectOf(normb);
      normal.rotateMeVector3(0.0, 1.0, 0.0, -.5*sliceSize);
      glNormal3d(normal.x, normal.y, normal.z);
      glVertex3d(vertex[j+1].x, vertex[j+1].y, vertex[j+1].z);
    }
    //Places last point
    copyVect = vertex[blocks-1].rotateVector3(0.0, 1.0, 0.0, sliceSize);
    norma = (vertex[blocks]-vertex[0]).cross(copyVect-vertex[0]);
    copyVect = vertex[blocks].rotateVector3(0.0, 1.0, 0.0, sliceSize);
    normb = (vertex[blocks+1]-vertex[blocks]).cross(copyVect-vertex[blocks]);
    normal = norma.bisectOf(normb);
    normal.rotateMeVector3(0.0, 1.0, 0.0, -.5*sliceSize);
    glNormal3d(normal.x, normal.y, normal.z);
    glNormal3d(vertex[blocks].x, vertex[blocks].y, vertex[blocks].z);
    glVertex3d(vertex[blocks].x, vertex[blocks].y, vertex[blocks].z);

    glEnd();
    glPopMatrix();
  }
}
