#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include "Particle.h"

class Behavior
{
    public:
        virtual void update() = 0;
};

class Fall : public Behavior
{
    private:
        Particle* p;

    public:
        Fall(): p(nullptr){}
        Fall(Particle* p): p(p){}
        virtual void update();
};

#endif