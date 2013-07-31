#ifndef AbstractFramework_h
#define AbstractFramework_h


#include <GL/glew.h>


class AbstractFramework
{
    public:
        virtual bool useShader( GLuint shader_id ) = 0;
        virtual bool useShader( const char* shader_name ) = 0;

        virtual GLuint getCurrentShaderId() const = 0;

        virtual void transmitMVP() = 0;
        virtual void transmitMV() = 0;

        virtual void pushMatrix() = 0;
        virtual void popMatrix() = 0;

        virtual void loadIdentity() = 0;

        virtual void translate(GLfloat x, GLfloat y, GLfloat z) = 0;

        virtual void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) = 0;

        virtual void scale(GLfloat x, GLfloat y, GLfloat z) = 0;
};


#endif
