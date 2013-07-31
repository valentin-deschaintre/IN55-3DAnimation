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
        *\brief Fonction de création d'un shader.
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
        *\brief Fonction d'initialization d'OpenGL, appelée à la création du
        *contexte de rendu.
        */
        void initializeGL();

        /*!
        *\brief Fonction d'initialization des objets 3D appelée par initializeGL().
        */
        virtual void initializeObjects() = 0;

        /*!
        *\brief Fonction d'affichage appelée à intervalle régulier.
        */
        virtual void paintGL() = 0;

        /*!
        *\brief Appelé chaque fois que la fenêtre est redimensionnée.
        */
        void resizeGL(int w, int h);


        /*!
        *\brief Recalcule la matrice de projection en utilisant les valeurs \a fovY
        *c'est à dire l'angle d'ouverture de la caméra selon l'axe Y (en degrés), le
        *\a ratio entre la longueur et la largeur de la caméra, et les distances
        *\a zNear et \a zFar correspondant respectivement aux distances de clipping
        *proches et éloignées.
        */
        void setPerspective(GLfloat fovY, GLfloat ratio, GLfloat zNear, GLfloat zFar);

        /*!
        *\brief Recalcule la matrive de vue en utilisant les coordonnées \a eyeX,
        *\a eyeY et \a eyeZ correspondant à la position de la caméra, les
        *coordonnées \a targetX, \a targetY et \a targetZ du point visé par la
        *caméra et les coordonnées \a upX, \a upY et \a upZ du vecteur représentant
        *l'axe vertical de la caméra.
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
        *identité.
        */
        void loadIdentity();

        /*!
        *\brief Multiplie la matrice de transformation courante par une matrice de
        *translation utilisant le vecteur de coordonnées \a x, \a y et \a z.
        */
        void translate(GLfloat x, GLfloat y, GLfloat z);

        /*!
        *\brief Multiplie la matrice de transformation courante par une matrice de
        *rotation utilisant l'angle \a angle (en degrés) et l'axe représenté par le
        *vecteur de coordonnées \a x, \a y et \a z.
        */
        void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

        /*!
        *\brief Multiplie la matrice de transformation courante par une matrice de
        *changement d'échelle utilisant les facteurs \a x, \a y et \a z.
        */
        void scale(GLfloat x, GLfloat y, GLfloat z);
};


#endif
