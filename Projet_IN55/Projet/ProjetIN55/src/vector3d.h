#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

class Vector3D
{
public:

    /*---------------------------------- Constructor --------------------------------*/
    Vector3D () {}
    Vector3D (float X, float Y, float Z)
    {
        x = X; y = Y; z = Z;
    }
    /*---------------------------------- Operators ----------------------------------*/
    // Return himself
    operator Vector3D () const
    {
        return Vector3D(x, y, z);
    }
    // Add vector
    Vector3D operator + (Vector3D Vector)
    {
        return Vector3D (Vector.x + x, Vector.y + y, Vector.z + z);
    }
    // Subtract vectors
    Vector3D operator - (Vector3D Vector)
    {
        return Vector3D (x - Vector.x, y - Vector.y, z - Vector.z);
    }
    // "produit vectoriel"
    Vector3D operator ^(Vector3D Vector)
    {
        Vector3D vNormal;
        vNormal.x = ((y * Vector.z) - (z * Vector.y));
        vNormal.y = ((z * Vector.x) - (x * Vector.z));
        vNormal.z = ((x * Vector.y) - (y * Vector.x));
        return vNormal;
    }
    // Divide by a scalar
    Vector3D operator * (float num)
    {
        // Return the scaled vector
        return Vector3D(x * num, y * num, z * num);
    }
    // "produit scalaire"
    float operator * (Vector3D Vector)
    {
        return (x * Vector.x + y * Vector.y + z * Vector.z);
    }
    // Divide by a scalar
    Vector3D operator / (float num)
    {
        // Return the scale vector
        return Vector3D(x / num, y / num, z / num);
    }
    // = operator
    void operator = (Vector3D Vector)
    {
        x = Vector.x;
        y = Vector.y;
        z = Vector.z;
    }
    // == operator
    bool operator == (Vector3D Vector)
    {
        return (x == Vector.x && y == Vector.y && z == Vector.z);
    }
    // != operator
    bool operator != (Vector3D Vector)
    {
        return (x != Vector.x || y != Vector.y || z != Vector.z);
    }
    /*---------------------------------- Functions ----------------------------------*/
    // Work out the norm of our vector
    float Norm()
    {
        // Norme = sqrt(x^2 + y^2 + z^2)
        return (float)sqrt( Vector3D(x,y,z) * Vector3D(x,y,z) );
    }
    // Work out the vector normalized : Vector.norm() == 1
    Vector3D Normalize()
    {
        return (Vector3D(x,y,z) / Norm());
    }
    float x, y, z;
};

#endif // VECTOR3D_H
