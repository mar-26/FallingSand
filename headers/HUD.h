#ifndef HUD_H
#define HUD_H

#include "Observer.h"
#include "ParticleSystem.h"

class HUD : public Observer
{
    private:
        std::string numParticles;
        std::string brushSize;
        std::string element;
        ParticleSystem *ps;

    public:
        HUD();
        HUD(ParticleSystem*);
        void draw();
        void drawString(int, int, float, std::string);
        virtual void update();
};

#endif