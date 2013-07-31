//*****************************************************************************
//
// Class: Basis
// Author: Fabrice LAURI (fabrice.lauri@utbm.fr)
//         (Associate Professor at the
//          "Université de Technologie de Belfort-Montbéliard", France)
// Version: 1.0
// Last update: 2012-05-01
//
//*****************************************************************************


#include "Shapes/Basis.h"


GLfloat g_TabColors[] =
{
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f
};


Basis::Basis( GLfloat length )
{
    for( GLuint i = 0; i < 6*3; ++i )
    {
        m_TabVertices[i] = 0.0f;
    }

    m_TabVertices[3] = length;
    m_TabVertices[10] = length;
    m_TabVertices[17] = length;
}


void
Basis::draw()
{
    m_Framework->useShader( "color" );
    m_Framework->transmitMVP();

    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, m_TabVertices );
    glEnableVertexAttribArray( 1 );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, g_TabColors );
    glDrawArrays( GL_LINES, 0, 6 );
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
}
