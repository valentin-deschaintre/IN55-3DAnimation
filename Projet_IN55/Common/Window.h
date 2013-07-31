#ifndef WINDOW_H
#define WINDOW_H


#include <GlFramework.h>
#include <QKeyEvent>
#include "Shapes/Bodypart.h"

class Window : public GlFramework
{
	private: // methods
		/*!
		*\brief Fonction d'initialization des structures des objets.
		*/
		void initializeObjects();

		/*!
		*\brief Fonction d'affichage appelée à intervalle régulier.
		*/
		void paintGL();
        void walk();
        void run();
        void jump();
		void keyPressEvent(QKeyEvent *);
        void mouseMoveEvent(QMouseEvent *);
        void paintMan();
        void drawSol();
        void drawImm();
	public: // methods
		Window();
		~Window();
};


#endif // WINDOW_H
