#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <list>
#include <vector>

#include "Screen.h"
#include "Particle.h"
#include "Subject.h"

class ParticleSystem : public Subject
{
    private:
        std::vector<std::vector<Particle*> > particles;
		std::list<Observer*> observers;
        Screen *screen;
        int brushSize;
        std::string element;

    public:
        ParticleSystem();
        ParticleSystem(int, int);
        ~ParticleSystem();

        void draw();
        void update();
        void addParticle(int, int);
        void eraseParticle(int, int);
        void keyPressed(int);
        void keyPressed(unsigned char);
        void sortVector();
        void placeColor(int, int, Color);

        bool isEmpty(int, int);
        Color getColor(int, int);

        std::string getElement();
        std::string getNumParticals();
        std::string getBrushSize();

		virtual void registerObserver(Observer*);
		virtual void removeObserver(Observer*);
		virtual void notifyObservers();
};

#endif
