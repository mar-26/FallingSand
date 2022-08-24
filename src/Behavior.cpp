#include "Behavior.h"
#include "Particle.h"
#include "Screen.h"

void Fall::update(void *s, void *p)
{
    Particle *particle = static_cast<Particle*>(p);
    Screen *screen = static_cast<Screen*>(s);

    int px = particle->getPosition().x;
    int py = particle->getPosition().y;

    bool down = screen->isEmpty(px, py+1);
    bool left = screen->isEmpty(px-1, py+1);
    bool right = screen->isEmpty(px+1, py+1);

    if (down)
    {
        particle->setPosition(Vector3(px, py+1, 0));
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
            particle->setPosition(Vector3(px-1, py+1, 0));
        }
        else if (right)
        {
            particle->setPosition(Vector3(px+1, py+1, 0));
        }
        else
        {
            particle->setPosition(Vector3(px, py, 0));
        }
    }
}

void Rise::update(void *s, void *p)
{
    Particle *particle = static_cast<Particle*>(p);
    Screen *screen = static_cast<Screen*>(s);

    int px = particle->getPosition().x;
    int py = particle->getPosition().y;

    bool up = screen->isEmpty(px, py-1);
    bool leftUp = screen->isEmpty(px-1, py-1);
    bool rightUp = screen->isEmpty(px+1, py-1);
    bool left = screen->isEmpty(px-1, py);
    bool right = screen->isEmpty(px+1, py);

    if (passive)
    {
        int r = rand()%3;
        if(r == 0)
        {
            particle->setPosition(Vector3(px-1, py, 0));
        }
        else if (r == 1)
        {
            particle->setPosition(Vector3(px+1, py, 0));
        }
        else
        {
            particle->setPosition(Vector3(px, py-1, 0));
        }
    }
    else
    {
        int r = rand()%3;
        if (up && r == 0)
        {
            particle->setPosition(Vector3(px, py-1, 0));
        }
        else if(leftUp && r == 1)
        {
            particle->setPosition(Vector3(px-1, py-1, 0));
        }
        else if (rightUp && r == 2)
        {
            particle->setPosition(Vector3(px+1, py-1, 0));
        }
        else
        {
            int s = rand()%2;
            if (right && s == 0)
            {
                particle->setPosition(Vector3(px+1, py, 0));
            }
            else if (left && s == 1)
            {
                particle->setPosition(Vector3(px-1, py, 0));
            }
            else
            {
                particle->setPosition(Vector3(px, py, 0));
            }
        }
    }
}

void Grow::update(void *s, void *p)
{
    height++;
    Particle *particle = static_cast<Particle*>(p);
    Screen *screen = static_cast<Screen*>(s);

    int px = particle->getPosition().x;
    int py = particle->getPosition().y;

    if (height < rand()%100)
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
            particle->setPosition(Vector3(px, py-1, 0));
        }
        else if(leftUp && r == 1)
        {
            particle->setPosition(Vector3(px-1, py-1, 0));
        }
        else if (rightUp && r == 2)
        {
            particle->setPosition(Vector3(px+1, py-1, 0));
        }
        else
        {
            int s = rand()%2;
            if (right && s == 0)
            {
                particle->setPosition(Vector3(px+1, py, 0));
            }
            else if (left && s == 1)
            {
                particle->setPosition(Vector3(px-1, py, 0));
            }
            else
            {
                particle->setPosition(Vector3(px, py, 0));
            }
        }
    }
}

void Liquid::update(void *s, void *p)
{
    Particle *particle = static_cast<Particle*>(p);
    Screen *screen = static_cast<Screen*>(s);

    int px = particle->getPosition().x;
    int py = particle->getPosition().y;

    bool down = screen->isEmpty(px, py+1);
    bool left = screen->isEmpty(px-1, py);
    bool right = screen->isEmpty(px+1, py);

    if (down)
    {
        particle->setPosition(Vector3(px, py+1, 0));
    }
    else
    {
        int s = rand()%2;
        if (right && s == 0)
        {
            particle->setPosition(Vector3(px+1, py, 0));
        }
        else if (left && s == 1)
        {
            particle->setPosition(Vector3(px-1, py, 0));
        }
        else
        {
            particle->setPosition(Vector3(px, py, 0));
        }
    }
}

void Burn::update(void *s, void *p)
{
    Particle *particle = static_cast<Particle*>(p);
    Screen *screen = static_cast<Screen*>(s);

    int px = particle->getPosition().x;
    int py = particle->getPosition().y;

    Color f = Fire().getColor();
    bool nearFire = (screen->getColor(px-1, py+1) == f) || 
                    (screen->getColor(px-1, py) == f) || 
                    (screen->getColor(px-1, py-1) == f) || 
                    (screen->getColor(px, py-1) == f) || 
                    (screen->getColor(px+1, py-1) == f) || 
                    (screen->getColor(px+1, py) == f) || 
                    (screen->getColor(px+1, py+1) == f) || 
                    (screen->getColor(px, py+1) == f) ? true : false;
    
    if (nearFire)
    {
        particle->setColor(f);
    }
    if (particle->getColor() == f)
    {
        halfLife++;
    }
    if (halfLife > rand()%100)
    {
        particle->setColor(Color(0.7, 0.7, 0.8));
        int r = rand()%10;
        if (r == 0)
        {
            particle->addBehavior(new Fall());
        }
        else
        {
            particle->addBehavior(new Rise(true));
        }
    }
}