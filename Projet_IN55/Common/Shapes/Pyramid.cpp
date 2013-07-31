//*****************************************************************************
//
// Class: Pyramid
// Author: Fabrice LAURI (fabrice.lauri@utbm.fr)
//         (Associate Professor at the
//          "Universit� de Technologie de Belfort-Montb�liard", France)
// Version: 1.0
// Last update: 2012-05-01
//
//*****************************************************************************


#include "Shapes/Pyramid.h"


Pyramid::Pyramid( int basis_nbr_edges, GLfloat radius, GLfloat y_high ) : ParametricShape( basis_nbr_edges+2 )
{
    m_BasisNbrEdges = basis_nbr_edges;


    // G�n�ration des vertices de la base
    generatePointsOnCircle( 0, 1, basis_nbr_edges, radius, 0.0f, 0.0f, true );
    // G�n�ration du sommet de la pyramide
    initVertex( basis_nbr_edges+1, 0.0f, y_high, 0.0f );


    // G�n�ration des couleurs de la base
    generateColors( 0, basis_nbr_edges+1, 1.0f, 0.0f, 0.0f );
    // G�n�ration de la couleur du sommet de la pyramide
    generateColors( basis_nbr_edges+1, 1, 0.0f, 0.0f, 1.0f );


    // G�n�ration des indices pour construire la base de la pyramide
    createTabIndices( m_TabBasisIndices, m_BasisNbrEdges+2 );
    generateCircleIndices( m_TabBasisIndices, 0, 1, 1, basis_nbr_edges );
    // G�n�ration des indices pour construire le chapeau de la pyramide
    createTabIndices( m_TabHatIndices, m_BasisNbrEdges+2 );
    generateCircleIndices( m_TabHatIndices, m_BasisNbrEdges+1, 1, 1, basis_nbr_edges );
}


void Pyramid::draw()
{
    if (m_Framework->useShader( "color" ))
    {
        m_Framework->transmitMVP();

        glEnableVertexAttribArray( 0 );
        glEnableVertexAttribArray( 1 );
        initArrays();
        glDrawElements( GL_TRIANGLE_FAN, m_BasisNbrEdges+2, GL_UNSIGNED_INT, m_TabBasisIndices );
        glDrawElements( GL_TRIANGLE_FAN, m_BasisNbrEdges+2, GL_UNSIGNED_INT, m_TabHatIndices );
        glDisableVertexAttribArray( 0 );
        glDisableVertexAttribArray( 1 );
    }
}
