#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
    screen = new Screen();
    observers = std::list<Observer*>();
    brushSize = 10;
    element = "Sand";
}

ParticleSystem::ParticleSystem(int width, int height)
{
    screen = new Screen(width, height);
    observers = std::list<Observer*>();
    brushSize = 10;
    element = "Sand";

    for (int i = 0; i < height; i++)
    {
        particles.push_back(std::vector<Particle*>());
    }
}

void ParticleSystem::draw()
{
    for (int i = 0; i < particles.size(); i++)
    {
        for (int j = 0; j < particles[i].size(); j++)
        {
            screen->placeParticle(particles[i][j]);
        }
    }
    screen->draw();
}

void ParticleSystem::update()
{
    for (int i = 0; i < particles.size(); i++)
    {
        for (int j = 0; j < particles[i].size(); j++)
        {
            if (particles[i][j]->getPosition().y > screen->getHeight() || particles[i][j]->getPosition().y < 0)
            {
                particles[i].erase(particles[i].begin()+j);
            }
            else
            {
                particles[i][j]->update(screen);
            }
        }
    }
    //sortVector();
    screen->update();
    notifyObservers();
}

void ParticleSystem::keyPressed(unsigned char key)
{
    switch(key)
    {
        case 's':
            element = "Sand";
            break;
        case 'S':
            element = "Soil";
            break;
        case 'w':
            element = "Water";
            break;
        case 'c':
            element = "Concrete";
            break;
        case 'e':
            element = "Eraser";
            break;
        case 'g':
            element = "Gas";
            break;
        case 'f':
            element = "Fire";
            break;
        case 'p':
            element = "Plant";
            break;
        default:
            element = "Sand";
            break;
    }
    notifyObservers();
}

void ParticleSystem::keyPressed(int key)
{
    if (key == 101)
    {
        brushSize++;
    }
    else if (key == 103)
    {
        brushSize--;
    }
    notifyObservers();
}

void ParticleSystem::addParticle(int x, int y)
{
    if (element == "Sand")
    {
        for (int i = 0; i < brushSize; i++)
        {
            for (int j = 0; j < brushSize; j++)
            {
                int r = rand()%4;
                if (r == 0)
                {
                    particles[y+i].push_back(new Sand(x-j, y-i));
                }
            }
        }
    }
    else if (element == "Soil")
    {
        for (int i = 0; i < brushSize; i++)
        {
            for (int j = 0; j < brushSize; j++)
            {
                int r = rand()%4;
                if (r == 0)
                {
                    particles[y+i].push_back(new Soil(x-j, y-i));
                }
            }
        }
    }
    else if (element == "Concrete")
    {
        for (int i = 0; i < brushSize; i++)
        {
            for (int j = 0; j < brushSize; j++)
            {
                particles[y+i].push_back(new Wall(x-j, y-i));
            }
        }
    }
    else if (element == "Eraser")
    {
        for (int i = 0; i < brushSize; i++)
        {
            for (int j = 0; j < brushSize; j++)
            {
                eraseParticle(x-j, y-i);
            }
        }
    }
    else if (element == "Water")
    {
        for (int i = 0; i < brushSize; i++)
        {
            for (int j = 0; j < brushSize; j++)
            {
                particles[y+i].push_back(new Water(x-j, y-i));
            }
        }
    }
    else if (element == "Gas")
    {
        for (int i = 0; i < brushSize; i++)
        {
            for (int j = 0; j < brushSize; j++)
            {
                int r = rand()%4;
                if (r == 0)
                {
                    particles[y+i].push_back(new Gas(x-j, y-i));
                }
            }
        }
    }
    else if (element == "Fire")
    {
        for (int i = 0; i < brushSize; i++)
        {
            for (int j = 0; j < brushSize; j++)
            {
                if (i > brushSize/2)
                {
                    int r2 = rand()%10;
                    if (r2 == 0)
                    {
                        int offsetY = rand()%10;
                        int offsetX = rand()%10;
                        screen->placeColor(x-offsetX, y-i-offsetY, Fire().getColor());
                    }
                }
                else
                {
                    int r = rand()%5;
                    if (r == 0)
                    {
                        screen->placeColor(x-j, y-i, Fire().getColor());
                    }
                }
            }
        }
    }
    else if (element == "Plant")
    {
        for (int i = 0; i < brushSize; i++)
        {
            for (int j = 0; j < brushSize; j++)
            {
                int r = rand()%10;
                if (r == 0)
                {
                    particles[y+i].push_back(new Plant(x-j, y-i));
                }
            }
        }
    }
    else
    {
        particles[y].push_back(new Sand(x, y));
    }
    notifyObservers();
}

// erases particle based on its position
void ParticleSystem::eraseParticle(int x, int y)
{
    if (particles.size() < 1)
    {
        return;
    }
    int i;
    bool found = false;
    for (i = 0; i < particles[y].size(); i++)
    {
        if (particles[y][i]->getPosition().x == x)
        {
            found = true;
            break;
        }
    }
    if (found)
    {
        particles[y].erase(particles[y].begin()+i);
    }
    screen->placeColor(x, y, Color(0, 0, 0));
}

// sorts the vector vectors so that erase will work properly
void ParticleSystem::sortVector()
{
    int j;
    for (int i = 0; i < particles.size(); i++)
    {
        for (j = 0; j < particles[i].size(); i++)
        {
            if (particles[i][j] == NULL)
            {
                particles[i].erase(particles[i].begin()+j);
            }
            if (particles[i][j]->getPosition().y != i)
            {
                particles[particles[i][j]->getPosition().y].push_back(particles[i][j]);
                particles[i].erase(particles[i].begin()+j);
            }
        }
    }
}

std::string ParticleSystem::getNumParticals()
{
    int total = 0;
    for (int i = 0; i < particles.size(); i++)
    {
        total += particles[i].size();
    }
    return std::to_string(total);
}

std::string ParticleSystem::getBrushSize()
{
    return std::to_string(brushSize);
}

std::string ParticleSystem::getElement()
{
    return element;
}

void ParticleSystem::registerObserver(Observer *o)
{
	observers.push_front(o);
}

void ParticleSystem::removeObserver(Observer *o)
{
	std::list<Observer*>::iterator it;
	for (it = observers.begin(); it != observers.end(); it++)
	{
		Observer* temp = *it;
		if (temp == o)
		{
			observers.erase(it);
		}
	}
}

void ParticleSystem::notifyObservers()
{
	std::list<Observer*>::iterator it;
	for (it = observers.begin(); it != observers.end(); it++)
	{
		Observer* temp = *it;
		temp->update();
	}
}

ParticleSystem::~ParticleSystem()
{
    free(screen);
    for (int i = 0; i < particles.size(); i++)
    {
        for (int j = 0; j < particles[i].size(); i++)
        {
            free(particles[i][j]);
        }
    }
    std::list<Observer*>::iterator it;
    for (it = observers.begin(); it != observers.end(); it++)
    {
        free(*it);
    }
}
