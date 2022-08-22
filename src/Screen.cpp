#include "Screen.h"
#include "Vector3.h"

Screen::Screen()
{
    width = 0;
    height = 0;
    screen = nullptr;
    sand = Color(0.9, 0.8, 0.4);
}

Screen::Screen(int w, int h)
{
    width = w;
    height = h;
    screen = new Color[width*height];

    for (int i = 0; i < width*height; i++)
    {
        screen[i].r = 0;
        screen[i].g = 0;
        screen[i].b = 0;
    }
}

bool Screen::isEmpty(int x, int y)
{
    if (y >= height)
    {
        return false;
    }
    else if (y <= 0)
    {
        return false;
    }
    else if (x >= width)
    {
        return false;
    }
    else if (x <= 0)
    {
        return false;
    }

    Color c = screen[getIndex(x, y)];
    if (!(c == black))
    {
        return false;
    }
    return true;
}

int Screen::getIndex(int x, int y)
{
    return (height-y)*width+x;
}

void Screen::clearScreen()
{
    for (int i = 0; i < width*height; i++)
    {
        if (screen[i] == Plant().getColor())
        {
        }
        else
        {
            screen[i] = black;
        }
    }
}

void Screen::update()
{
    clearScreen();
}

void Screen::placeParticle(Particle* p)
{
    int index = getIndex(p->getPosition().x, p->getPosition().y);
    screen[index] = p->getColor();
}

void Screen::placeColor(int x, int y, Color c)
{
    screen[getIndex(x, y)] = c;
}

void Screen::draw()
{
	glDrawPixels(width, height, GL_RGB, GL_FLOAT, screen);
}

Color Screen::getColor(int x, int y)
{
    return screen[getIndex(x, y)];
}

void Screen::setWidth(int w)
{
    width = w;
}

void Screen::setHeight(int h)
{
    height = h;
}

int Screen::getWidth()
{
    return width;
}

int Screen::getHeight()
{
    return height;
}

Screen::~Screen()
{
}
