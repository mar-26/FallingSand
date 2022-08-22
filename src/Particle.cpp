#include "Particle.h"
#include "Screen.h"
#include "ParticleSystem.h"

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
}

Particle::Particle(Vector3 p, Vector3 v, Color c)
{
    position = p;
    velocity = v;
    color = c;
}

void Particle::update()
{
    position += velocity;
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

void Sand::move(void *s)
{
    int px = getPosition().x;
    int py = getPosition().y;

    Screen *screen = static_cast<Screen*>(s);
    bool down = screen->isEmpty(px, py+1);
    bool left = screen->isEmpty(px-1, py+1);
    bool right = screen->isEmpty(px+1, py+1);

    if (down || screen->getColor(px, py+1) == Water().getColor())
    {
        setPosition(Vector3(px, py+1, 0));
    }
    else
    {
        if (left && right)
        {
            int r = rand()%2;
            left = r == 0 ? true : false;
            right = r == 0 ? false : true;
        }

        if (left)
        {
            setPosition(Vector3(px-1, py+1, 0));
        }
        else if (right)
        {
            setPosition(Vector3(px+1, py+1, 0));
        }
        else
        {
            setPosition(Vector3(px, py, 0));
        }
    }
}

void Wall::move(void *s)
{
}

void Erase::move(void *s)
{
}

void Water::move(void *s)
{
    int px = getPosition().x;
    int py = getPosition().y;

    Screen *screen = static_cast<Screen*>(s);
    bool down = screen->isEmpty(px, py+1);
    bool left = screen->isEmpty(px-1, py);
    bool right = screen->isEmpty(px+1, py);

    if (down)
    {
        setPosition(Vector3(px, py+1, 0));
    }
    else
    {
        int s = rand()%2;
        if (right && s == 0)
        {
            setPosition(Vector3(px+1, py, 0));
        }
        else if (left && s == 1)
        {
            setPosition(Vector3(px-1, py, 0));
        }
        else
        {
            setPosition(Vector3(px, py, 0));
        }
    }
}

void Gas::move(void *s)
{
    int px = getPosition().x;
    int py = getPosition().y;

    Screen *screen = static_cast<Screen*>(s);
    bool up = screen->isEmpty(px, py-1);
    bool leftUp = screen->isEmpty(px-1, py-1);
    bool rightUp = screen->isEmpty(px+1, py-1);
    bool left = screen->isEmpty(px-1, py);
    bool right = screen->isEmpty(px+1, py);

    int r = rand()%3;
    if (up && r == 0)
    {
        setPosition(Vector3(px, py-1, 0));
    }
    else if(leftUp && r == 1)
    {
        setPosition(Vector3(px-1, py-1, 0));
    }
    else if (rightUp && r == 2)
    {
        setPosition(Vector3(px+1, py-1, 0));
    }
    else
    {
        int s = rand()%2;
        if (right && s == 0)
        {
            setPosition(Vector3(px+1, py, 0));
        }
        else if (left && s == 1)
        {
            setPosition(Vector3(px-1, py, 0));
        }
        else
        {
            setPosition(Vector3(px, py, 0));
        }
    }
}

void Soil::move(void *s)
{
    int px = getPosition().x;
    int py = getPosition().y;
    
    Screen *screen = static_cast<Screen*>(s);
    bool down = screen->isEmpty(px, py+1);
    bool leftDown = screen->isEmpty(px-1, py+1);
    bool rightDown = screen->isEmpty(px+1, py+1);

    if (down || screen->getColor(px, py+1) == Water().getColor())
    {
        setPosition(Vector3(px, py+1, 0));
    }
    else
    {
        if (leftDown)
        {
            setPosition(Vector3(px-1, py+1, 0));
        }
        else if (rightDown)
        {
            setPosition(Vector3(px+1, py+1, 0));
        }
        else
        {
            setPosition(Vector3(px, py, 0));
        }
    }
}

void Fire::move(void *s)
{

}

void Plant::move(void *s)
{
    moves++;
    int px = getPosition().x;
    int py = getPosition().y;
    Screen *screen = static_cast<Screen*>(s);

    if (moves < rand()%100)
    {
        bool up = false;

        // this way plants can grow though the dirt
        for (int i = 0; i < 10; i++)
        {
            if (screen->isEmpty(px, py-i))
            {
                up = true;
            }
        }
        bool leftUp = screen->isEmpty(px-1, py-1);
        bool rightUp = screen->isEmpty(px+1, py-1);
        bool left = screen->isEmpty(px-1, py);
        bool right = screen->isEmpty(px+1, py);

        int r = rand()%3;
        if (up && r == 0)
        {
            setPosition(Vector3(px, py-1, 0));
        }
        else if(leftUp && r == 1)
        {
            setPosition(Vector3(px-1, py-1, 0));
        }
        else if (rightUp && r == 2)
        {
            setPosition(Vector3(px+1, py-1, 0));
        }
        else
        {
            int s = rand()%2;
            if (right && s == 0)
            {
                setPosition(Vector3(px+1, py, 0));
            }
            else if (left && s == 1)
            {
                setPosition(Vector3(px-1, py, 0));
            }
            else
            {
                setPosition(Vector3(px, py, 0));
            }
        }
    }
}
