#include "Bodypart.h"
#include "MemDefns.h"
#include <math.h>
#include <stdio.h>

BodyPart::BodyPart(glm::vec3 size,glm::vec3 angles, glm::vec3 relativePosition, BodyPart *parent, glm::vec3 localOrigin)
{
    this->angles = angles;
    this->relativePosition = relativePosition;
    this->parent = parent;
    this->size = size;
    this->localOrigin = localOrigin;

}

glm::vec3 BodyPart::getAngles(){
    if(this->parent == NULL){
        return this->angles;
    } else {
        return this->angles + this->parent->getAngles();
    }

}

glm::vec3 BodyPart::getRelativePosition(){
    if(this->parent == NULL){
        return this->relativePosition;
    } else {
        return this->relativePosition + this->parent->getRelativePosition();
    }
}


glm::vec3 BodyPart::getSize(){
    return this->size;
}

glm::vec3 BodyPart::getLocalOrigin(){
    return this->localOrigin;
}

glm::vec3& BodyPart::getAnglesReference(){
    return this->angles;
}

glm::vec3& BodyPart::getRelativePositionReference(){
    return this->relativePosition;
}

glm::vec3& BodyPart::getSizeReference(){
    return this->size;
}

glm::vec3& BodyPart::getLocalOriginReference(){
    return this->localOrigin;
}

void BodyPart::draw()
{
    if (m_Framework->useShader( "texture" ))
    {
        //m_Framework->pushMatrix();
        GLfloat xO = this->getLocalOrigin().x;
        GLfloat yO = this->getLocalOrigin().y;
        GLfloat zO = this->getLocalOrigin().z;

        GLfloat longueur = this->getSize().x;
        GLfloat largeur = this->getSize().y;
        GLfloat profondeur = this->getSize().z;
       // m_Framework->translate(this->getRelativePosition().x,this->getRelativePosition().y,this->getRelativePosition().z);
        m_Framework->translate(this->relativePosition.x,this->relativePosition.y,this->relativePosition.z);
        m_Framework->rotate(this->angles.x,1,0,0);
        m_Framework->rotate(this->angles.y,0,1,0);
        m_Framework->rotate(this->angles.z,0,0,1);

        m_Framework->transmitMVP();

        GLfloat tab_vertex[] = {0 - xO,0 - yO,0 - zO,
                                longueur - xO,0 - yO,0 - zO,
                                longueur - xO,largeur- yO,0 - zO,
                                0 - xO,largeur- yO,0 - zO,
                                0 - xO,0- yO,profondeur - zO,
                                longueur - xO,0- yO,profondeur - zO,
                                longueur - xO,largeur- yO,profondeur - zO,
                                0 - xO,largeur- yO,profondeur - zO};
        GLfloat tab_tex[] = {0,0,
                             1,0,
                             1,1,
                             0,1,
                             0,0,
                             1,0,
                             1,1,
                             0,1};
        //GLfloat tab_color[] = {1,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,1,0,0,1};
        GLuint tab_order[] = {0,3,1,2,5,6,4,7,0,3};//CUBES STRIPES
        GLuint tab_order2[] = {3,2,6,7,0,1,5,4};// en CUBES

        // Rendu des objets
        //m_Framework->useShader("brown");
        //GLint var_id = glGetUniformLocation(m_Framework->getCurrentShaderId(), "MVP");
        GLint var_pos = glGetAttribLocation(m_Framework->getCurrentShaderId(), "position");
        //GLint var_color = glGetAttribLocation(m_Framework->getCurrentShaderId(), "color");
        GLint var_tex = glGetAttribLocation(m_Framework->getCurrentShaderId(), "texC");
        glEnableVertexAttribArray(var_pos);
        glVertexAttribPointer(var_pos,3,GL_FLOAT, GL_FALSE, 0, tab_vertex);
        /*glEnableVertexAttribArray(var_color);
        glVertexAttribPointer(var_color,3,GL_FLOAT, GL_FALSE, 0, tab_color);*/
        glEnableVertexAttribArray(var_tex);
                glVertexAttribPointer(var_tex,2,GL_FLOAT, GL_FALSE, 0, tab_tex);
        glUniform1i(glGetUniformLocation(m_Framework->getCurrentShaderId(),"texId"),1);

        glDrawElements(GL_QUAD_STRIP, 10, GL_UNSIGNED_INT,tab_order);
        glDrawElements(GL_QUADS, 8, GL_UNSIGNED_INT,tab_order2);

        glDisableVertexAttribArray(var_pos);
        //glDisableVertexAttribArray(var_color);
        glDisableVertexAttribArray(var_tex);
       //m_Framework->popMatrix();
    }
}

