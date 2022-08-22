#ifndef COLOR_H
#define COLOR_H

#include <iostream>

struct Color
{
    float r;
    float g;
    float b;

    Color() : r(0), g(0), b(0){}
    Color(float r, float g, float b) : r(r), g(g), b(b){}

    bool operator==(const Color &c)
    {
        return r == c.r && g == c.g && b == c.b;
    }

};

#endif