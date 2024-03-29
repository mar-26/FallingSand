#ifndef PARTICLE_H
#define PARTICLE_H

#include "Color.h"
#include "Vector3.h"

class Particle
{
    private:
        Vector3 position;
        Vector3 velocity;
        Color color;

    public:
        Particle();
        Particle(Vector3, Vector3, Color);

        virtual void move(void*) = 0;
        void update();

        void setPosition(Vector3);
        void setVelocity(Vector3);
        void setColor(Color);

        Vector3 getPosition();
        Vector3 getVelocity();
        Color getColor();
        friend bool operator==(const Particle &, const Particle&);
};

class Sand : public Particle
{
    public:
        Sand() : Particle(Vector3(0, 0, 0), Vector3(0, 0, 0), Color(0.9, 0.8, 0.4)){}
        Sand(int x, int y) : Particle(Vector3(x, y, 0), Vector3(0, 0, 0), Color(0.9, 0.8, 0.4)){}

        virtual void move(void*);
};

class Wall : public Particle
{
    public:
        Wall() : Particle(Vector3(0, 0, 0), Vector3(0, 0, 0), Color(0.6, 0.6, 0.7)){}
        Wall(int x, int y) : Particle(Vector3(x, y, 0), Vector3(0, 0, 0), Color(0.6, 0.6, 0.7)){}

        virtual void move(void*);
};

class Erase : public Particle
{
    public:
        Erase() : Particle(Vector3(0, 0, 0), Vector3(0, 0, 0), Color(0, 0, 0)){}
        Erase(int x, int y) : Particle(Vector3(x, y, 0), Vector3(0, 0, 0), Color(0, 0, 0)){}

        virtual void move(void*);
};

class Water : public Particle
{
    public:
        Water() : Particle(Vector3(0, 0, 0), Vector3(0, 0, 0), Color(0.3, 0.4, 1)){}
        Water(int x, int y) : Particle(Vector3(x, y, 0), Vector3(0, 0, 0), Color(0.3, 0.4, 1)){}

        virtual void move(void*);
};

class Gas : public Particle
{
    public:
        Gas() : Particle(Vector3(0, 0, 0), Vector3(0, 0, 0), Color(0, 0.6, 0.1)){}
        Gas(int x, int y) : Particle(Vector3(x, y, 0), Vector3(0, 0, 0), Color(0, 0.6, 0.1)){}

        virtual void move(void*);
};

class Soil : public Particle
{
    public:
        Soil() : Particle(Vector3(0, 0, 0), Vector3(0, 0, 0), Color(0.4, 0.2, 0)){}
        Soil(int x, int y) : Particle(Vector3(x, y, 0), Vector3(0, 0, 0), Color(0.4, 0.2, 0)){}

        virtual void move(void*);
};

class Fire : public Particle
{
    public:
        Fire() : Particle(Vector3(0, 0, 0), Vector3(0, 0, 0), Color(0.9, 0, 0.1)){}
        Fire(int x, int y) : Particle(Vector3(x, y, 0), Vector3(0, 0, 0), Color(0.9, 0, 0.1)){}

        virtual void move(void*);
};

class Plant : public Particle
{
    private:
        int moves;
    public:
        Plant() : Particle(Vector3(0, 0, 0), Vector3(0, 0, 0), Color(0, 0.9, 0.2)), moves(0){}
        Plant(int x, int y) : Particle(Vector3(x, y, 0), Vector3(0, 0, 0), Color(0, 0.9, 0.2)), moves(0){}

        virtual void move(void*);
};

#endif