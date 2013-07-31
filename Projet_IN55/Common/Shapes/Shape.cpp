//*****************************************************************************
//
// Class: Shape
// Author: Fabrice LAURI (fabrice.lauri@utbm.fr)
//         (Associate Professor at the
//          "Universit� de Technologie de Belfort-Montb�liard", France)
// Version: 1.0
// Last update: 2012-05-01
//
//*****************************************************************************


#include "Shapes/Shape.h"


AbstractFramework* Shape::m_Framework = NULL;


void
Shape::setFramework( AbstractFramework* fw )
{
    m_Framework = fw;
}
