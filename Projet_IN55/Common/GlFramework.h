#ifndef GlFramework_h
#define GlFramework_h


#include "AbstractFramework.h"

#include <GL/glew.h>

#include <QGLWidget>
#include <QLinkedList>
#include <vector>
#include <string>


struct GLMatrix
{
    union
    {
        GLfloat m[4][4];
        GLfloat data[16];
    };

    void setIdentity();
};

GLMatrix operator*(const GLMatrix &, const GLMatrix &);


class GlFramework : public AbstractFramework, public QGLWidget
{
    protected:
        GLMatrix pProjMatrix, pViewMatrix, pModelMatrix;
        QLinkedList<GLMatrix> pMatrixStack;
        std::vector<std::string> m_ShaderNames;
        std::vector<GLuint> m_Shader;
        GLint m_CurrentShader;


    private: // methods
        void timerEvent(QTimerEvent *);


    public: // methods
        GlFramework();
        ~GlFramework();

        /*!
        *\brief Fonction de chargement d'un shader.
        */
        char* loadShader( const char* file_name );

        /*!
        *\brief Fonction de cr�ation d'un shader.
        */
        GLuint createShader( const char* shader_prefix );

        /*!
        *\brief Utilisation d'un shader.
        */
        bool useShader( GLuint shader_id );
        bool useShader( const char* shader_name );

        /*!
        *\brief Id du shader actuel.
        */
        GLuint getCurrentShaderId() const;

        /*!
        *\brief Transmet la matrice MVP = P*V*M au shader actif.
        */
        void transmitMVP();

        /*!
        *\brief Transmet la matrice MV = V*M au shader actif.
        */
        void transmitMV();

        /*!
        *\brief Fonction d'initialization d'OpenGL, appel�e � la cr�ation du
        *contexte de rendu.
        */
        void initializeGL();

        /*!
        *\brief Fonction d'initialization des objets 3D appel�e par initializeGL().
        */
        virtual void initializeObjects() = 0;

        /*!
        *\brief Fonction d'affichage appel�e � intervalle r�gulier.
        */
        virtual void paintGL() = 0;

        /*!
        *\brief Appel� chaque fois que la fen�tre est redimensionn�e.
        */
        void resizeGL(int w, int h);


        /*!
        *\brief Recalcule la matrice de projection en utilisant les valeurs \a fovY
        *c'est � dire l'angle d'ouverture de la cam�ra selon l'axe Y (en degr�s), le
        *\a ratio entre la longueur et la largeur de la cam�ra, et les distances
        *\a zNear et \a zFar correspondant respectivement aux distances de clipping
        *proches et �loign�es.
        */
        void setPerspective(GLfloat fovY, GLfloat ratio, GLfloat zNear, GLfloat zFar);

        /*!
        *\brief Recalcule la matrive de vue en utilisant les coordonn�es \a eyeX,
        *\a eyeY et \a eyeZ correspondant � la position de la cam�ra, les
        *coordonn�es \a targetX, \a targetY et \a targetZ du point vis� par la
        *cam�ra et les coordonn�es \a upX, \a upY et \a upZ du vecteur repr�sentant
        *l'axe vertical de la cam�ra.
        */
        void lookAt(GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ, GLfloat targetX, GLfloat targetY, GLfloat targetZ, GLfloat upX = 0.0f, GLfloat upY = 1.0f, GLfloat upZ = 0.0f);

        /*!
        *\brief Enregistre la matrice de transformation courante sur le sommet de la
        *pile de matrices.
        */
        void pushMatrix();

        /*!
        *\brief Remplace la matrice de transformation courante par celle se trouvant
        *au sommet de la pile de matrices.
        */
        void popMatrix();

        /*!
        *\brief Remplace la matrice de transformation courante par une matrice
        *identit�.
        */
        void loadIdentity();

        /*!
        *\brief Multiplie la matrice de transformation courante par une matrice de
        *translation utilisant le vecteur de coordonn�es \a x, \a y et \a z.
        */
        void translate(GLfloat x, GLfloat y, GLfloat z);

        /*!
        *\brief Multiplie la matrice de transformation courante par une matrice de
        *rotation utilisant l'angle \a angle (en degr�s) et l'axe repr�sent� par le
        *vecteur de coordonn�es \a x, \a y et \a z.
        */
        void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

        /*!
        *\brief Multiplie la matrice de transformation courante par une matrice de
        *changement d'�chelle utilisant les facteurs \a x, \a y et \a z.
        */
        void scale(GLfloat x, GLfloat y, GLfloat z);
};


#endif
