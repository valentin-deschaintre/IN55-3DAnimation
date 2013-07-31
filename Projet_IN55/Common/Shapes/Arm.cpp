#include "Arm.h"
#include "MemDefns.h"
#include <math.h>

    Arm::Arm()
    {
    }

    void Arm::draw(){
        if (m_Framework->useShader( "color" )){
            //Bras
            m_Framework->pushMatrix();
            m_Framework->rotate( -30 , 0.0f, 0.0f, 1.0f );
            m_Framework->scale( 1.0f, 4.0f, 1.0f );
            m_Cube.draw();

            //avant-bras
            m_Framework->scale( 1.0f, 1.0f, 1.0f );
            m_Framework->translate(1.0f,4.0f,1.0f);
            //m_Framework->rotate( 30 , 0.0f, 0.0f, 1.0f );
            m_Framework->scale( 1.0f, 3.0f, 1.0f );
            m_Cube.draw();
            m_Framework->popMatrix();

        }
    }

