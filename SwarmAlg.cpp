#include <iostream>
#include <vector>
#include "Agent.h"
#include "glut.h"
using namespace std;
const int WINDOW_SIZE = 800;
vector<Agent*> swarm(500);

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (size_t i = 0; i < swarm.size(); i++)
	{
		swarm[i]->Iteration(swarm);
		//swarm[i]->Noise(swarm);
	}
	glPointSize(2);
	glBegin(GL_POINTS);
		glColor3f(255, 255, 255);
		for (size_t i = 0; i < swarm.size(); i++)
			glVertex2f(swarm[i]->x, swarm[i]->y);
	glEnd();
	glPointSize(radius);
	glColor3f(0, 0, 100);
	glBegin(GL_POINTS);
		glVertex2f(x_a, y_a);
		glVertex2f(x_b, y_b);
	glEnd();
	glutSwapBuffers();
	
}
void Timer(int) 
{
	glutPostRedisplay();
	glutTimerFunc(10, Timer, 0);
}
void Init()
{
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SizeScene, 0, SizeScene, -5, 5);
}
int main(int argc, char* argv[])
{
	srand(time(0));

	// swarm init
	for (size_t i = 0; i < swarm.size(); i++) 
		swarm[i] = new Agent();

	// window init
	glutInit(&argc, argv);
	glutInitWindowPosition(50, 10);
	glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE); 
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); 
	glutCreateWindow("Swarm"); 
	glutDisplayFunc(Draw);
	glutTimerFunc(10, Timer, 0);
	Init();
	glutMainLoop();
	for (size_t i = 0; i < swarm.size(); i++)
		delete swarm[i];
}

