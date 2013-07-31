#ifndef Shape_h
#define Shape_h


#include "AbstractFramework.h"


class Shape
{
    public:
        static void setFramework( AbstractFramework* );

        virtual void draw() = 0;


    protected:
        static AbstractFramework* m_Framework;
};


#endif
