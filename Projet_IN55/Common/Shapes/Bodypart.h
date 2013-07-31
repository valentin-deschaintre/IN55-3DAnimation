#ifndef BODYPART_H
#define BODYPART_H

#include "Shapes/Shape.h"
#include "vector3d.h"

class BodyPart : public Shape
{
public:
    BodyPart(Vector3D size, Vector3D angles, Vector3D relativePosition, BodyPart* parent, Vector3D localOrigin);
    Vector3D getAngles();
    Vector3D getRelativePosition();
    Vector3D getSize();
    Vector3D getLocalOrigin();
    Vector3D& getAnglesReference();
    Vector3D& getRelativePositionReference();
    Vector3D& getSizeReference();
    Vector3D& getLocalOriginReference();
    void draw();

protected:

private:
    Vector3D angles;
    BodyPart* parent;
    Vector3D relativePosition;
    Vector3D size;
    Vector3D localOrigin;


};

#endif // BODYPART_H
