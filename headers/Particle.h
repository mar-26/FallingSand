#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>

#include "Color.h"
#include "Vector3.h"
#include "Behavior.h"

class Particle
{
    private:
        Vector3 position;
        Vector3 velocity;
        Color color;
        std::vector<Behavior*> behaviors;

    public:
        Particle();
        Particle(Vector3, Vector3, Color);

        void update(void*);

        void setPosition(Vector3);
        void setVelocity(Vector3);
        void setColor(Color);
        void addBehavior(Behavior*);
        void removeBehavior(Behavior*);

        std::vector<Behavior*> getBehaviors();
        Vector3 getPosition();
        Vector3 getVelocity();
        Color getColor();
        friend bool operator==(const Particle &, const Particle&);
};

class Sand : public Particle
{
    public:
        Sand() : Particle(Vector3(), Vector3(), Color(0.9, 0.8, 0.4)){}
        Sand(int x, int y) : Particle(Vector3(x, y, 0), Vector3(), Color(0.9, 0.8, 0.4))
            { addBehavior(new Fall()); }
};

class Wall : public Particle
{
    public:
        Wall() : Particle(Vector3(), Vector3(), Color(0.6, 0.6, 0.7)){}
        Wall(int x, int y) : Particle(Vector3(x, y, 0), Vector3(), Color(0.6, 0.6, 0.7)){}
};

class Erase : public Particle
{
    public:
        Erase() : Particle(Vector3(), Vector3(), Color(0, 0, 0)){}
        Erase(int x, int y) : Particle(Vector3(x, y, 0), Vector3(), Color(0, 0, 0)){}
};

class Water : public Particle
{
    public:
        Water() : Particle(Vector3(), Vector3(), Color(0.3, 0.4, 1)){}
        Water(int x, int y) : Particle(Vector3(x, y, 0), Vector3(), Color(0.3, 0.4, 1))
            { addBehavior(new Liquid()); }
};

class Gas : public Particle
{
    public:
        Gas() : Particle(Vector3(), Vector3(), Color(0, 0.6, 0.1)){}
        Gas(int x, int y) : Particle(Vector3(x, y, 0), Vector3(), Color(0, 0.6, 0.1))
            { addBehavior(new Rise(false)); }
};

class Soil : public Particle
{
    public:
        Soil() : Particle(Vector3(), Vector3(), Color(0.4, 0.2, 0)){}
        Soil(int x, int y) : Particle(Vector3(x, y, 0), Vector3(), Color(0.4, 0.2, 0))
            { addBehavior(new Fall()); }
};

class Fire : public Particle
{
    public:
        Fire() : Particle(Vector3(), Vector3(), Color(0.9, 0, 0.1)){}
        Fire(int x, int y) : Particle(Vector3(x, y, 0), Vector3(), Color(0.9, 0, 0.1)){}
};

class Plant : public Particle
{
    public:
        Plant() : Particle(Vector3(), Vector3(), Color(0, 0.9, 0.2)){}
        Plant(int x, int y) : Particle(Vector3(x, y, 0), Vector3(), Color(0, 0.9, 0.2))
            { addBehavior(new Grow());
              addBehavior(new Burn());
            }
};

class Ice : public Particle
{
    public:
        Ice() : Particle(Vector3(), Vector3(), Color(0, 1, 1)){}
        Ice(int x, int y) : Particle(Vector3(x, y, 0), Vector3(), Color(0, 1, 1))
        {
            addBehavior(new Melt());
        }
};

#endif