#include <Window.h>

#include "Shapes/Bodypart.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include "glm-0.9.4.4/glm/glm.hpp"

using namespace std;

GLfloat angle1 = 30.0f;
GLfloat angle2 = 0.0f;
GLfloat distY = 0.0f;
GLuint action = 0;
glm::vec2 currentRotation = glm::vec2(0);


glm::vec4 lookPoint = glm::vec4(0.0,0.0,0.0,1.0);
glm::vec4 globalPosition = glm::vec4(0.0,0.0,50.0,1.0);

GLfloat camX = 0;
GLfloat camY = 0;
const GLfloat g_AngleSpeed = 10.0f;

//BodyPart(glm::vec3 size, glm::vec3 angles, glm::vec3 relativePosition, BodyPart* parent, glm::vec3 localOrigin);
//Torse
BodyPart torso = BodyPart(glm::vec3(3.5,8,2),glm::vec3(0,0,0),glm::vec3(0,0,0),NULL, glm::vec3(1.75,4,1));

//Head
BodyPart head = BodyPart(glm::vec3(2,2,2),glm::vec3(0,0,0),glm::vec3(0,4.3,0),&torso, glm::vec3(1,0,1));

//bras gauche
BodyPart leftArm = BodyPart(glm::vec3(1,4.5,1),glm::vec3(20,0,0),glm::vec3(-2.4,3.5,0), &torso,glm::vec3(0.5,4.5,0.5));
BodyPart leftForeArm = BodyPart(glm::vec3(0.9,4.3,0.9),glm::vec3(20,0,0),glm::vec3(0,-4.5,0), &leftArm,glm::vec3(0.45,4.3,0.45));
BodyPart leftHand = BodyPart(glm::vec3(0.4,1.5,1.2),glm::vec3(0,0,0),glm::vec3(0,-4.3,0), &leftArm,glm::vec3(0.2,1.5,0.6));

//bras droit
BodyPart rightArm = BodyPart(glm::vec3(1,4.5,1),glm::vec3(-20,0,0),glm::vec3(2.4,3.5,0), &torso,glm::vec3(0.5,4.5,0.5));
BodyPart rightForeArm = BodyPart(glm::vec3(0.9,4.3,0.9),glm::vec3(20,0,0),glm::vec3(0,-4.5,0), &rightArm,glm::vec3(0.45,4.3,0.45));
BodyPart rightHand = BodyPart(glm::vec3(0.4,1.5,1.2),glm::vec3(0,0,0),glm::vec3(0,-4.3,0), &leftArm,glm::vec3(0.2,1.5,0.6));

//jambe gauche
BodyPart leftThigh = BodyPart(glm::vec3(1.5,5.5,1.5),glm::vec3(20,0,0),glm::vec3(-0.8,-4,0), &torso,glm::vec3(0.75,5.5,0.75));
BodyPart leftCalf = BodyPart(glm::vec3(1.3,4.5,1.3),glm::vec3(-20,0,0),glm::vec3(0,-5.5,0), &leftThigh,glm::vec3(0.65,4.5,0.65));
BodyPart leftFoot = BodyPart(glm::vec3(1.4,0.5,2.5),glm::vec3(0,0,0),glm::vec3(0,-4.5,0), &leftThigh,glm::vec3(0.7,0.5,2.5-0.65));

//jambe droite
BodyPart rightThigh = BodyPart(glm::vec3(1.5,5.5,1.5),glm::vec3(-20,0,0),glm::vec3(0.8,-4,0), &torso,glm::vec3(0.75,5.5,0.75));
BodyPart rightCalf = BodyPart(glm::vec3(1.3,4.5,1.3),glm::vec3(-20,0,0),glm::vec3(0,-5.5,0), &rightThigh,glm::vec3(0.65,4.5,0.65));
BodyPart rightFoot = BodyPart(glm::vec3(1.4,0.5,2.5),glm::vec3(0,0,0),glm::vec3(0,-4.5,0), &leftThigh,glm::vec3(0.7,0.5,2.5-0.65));

Window::Window()
{
    setWindowTitle(trUtf8("ProjetIN55"));
}

Window::~Window()
{
}

void
Window::initializeObjects()
{
    // Initialisation des objets 3D avec le framework courant
    Shape::setFramework( this );

    glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );

    // Chargement des shaders
    createShader( "Shaders/color" );
    createShader( "Shaders/texture" );

    const int NBR_TEXTURES = 4;
    GLuint texId[NBR_TEXTURES];
    glGenTextures(NBR_TEXTURES,texId);

    QImage texture;
    texture.load("img/sol.jpg");
    QImage img = QGLWidget::convertToGLFormat( texture );

    QImage texture1;
    texture1.load("img/bois.jpg");
    QImage img1 = QGLWidget::convertToGLFormat( texture1 );

    QImage texture2;
    texture2.load("img/imm.jpg");
    QImage img2 = QGLWidget::convertToGLFormat( texture2 );

    QImage texture3;
    texture3.load("img/sky.jpg");
    QImage img3 = QGLWidget::convertToGLFormat( texture3 );

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texId[0]);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, texture.width(), texture.height(), 0,
    GL_RGBA, GL_UNSIGNED_BYTE, img.bits() );

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texId[1]);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, texture1.width(), texture1.height(), 0,
    GL_RGBA, GL_UNSIGNED_BYTE, img1.bits() );

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, texId[2]);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, texture2.width(), texture2.height(), 0,
    GL_RGBA, GL_UNSIGNED_BYTE, img2.bits() );

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, texId[3]);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, texture3.width(), texture3.height(), 0,
    GL_RGBA, GL_UNSIGNED_BYTE, img3.bits() );
}

void
Window::paintGL()
{
    //setMouseTracking(true);
    // Nettoyage du Color Buffer et du Depth Buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Rendu des objets
    pushMatrix();
	rotate( angle1, 0, 1, 0 );
	rotate( angle2, 1, 0, 0 );

	useShader("texture");
	transmitMVP();

	lookAt( globalPosition.x, globalPosition.y, globalPosition.z, lookPoint.x, lookPoint.y, lookPoint.z);

	drawSol();
	drawImm();

	if(action == 1){
		walk();
	} else if(action == 2){
		run();
	} else if(action == 3){
		jump();
	}

    paintMan();
	popMatrix();
}

void Window::paintMan(){
    torso.draw();
    //tête
    pushMatrix();
    head.draw();
    popMatrix();
    //Bras1
    pushMatrix();
    leftArm.draw();
    leftForeArm.draw();
    leftHand.draw();
    popMatrix();
    //Bras2
    pushMatrix();
    rightArm.draw();
    rightForeArm.draw();
    rightHand.draw();
    popMatrix();
    //Jambe1
    pushMatrix();
    leftThigh.draw();
    leftCalf.draw();
    leftFoot.draw();
    popMatrix();
    //Jambe2
    pushMatrix();
    rightThigh.draw();
    rightCalf.draw();
    rightFoot.draw();
    popMatrix();

}

void Window::walk() {
    SYSTEMTIME st;
    GetLocalTime(&st);
    leftArm.getAnglesReference().x = cos((st.wSecond + st.wMilliseconds/1000.0)*3)*-20;
    leftForeArm.getAnglesReference().x = cos((st.wSecond + st.wMilliseconds/1000.0)*3)*-10+10;
    leftHand.getAnglesReference().x = cos((st.wSecond + st.wMilliseconds/1000.0)*3)*-5+5;
    rightArm.getAnglesReference().x = cos((st.wSecond + st.wMilliseconds/1000.0)*3)*20;
    rightForeArm.getAnglesReference().x = cos((st.wSecond + st.wMilliseconds/1000.0)*3)*10+10;
    rightHand.getAnglesReference().x = cos((st.wSecond + st.wMilliseconds/1000.0)*3)*5+5;
    torso.getRelativePositionReference().y = cos((st.wSecond + st.wMilliseconds/1000.0)*6)*-0.25;
    leftThigh.getAnglesReference().x = cos((st.wSecond + st.wMilliseconds/1000.0)*3)*20;
    leftCalf.getAnglesReference().x = min(sin((st.wSecond + st.wMilliseconds/1000.0)*3)*60,0.0);
    leftFoot.getAnglesReference().x = cos((st.wSecond + st.wMilliseconds/1000.0)*3)*-20;
    rightThigh.getAnglesReference().x = cos((st.wSecond + st.wMilliseconds/1000.0)*3)*-20;
    rightCalf.getAnglesReference().x = min(sin((st.wSecond + st.wMilliseconds/1000.0)*3)*-60,0.0);
    rightFoot.getAnglesReference().x = cos((st.wSecond + st.wMilliseconds/1000.0)*3)*20;
    torso.getRelativePositionReference().z -= 0.18;
}

void Window::run() {
    SYSTEMTIME st;
    GetLocalTime(&st);
    st.wSecond *= 12;
    st.wMilliseconds *=12;
    torso.getAnglesReference().x = -20;

    double t = st.wSecond % 12 + (st.wMilliseconds%12000)/1000.0;
    double t2 = st.wSecond % 6 + (st.wMilliseconds%6000)/1000.0;

    //(0,0) (1,-2) (3,0) (4,2) (6,0)
    torso.getRelativePositionReference().y = 0.5*(-0.016666666666667 *pow(t2,4)  -0.033333333333333 *pow(t2,3) + 1.35 *pow(t2,2) -3.3*t2);

    leftArm.getAnglesReference().x = sin(t/1.92)* 25;
    rightArm.getAnglesReference().x = sin((t-6)/1.92)* 25;
    leftForeArm.getAnglesReference().x = (sin(t/1.92)*35)+45;
    rightForeArm.getAnglesReference().x = (sin((t-6)/1.92)*35)+45;
    if (t<6){
        //(0,45) (1,70) (3,0) (4,-20) (6,0)
        leftThigh.getAnglesReference().x = -0.875*pow(t,4)+13.25*pow(t,3)-61.625*pow(t,2)+74.25*t+45;
   } else {
       rightThigh.getAnglesReference().x =  -0.875*pow(t-6,4)+13.25*pow(t-6,3)-61.625*pow(t-6,2)+74.25*(t-6)+45;
    }

    if(t < 6) {
        rightThigh.getAnglesReference().x = 0.5*pow(t+6,3)-19*pow(t+6,2)+223.5*(t+6)-765;
    } else {
        //(6,0) (10,70) (11,60) (12,45)
        leftThigh.getAnglesReference().x = 0.5*pow(t,3)-19*pow(t,2)+223.5*(t)-765;
    }
	
    if (t<6){
        //(0,0) (1,-70) (4,-10) (6,-70)
        leftCalf.getAnglesReference().x = -5.4166666666667*pow(t,3)+49.583333333333*pow(t,2)+-114.16666666667*t;
    } else {
        rightCalf.getAnglesReference().x = -5.4166666666667*pow(t-6,3)+49.583333333333*pow(t-6,2)+-114.16666666667*(t-6);
    }

    if(t < 6) {
        rightCalf.getAnglesReference().x = -1.25*pow(t+6,3)+37.916666666667*pow(t+6,2)-355.83333333333*(t+6)+970;
    } else {
        //(6,-70) (8,-90) (11,-20) (12,0)
        leftCalf.getAnglesReference().x = -1.25*pow(t,3)+37.916666666667*pow(t,2)+-355.83333333333*(t)+970;
    }
	torso.getRelativePositionReference().z -= 1;
}


void Window::jump() {

    SYSTEMTIME st;
    GetLocalTime(&st);
    st.wSecond *= 3;
    st.wMilliseconds *=3;
    double t = st.wSecond % 6 + (st.wMilliseconds%6000)/1000.0;

    torso.getRelativePositionReference().y = cos((t/3)*M_PI-M_PI)*5;

    if(t<2) {
        torso.getAnglesReference().x = -22.5*t + 60;
        leftThigh.getAnglesReference().x = 20*pow(t,2) + 20*t - 120;
        leftArm.getAnglesReference().x = 120*t - 80;
        leftForeArm.getAnglesReference().x = -45*t + 90;
        torso.getRelativePositionReference().z -= 0.5;
    } else if (t<4) {
        torso.getAnglesReference().x = -22.5*t + 60;
        leftThigh.getAnglesReference().x = (cos(t*M_PI)*0.5-0.5)*70;
        leftArm.getAnglesReference().x = -70*t + 300;
        leftForeArm.getAnglesReference().x = 40*t - 80;
        torso.getRelativePositionReference().z -= 0.5;
    } else {
        torso.getAnglesReference().x = 45*t - 210;
        leftThigh.getAnglesReference().x = -20*pow(t,2)	+ 140*t	- 240;
        leftArm.getAnglesReference().x = -50*t + 220;
        leftForeArm.getAnglesReference().x = 5*t + 60;
    }

    torso.getAnglesReference().x = -torso.getAnglesReference().x;
    leftThigh.getAnglesReference().x = -leftThigh.getAnglesReference().x;
    rightThigh.getAnglesReference().x = leftThigh.getAnglesReference().x;
    leftCalf.getAnglesReference().x = -leftThigh.getAnglesReference().x;
    rightCalf.getAnglesReference().x = -leftThigh.getAnglesReference().x;
    rightArm.getAnglesReference().x = leftArm.getAnglesReference().x;
    rightForeArm.getAnglesReference().x = leftForeArm.getAnglesReference().x;

}

void Window::drawSol(){

    GLfloat tab_vertex[] = {-100,-14.5,-1000,
                            100,-14.5,-1000,
                            -100,-14.5,1000,
                            100,-14.5,1000};
    GLfloat tab_color[] = {1,1,1,
                           1,1,1,
                           1,1,1,
                           1,1,1};
    GLuint tab_order[] = {0,1,3,2};// en CUBES
    GLfloat tab_tex[] = {0,0,
                         10,0,
                         0,100,
                         10,100};

    // Rendu des objets
    GLint var_pos = glGetAttribLocation(getCurrentShaderId(), "position");
    GLint var_color = glGetAttribLocation(getCurrentShaderId(), "color");
    GLint var_tex = glGetAttribLocation(getCurrentShaderId(), "texC");

    glEnableVertexAttribArray(var_pos);
    glVertexAttribPointer(var_pos,3,GL_FLOAT, GL_FALSE, 0, tab_vertex);
    glEnableVertexAttribArray(var_color);
    glVertexAttribPointer(var_color,3,GL_FLOAT, GL_FALSE, 0, tab_color);
    glEnableVertexAttribArray(var_tex);
    glVertexAttribPointer(var_tex,2,GL_FLOAT, GL_FALSE, 0, tab_tex);

    glUniform1i(glGetUniformLocation(getCurrentShaderId(),"texId"),0);

    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT,tab_order);

    glDisableVertexAttribArray(var_pos);
    glDisableVertexAttribArray(var_color);
    glDisableVertexAttribArray(var_tex);




    GLfloat tab_vertex1[] = {-150,105,-1000,
                            150,105,-1000,
                            -150,105,1000,
                            150,105,1000};
    GLfloat tab_color1[] = {1,1,1,
                           1,1,1,
                           1,1,1,
                           1,1,1};
    GLuint tab_order1[] = {0,1,3,2};// en CUBES
    GLfloat tab_tex1[] = {0,0,
                         1,0,
                         0,1,
                         1,1};

    // Rendu des objets
    //GLint var_id = glGetUniformLocation(m_Framework->getCurrentShaderId(), "MVP");
    GLint var_pos1 = glGetAttribLocation(getCurrentShaderId(), "position");
    GLint var_color1 = glGetAttribLocation(getCurrentShaderId(), "color");
    GLint var_tex1 = glGetAttribLocation(getCurrentShaderId(), "texC");

    glEnableVertexAttribArray(var_pos1);
    glVertexAttribPointer(var_pos1,3,GL_FLOAT, GL_FALSE, 0, tab_vertex1);
    glEnableVertexAttribArray(var_color1);
    glVertexAttribPointer(var_color1,3,GL_FLOAT, GL_FALSE, 0, tab_color1);
    glEnableVertexAttribArray(var_tex);
    glVertexAttribPointer(var_tex1,2,GL_FLOAT, GL_FALSE, 0, tab_tex1);

    glUniform1i(glGetUniformLocation(getCurrentShaderId(),"texId"),3);

    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT,tab_order1);

    glDisableVertexAttribArray(var_pos1);
    glDisableVertexAttribArray(var_color1);
    glDisableVertexAttribArray(var_tex1);
}

void Window::drawImm(){

    GLfloat tab_vertex[] = {-100,-14.5,-1000,
                            -100, 100,-1000,
                            -100,-14.5,1000,
                            -100,100,1000};
    GLfloat tab_color[] = {1,1,1,
                           1,1,1,
                           1,1,1,
                           1,1,1};
    GLuint tab_order[] = {0,1,3,2};// en CUBES
    GLfloat tab_tex[] = {0,0,
                         1,0,
                         0,10,
                         1,10};

    // Rendu des objets
    //GLint var_id = glGetUniformLocation(m_Framework->getCurrentShaderId(), "MVP");
    GLint var_pos = glGetAttribLocation(getCurrentShaderId(), "position");
    GLint var_color = glGetAttribLocation(getCurrentShaderId(), "color");
    GLint var_tex = glGetAttribLocation(getCurrentShaderId(), "texC");

    glEnableVertexAttribArray(var_pos);
    glVertexAttribPointer(var_pos,3,GL_FLOAT, GL_FALSE, 0, tab_vertex);
    glEnableVertexAttribArray(var_color);
    glVertexAttribPointer(var_color,3,GL_FLOAT, GL_FALSE, 0, tab_color);
    glEnableVertexAttribArray(var_tex);
    glVertexAttribPointer(var_tex,2,GL_FLOAT, GL_FALSE, 0, tab_tex);

    glUniform1i(glGetUniformLocation(getCurrentShaderId(),"texId"),2);

    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT,tab_order);

    glDisableVertexAttribArray(var_pos);
    glDisableVertexAttribArray(var_color);
    glDisableVertexAttribArray(var_tex);


    GLfloat tab_vertex1[] = {100,-14.5,-1000,
                            100, 100,-1000,
                            100,-14.5,1000,
                            100,100,1000};
    GLfloat tab_color1[] = {1,1,1,
                           1,1,1,
                           1,1,1,
                           1,1,1};
    GLuint tab_order1[] = {0,1,3,2};// en CUBES
    GLfloat tab_tex1[] = {0,0,
                         1,0,
                         0,10,
                         1,10};

    // Rendu des objets
    //GLint var_id = glGetUniformLocation(m_Framework->getCurrentShaderId(), "MVP");
    GLint var_pos1 = glGetAttribLocation(getCurrentShaderId(), "position");
    GLint var_color1 = glGetAttribLocation(getCurrentShaderId(), "color");
    GLint var_tex1 = glGetAttribLocation(getCurrentShaderId(), "texC");

    glEnableVertexAttribArray(var_pos1);
    glVertexAttribPointer(var_pos1,3,GL_FLOAT, GL_FALSE, 0, tab_vertex1);
    glEnableVertexAttribArray(var_color1);
    glVertexAttribPointer(var_color1,3,GL_FLOAT, GL_FALSE, 0, tab_color1);
    glEnableVertexAttribArray(var_tex1);
    glVertexAttribPointer(var_tex1,2,GL_FLOAT, GL_FALSE, 0, tab_tex1);

    glUniform1i(glGetUniformLocation(getCurrentShaderId(),"texId"),2);

    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT,tab_order1);

    glDisableVertexAttribArray(var_pos1);
    glDisableVertexAttribArray(var_color1);
    glDisableVertexAttribArray(var_tex1);



    GLfloat tab_vertex2[] = {100,-14.5,-900,
                            100, 100,-900,
                            -100,-14.5,-900,
                            -100,100,-900};
    GLfloat tab_color2[] = {1,1,1,
                           1,1,1,
                           1,1,1,
                           1,1,1};
    GLuint tab_order2[] = {0,1,3,2};// en CUBES
    GLfloat tab_tex2[] = {0,0,
                         1,0,
                         0,1,
                         1,1};

    // Rendu des objets
    GLint var_pos2 = glGetAttribLocation(getCurrentShaderId(), "position");
    GLint var_color2 = glGetAttribLocation(getCurrentShaderId(), "color");
    GLint var_tex2 = glGetAttribLocation(getCurrentShaderId(), "texC");

    glEnableVertexAttribArray(var_pos2);
    glVertexAttribPointer(var_pos2,3,GL_FLOAT, GL_FALSE, 0, tab_vertex2);
    glEnableVertexAttribArray(var_color2);
    glVertexAttribPointer(var_color2,3,GL_FLOAT, GL_FALSE, 0, tab_color2);
    glEnableVertexAttribArray(var_tex2);
    glVertexAttribPointer(var_tex2,2,GL_FLOAT, GL_FALSE, 0, tab_tex2);

    glUniform1i(glGetUniformLocation(getCurrentShaderId(),"texId"),2);

    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT,tab_order2);

    glDisableVertexAttribArray(var_pos2);
    glDisableVertexAttribArray(var_color2);
    glDisableVertexAttribArray(var_tex2);



    GLfloat tab_vertex3[] = {100,-14.5,900,
                            100, 100,900,
                            -100,-14.5,900,
                            -100,100,900};
    GLfloat tab_color3[] = {1,1,1,
                           1,1,1,
                           1,1,1,
                           1,1,1};
    GLuint tab_order3[] = {0,1,3,2};// en CUBES
    GLfloat tab_tex3[] = {0,0,
                         1,0,
                         0,1,
                         1,1};

    // Rendu des objets
    GLint var_pos3 = glGetAttribLocation(getCurrentShaderId(), "position");
    GLint var_color3 = glGetAttribLocation(getCurrentShaderId(), "color");
    GLint var_tex3 = glGetAttribLocation(getCurrentShaderId(), "texC");

    glEnableVertexAttribArray(var_pos3);
    glVertexAttribPointer(var_pos3,3,GL_FLOAT, GL_FALSE, 0, tab_vertex3);
    glEnableVertexAttribArray(var_color3);
    glVertexAttribPointer(var_color3,3,GL_FLOAT, GL_FALSE, 0, tab_color3);
    glEnableVertexAttribArray(var_tex3);
    glVertexAttribPointer(var_tex3,2,GL_FLOAT, GL_FALSE, 0, tab_tex3);

    glUniform1i(glGetUniformLocation(getCurrentShaderId(),"texId"),2);

    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT,tab_order3);

    glDisableVertexAttribArray(var_pos3);
    glDisableVertexAttribArray(var_color3);
    glDisableVertexAttribArray(var_tex3);

}

void Window::mouseMoveEvent(QMouseEvent* event){

    int currX =event->pos().x();
    int currY =event->pos().y();
    int speed = 3;

    glm::vec4 view2pos =glm::vec4(lookPoint-globalPosition);
    view2pos = glm::normalize(view2pos);
    if(view2pos.x != 0 || view2pos.y != 0 || view2pos.z != 0){
        if(currX - camX > 1 && currX - camX < 10){
            float angle = 3*(M_PI/180);
            currentRotation.x += speed;

            glm::mat4 rotatey = glm::mat4(
                                   cos(angle) ,0,sin(angle), globalPosition.x - globalPosition.x*cos(angle) - globalPosition.z*sin(angle),
                                   0,1,0,0,
                                   -sin(angle), 0, cos(angle), globalPosition.z - globalPosition.z*cos(angle) + globalPosition.x*sin(angle),
                                   0 ,0,0,1
                               );

            glm::vec4 result = rotatey * view2pos;

            lookPoint.x = globalPosition.x + result.x;
            lookPoint.z = globalPosition.z + result.z;
		} else if (currX - camX < -1 && currX - camX > -10){
			float angle = -3*(M_PI/180);
			currentRotation.x += -speed;
			glm::mat4 rotatey = glm::mat4(
								   cos(angle) ,0,sin(angle), globalPosition.x - globalPosition.x*cos(angle) - globalPosition.z*sin(angle),
								   0,1,0,0,
								   -sin(angle), 0, cos(angle), globalPosition.z - globalPosition.z*cos(angle) + globalPosition.x*sin(angle),
								   0 ,0,0,1
							   );

			glm::vec4 result = rotatey * view2pos;

			lookPoint.x = globalPosition.x + result.x;
			lookPoint.z = globalPosition.z + result.z;
		}

		//Using the Y
		if(currY - camY > 1 && currY - camY < 10 && currentRotation.y < 50){
			float angle;
			if(((int)currentRotation.x)%180 < 90 && ((int)currentRotation.x)%180 > -90){
				angle = speed*(M_PI/180);
			} else {
				angle = -speed*(M_PI/180);
			}
			currentRotation.y += speed;
			glm::mat4 rotatex = glm::mat4(
								   1,         0,          0,                             0,
								   0, cos(angle), -sin(angle), globalPosition.y - globalPosition.y*cos(angle) + globalPosition.z*sin(angle),
								   0, sin(angle),  cos(angle), globalPosition.z - globalPosition.z*cos(angle) - globalPosition.y*sin(angle),
								   0 ,0,0,1
							   );

			glm::vec4 result = rotatex * view2pos;

			lookPoint.y = globalPosition.y + result.y;
			lookPoint.z = globalPosition.z + result.z;
		} else if (currY - camY < -1 && currY - camY > -10 && currentRotation.y > -50){
			float angle;
			if(((int)currentRotation.x)%180 < 90 && ((int)currentRotation.x)%180 > -90){
				angle = -speed*(M_PI/180);
			} else {
				angle = speed*(M_PI/180);
			}
			currentRotation.y += -speed ;
			glm::mat4 rotatex = glm::mat4(
								   1,         0,          0,                             0,
								   0, cos(angle), -sin(angle), globalPosition.y - globalPosition.y*cos(angle) + globalPosition.z*sin(angle),
								   0, sin(angle),  cos(angle), globalPosition.z - globalPosition.z*cos(angle) - globalPosition.y*sin(angle),
								   0 ,0,0,1
							   );

			glm::vec4 result = rotatex * view2pos;

			lookPoint.y = globalPosition.y + result.y;
			lookPoint.z = globalPosition.z + result.z;
		}
	}
	camX = currX;
	camY = currY;
	//QCursor::setPos(glob);
}


void
Window::keyPressEvent( QKeyEvent* event )
{
     glm::mat4 rotate90;
     glm::vec4 vec2View;
     glm::vec4 result;
    switch( event->key() )
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
		case Qt::Key_Q:
			vec2View = glm::vec4(lookPoint.x - globalPosition.x,lookPoint.y - globalPosition.y,lookPoint.z - globalPosition.z,1.0);
			if(vec2View.x != 0 || vec2View.y != 0 || vec2View.z != 0 ){
				vec2View = glm::normalize(vec2View);
				rotate90 = glm::mat4(
									   0 ,0,1,0,
									   0 ,1,0,0,
									   -1,0,0,0,
									   0 ,0,0,1
								   );
				result = vec2View * rotate90;
				globalPosition+=result*4;
				lookPoint += result*4;
			}
			break;
		case Qt::Key_PageUp:
			globalPosition.y += 3;
			lookPoint.y +=3;
			break;
		case Qt::Key_PageDown:
			globalPosition.y -= 3;
			lookPoint.y -=3;
			break;
		case Qt::Key_D:
			vec2View = glm::vec4(lookPoint.x - globalPosition.x,lookPoint.y - globalPosition.y,lookPoint.z - globalPosition.z,1.0);
			if(vec2View.x != 0 || vec2View.y != 0 || vec2View.z != 0 ){
				vec2View = glm::normalize(vec2View);
				rotate90 = glm::mat4(
									   0 ,0,-1,0,
									   0 ,1,0,0,
									   1,0,0,0,
									   0 ,0,0,1
								   );
				result = vec2View * rotate90;
				globalPosition+=result*4;
				lookPoint += result*4;
			}
			break;
		case Qt::Key_Z:
			vec2View = glm::vec4(lookPoint.x - globalPosition.x,lookPoint.y - globalPosition.y,lookPoint.z - globalPosition.z,1.0);
			if(vec2View.x != 0 || vec2View.y != 0 || vec2View.z != 0 ){
				vec2View = glm::normalize(vec2View);
				result = vec2View;
				globalPosition+=result*4;
				lookPoint += result*4;
			}
			break;
		case Qt::Key_S:
			vec2View = glm::vec4(lookPoint.x - globalPosition.x,lookPoint.y - globalPosition.y,lookPoint.z - globalPosition.z,1.0);
			if(vec2View.x != 0 || vec2View.y != 0 || vec2View.z != 0 ){
				vec2View = glm::normalize(vec2View);
				result = vec2View;
				globalPosition-=result*4;
				lookPoint -= result*4;
			}
			break;
		case Qt::Key_R:
				angle1 = angle2 = 0.0f;
				break;
		case Qt::Key_A:
				action += 1;
				torso.getAnglesReference().x = 0;
				break;
		case Qt::Key_E:
				action -= 1;
				torso.getAnglesReference().x = 0;
				break;
    }
}
