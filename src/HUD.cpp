#include "HUD.h"

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

HUD::HUD(ParticleSystem *partS)
{
    ps = partS;
    ps->registerObserver(this);
    numParticles = "# particles: " + ps->getNumParticals();
    brushSize = "Brush size: " + ps->getBrushSize();
    element = "Element: " + ps->getElement();
}

void HUD::update()
{
    numParticles = "# particles: " + ps->getNumParticals();
    brushSize = "Brush size: " + ps->getBrushSize();
    element = "Element: " + ps->getElement();
}

void HUD::drawString(int x, int y, float size, std::string text)
{
    glPushMatrix();
	glColor3f(1, 1, 1);
    glTranslatef(x, y, 0);
    glScalef(size, size, 0);
	glRotatef(180, 1, 0, 0);
    for (int i = 0; i < text.length(); i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
    }
    glPopMatrix();
}

void HUD::draw()
{
    drawString(0, 25, 0.1, numParticles);
    drawString(0, 50, 0.1, brushSize);
    drawString(0, 75, 0.1, element);
}
