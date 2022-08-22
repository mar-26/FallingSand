#ifndef SCREEN_H
#define SCREEN_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Color.h"
#include "Particle.h"

class Screen
{
    private:
        int width;
        int height;
        Color *screen;
        Color black;
        Color sand;

    public:
        Screen();
        Screen(int, int);
        ~Screen();

        void draw();
        void update();
        void clearScreen();
        void placeParticle(Particle*);
        void placeColor(int, int, Color);

        bool isEmpty(int, int);
        int getIndex(int, int);
        Color getColor(int, int);

        void setWidth(int);
        void setHeight(int);

        int getWidth();
        int getHeight();
};

#endif
