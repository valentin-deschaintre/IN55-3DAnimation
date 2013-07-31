#include "Camera.h"

Camera::Camera(Window* pcl_GLFramework)
{
    pcl_Framework = pcl_GLFramework;
    lock = false;
    speed = 0.5f;
    angleSpeed = 6.0f;

    baseI = Vector3d(1.0,0.0,0.0);
    baseJ = Vector3d(0.0,1.0,0.0);
    baseK = Vector3d(0.0,0.0,1.0);

    position = Vector3d(0.0,5.0,-20.0);

    look();
}

void
Camera::look()
{
    regard = position + baseK;
    pcl_Framework->lookAt( position.x,position.y,position.z,
                           regard.x,regard.y,regard.z);
}

void
Camera::up()
{
    position.y += speed;
    regard.y += speed;
}

void
Camera::down()
{
    position.y -= speed;
    regard.y -= speed;
}

void
Camera::lookLeft()
{
    rote(-angleSpeed,true);
}

void
Camera::lookRight()
{
    rote(angleSpeed,true);
}

void
Camera::lookUp()
{
    if (baseK.y<0.70) {
        rote(angleSpeed,false);
    }
}

void
Camera::lookDown()
{
    if (baseK.y>-0.70) {
        rote(-angleSpeed,false);
    }
}

void
Camera::goLeft()
{
    position.x += speed * baseI.x;
    regard.x   += speed * baseI.x;
    position.z += speed * baseI.z;
    regard.z   += speed * baseI.z;
}

void
Camera::goRight()
{
    position.x -= speed * baseI.x;
    regard.x   -= speed * baseI.x;
    position.z -= speed * baseI.z;
    regard.z   -= speed * baseI.z;
}

void
Camera::goForward()
{
    position.x += speed * baseK.x;
    regard.x   += speed * baseK.x;
    position.z += speed * baseK.z;
    regard.z   += speed * baseK.z;
}

void
Camera::goBack()
{
    position.x -= speed * baseK.x;
    regard.x   -= speed * baseK.x;
    position.z -= speed * baseK.z;
    regard.z   -= speed * baseK.z;
}

void
Camera::rote(float angle, bool horizontal)
{
    glm::vec3 o = glm::vec3(0,0,0);
    float ux = baseI.x;
    float uy = baseI.y;
    float uz = baseI.z;

    if (horizontal)
    {
        ux = 0;
        uy = 1;
        uz = 0;
    }

    float norme = sqrt ( ux*ux + uy*uy + uz*uz );

    if (norme != 0)
    {
        ux/=norme;
        uy/=norme;
        uz/=norme;

        float c = cos(angle/180*M_PI);
        float s = sin(angle/180*M_PI);

        glm::mat4 rot
                (
                    ux*ux+(1-ux*ux)*c   ,ux*uy*(1-c)-uz*s   ,ux*uz*(1-c)+uy*s   ,0,
                    ux*uy*(1-c)+uz*s    ,uy*uy+(1-uy*uy)*c  ,uy*uz*(1-c)-ux*s   ,0,
                    ux*uz*(1-c)-uy*s    ,uy*uz*(1-c)+ux*s   ,uz*uz+(1-uz*uz)*c  ,0,
                    0                   ,0                  ,0                  ,1
                );

        glm::vec4 baseK4(baseK.x,baseK.y,baseK.z,1.0f);
        baseK4 = rot * baseK4;
        baseK.x = baseK4.x;
        baseK.y = baseK4.y;
        baseK.z = baseK4.z;

        glm::vec4 baseI4(baseI.x,baseI.y,baseI.z,1.0f);
        baseI4 = rot * baseI4;
        baseI.x = baseI4.x;
        baseI.y = baseI4.y;
        baseI.z = baseI4.z;

        glm::vec4 baseJ4(baseJ.x,baseJ.y,baseJ.z,1.0f);
        baseJ4 = rot * baseJ4;
        baseJ.x = baseJ4.x;
        baseJ.y = baseJ4.y;
        baseJ.z = baseJ4.z;
    }
    else
    {
        printf("Norme nulle\n");
    }
}

void
Camera::changeLock()
{
    lock = !lock;
}

bool
Camera::isLocked()
{
    return lock;
}
