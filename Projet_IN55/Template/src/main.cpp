//*****************************************************************************
//
// Program: IN55-TemplateTP (IN55)
// Author: Fabrice LAURI (fabrice.lauri@utbm.fr)
//          (Associate Professor at the
//          "Université de Technologie de Belfort-Montbéliard", France)
// Version: 1.0
// Last update: 2012-05-01
//
//*****************************************************************************


#include <Window.h>

#include "Shapes/Shape.h"


GLfloat angle1 = 0.0f;
GLfloat angle2 = 0.0f;

const GLfloat g_AngleSpeed = 10.0f;


Window::Window()
{
    setWindowTitle(trUtf8("IN55-Template"));
}

Window::~Window()
{
}


void
Window::initializeObjects()
{
    // Fond gris
    glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );

    // Chargement des shaders
    createShader( "Shaders/color" );

    // Initialisation des objets 3D avec le framework courant
    Shape::setFramework( this );

    // Initialisation des objets
}


void
Window::paintGL()
{
    // Nettoyage du Color Buffer et du Depth Buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Initialisation de la caméra
    lookAt( 0, 5, 20, 0, 0, 0 );

    // Rendu des objets
    pushMatrix();
        rotate( angle1, 0, 1, 0 );
        rotate( angle2, 0, 1, 0 );

        // Appel des méthodes draw des objets
    popMatrix();
}


void
Window::keyPressEvent( QKeyEvent* event )
{
    switch( event->key())
    {
        case Qt::Key_Escape:
            close();
            break;

        case Qt::Key_Left:
            angle1 -= g_AngleSpeed;
            break;

        case Qt::Key_Right:
            angle1 += g_AngleSpeed;
            break;

        case Qt::Key_Up:
            angle2 -= g_AngleSpeed;
            break;

        case Qt::Key_Down:
            angle2 += g_AngleSpeed;
            break;

        case Qt::Key_R:
            angle1 = angle2 = 0.0f;
            break;
    }
}
