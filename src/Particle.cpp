#include "Particle.h"

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

Particle::Particle()
{
    position = Vector3(0, 0, 0);
    color = Color(0, 1, 0);
    behaviors = std::vector<Behavior*>();
}

Particle::Particle(Vector3 p, Vector3 v, Color c)
{
    position = p;
    velocity = v;
    color = c;
    behaviors = std::vector<Behavior*>();
}

void Particle::update(void *s)
{
    for (int i = 0; i < behaviors.size(); i++)
    {
        behaviors[i]->update(s, this);
    }
}

void Particle::setPosition(Vector3 p)
{
    position = p;
}

void Particle::setVelocity(Vector3 v)
{
    velocity = v;
}

void Particle::setColor(Color c)
{
    color = c;
}

void Particle::addBehavior(Behavior *b)
{
    behaviors.push_back(b);
}

void Particle::removeBehavior(Behavior *b)
{
	std::vector<Behavior*>::iterator it;
	for (it = behaviors.begin(); it != behaviors.end(); it++)
	{
		Behavior* temp = *it;
		if (temp == b)
		{
			behaviors.erase(it);
		}
	}
}

std::vector<Behavior*> Particle::getBehaviors()
{
    return behaviors;
}

Vector3 Particle::getPosition()
{
    return position;
}

Vector3 Particle::getVelocity()
{
    return velocity;
}

Color Particle::getColor()
{
    return color;
}

bool operator==(const Particle &p1, const Particle &p2)
{
    if (p1.position.x == p2.position.x && p1.position.y == p2.position.y && p1.position.z == p2.position.z)
    {
        return true;
    }
    return false;
}
