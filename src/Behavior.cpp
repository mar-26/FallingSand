#include "Behavior.h"
#include "Particle.h"
#include "ParticleSystem.h"

void Fall::update(void *s, void *p)
{
    Particle *particle = static_cast<Particle*>(p);
    ParticleSystem *ps = static_cast<ParticleSystem*>(s);

    int px = particle->getPosition().x;
    int py = particle->getPosition().y;

    bool down = ps->isEmpty(px, py+1);
    bool left = ps->isEmpty(px-1, py+1);
    bool right = ps->isEmpty(px+1, py+1);

    if (down || ps->getColor(px, py+1) == Water().getColor())
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
    ParticleSystem *ps = static_cast<ParticleSystem*>(s);

    int px = particle->getPosition().x;
    int py = particle->getPosition().y;

    bool up = ps->isEmpty(px, py-1);
    bool leftUp = ps->isEmpty(px-1, py-1);
    bool rightUp = ps->isEmpty(px+1, py-1);
    bool left = ps->isEmpty(px-1, py);
    bool right = ps->isEmpty(px+1, py);

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
    ParticleSystem *ps = static_cast<ParticleSystem*>(s);

    int px = particle->getPosition().x;
    int py = particle->getPosition().y;

    if (height < rand()%100)
    {
        bool up = false;

        // this way plants can grow though the dirt
        for (int i = 0; i < 10; i++)
        {
            if (ps->isEmpty(px, py-i))
            {
                up = true;
            }
        }
        bool leftUp = ps->isEmpty(px-1, py-1);
        bool rightUp = ps->isEmpty(px+1, py-1);
        bool left = ps->isEmpty(px-1, py);
        bool right = ps->isEmpty(px+1, py);

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
    ParticleSystem *ps = static_cast<ParticleSystem*>(s);

    int px = particle->getPosition().x;
    int py = particle->getPosition().y;

    bool down = ps->isEmpty(px, py+1);
    bool left = ps->isEmpty(px-1, py);
    bool right = ps->isEmpty(px+1, py);

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
    ParticleSystem *ps = static_cast<ParticleSystem*>(s);

    int px = particle->getPosition().x;
    int py = particle->getPosition().y;

    Color f = Fire().getColor();
    bool nearFire = (ps->getColor(px-1, py+1) == f) || 
                    (ps->getColor(px-1, py) == f) || 
                    (ps->getColor(px-1, py-1) == f) || 
                    (ps->getColor(px, py-1) == f) || 
                    (ps->getColor(px+1, py-1) == f) || 
                    (ps->getColor(px+1, py) == f) || 
                    (ps->getColor(px+1, py+1) == f) ||
                    (ps->getColor(px, py+1) == f) ? true : false;
    
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
        particle->addBehavior(new Rise(true));
    }
}

void Melt::update(void *s, void *p)
{
    Particle *particle = static_cast<Particle*>(p);
    ParticleSystem *ps = static_cast<ParticleSystem*>(s);

    int px = particle->getPosition().x;
    int py = particle->getPosition().y;

    Color f = Fire().getColor();
    bool nearFire = (ps->getColor(px-1, py+1) == f) || 
                    (ps->getColor(px-1, py) == f) || 
                    (ps->getColor(px-1, py-1) == f) || 
                    (ps->getColor(px, py-1) == f) || 
                    (ps->getColor(px+1, py-1) == f) || 
                    (ps->getColor(px+1, py) == f) || 
                    (ps->getColor(px+1, py+1) == f) ||
                    (ps->getColor(px, py+1) == f) ? true : false;

    if (nearFire)
    {
        particle->setColor(Water().getColor());
        particle->addBehavior(new Liquid());
        particle->removeBehavior(this);
    }
}