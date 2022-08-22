#include <iostream>

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

#include "ParticleSystem.h"
#include "HUD.h"

int windowWIDTH = 800, windowHEIGHT = 600;
int screenWIDTH = 800, screenHEIGHT = 600;
bool mousePressed = false;
bool mouseMove = false;
int mouseX, mouseY;

ParticleSystem *ps;
HUD *ui;

void init();
void update();
void display();
void keyboard (unsigned char, int, int);
void mouse(int, int, int, int);
void mousePassive(int, int);
void reshape(int, int);

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
    srand(time(NULL));
	ps = new ParticleSystem(screenWIDTH, screenHEIGHT);
	ui = new HUD(ps);
}

void update(int dt)
{
	ps->update();
	glutTimerFunc(1, update, dt);
	glutPostRedisplay();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

	if (mousePressed && !mouseMove)
	{
		ps->addParticle(mouseX, mouseY);
	}

	ps->draw();
	ui->draw();

	glFlush();
    glutSwapBuffers();
}

void keyboard (unsigned char key, int x, int y)
{
	if ((int)key == 27)
	{
		exit(0);
	}
	else
	{
		ps->keyPressed(key);
	}
}

void specialKeys(int key, int x, int y)
{
	ps->keyPressed(key);
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseX = x;
			mouseY = y;
			mousePressed = true;
		}
		else if (state == GLUT_UP)
		{
			mousePressed = false;
			mouseMove = false;
		}
	}
}

void mousePassive(int x, int y)
{
	if (mousePressed)
	{
		ps->addParticle(x, y);
	}
		mouseMove = true;
}

void reshape(int w, int h)
{
	glViewport(0, 0, windowWIDTH, windowHEIGHT);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //set the coordinate system, with the origin in the top left
    gluOrtho2D(0, windowWIDTH, windowHEIGHT, 0);
    glMatrixMode(GL_MODELVIEW);
	
	windowWIDTH = w;
	windowHEIGHT = h;

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(windowWIDTH, windowHEIGHT);
	glutInitWindowPosition(100, 0);
	glutCreateWindow("Falling Sand");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys);
	glutMouseFunc(mouse);
	glutMotionFunc(mousePassive);
	glutTimerFunc(1, update, 1);
	glutMainLoop();

	return 0;
}
