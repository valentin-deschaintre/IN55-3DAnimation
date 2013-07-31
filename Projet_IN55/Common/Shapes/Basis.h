#ifndef Basis_h
#define Basis_h


#include "Shapes/Shape.h"


class Basis : public Shape
{
    public:
        Basis( GLfloat length );

        void draw();


    protected:
        GLfloat m_TabVertices[6*3];
};


#endif
