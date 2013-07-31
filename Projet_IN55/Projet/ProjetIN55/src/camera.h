#ifndef CAMERA_H
#define CAMERA_H

#include "Includes.h"
#include "Window.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    Camera(Window* pcl_GLFramework);
    void look();

    void up();
    void down();
    void lookLeft();
    void lookRight();
    void lookUp();
    void lookDown();
    void goLeft();
    void goRight();
    void goForward();
    void goBack();

    void rote(float angle, bool horizontal);
    void changeLock();
    bool isLocked();

protected:
    Window* pcl_Framework;
    bool lock;
    float speed;
    float angleSpeed;
    Vector3d position;
    Vector3d regard;
    Vector3d baseI;
    Vector3d baseJ;
    Vector3d baseK;
};

#endif // CAMERA_H
