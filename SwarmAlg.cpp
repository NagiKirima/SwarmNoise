#include <iostream>
#include <vector>
#include "Agent.h"
#include "glut.h"
using namespace std;
const int WINDOW_SIZE = 800;
vector<Agent*> swarm(1000);

void Draw()
{
	srand(time(0));
	glClear(GL_COLOR_BUFFER_BIT);
	for (size_t i = 0; i < swarm.size(); i++)
	{
		double change_angle = rand() / double(RAND_MAX) * 0.01 * pi * (-1 + rand() % 2);
		swarm[i]->Iteration(swarm, change_angle);
	}
	glPointSize(2);
	glBegin(GL_POINTS);
		glColor3f(255, 255, 255);
		for (size_t i = 0; i < swarm.size(); i++)
			glVertex2f(swarm[i]->x, swarm[i]->y);
	glEnd();
	glPointSize(radius);
	glBegin(GL_POINTS);
		glColor3f(0, 0, 100);
		glVertex2f(x_a, y_a);
		glColor3f(0, 100, 0);
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
	//x_a = rand() / double(RAND_MAX) * SizeScene;
	//y_a = rand() / double(RAND_MAX) * SizeScene;
	//x_b = rand() / double(RAND_MAX) * SizeScene;
	//y_b = rand() / double(RAND_MAX) * SizeScene;
	// swarm init
	for (size_t i = 0; i < swarm.size(); i++)
		swarm[i] = new Agent();

	int Acount = 0, Bcount = 0;
	for (auto i : swarm) 
	{
		if (i->node_of_arrive == 0)
			Acount++;
		else
			Bcount++;
	}
	cout << "A:" << Acount << endl << "B:" << Bcount << endl;
	//for (size_t i = 0; i < swarm.size(); i++) 
	//{
	//	swarm[i]->x = rand() / double(RAND_MAX) * SizeScene;				// rand coords (0..scenesize)
	//	swarm[i]->y = rand() / double(RAND_MAX) * SizeScene;				//
	//	swarm[i]->angle = rand() / double(RAND_MAX) * 2 * pi;				// rand vector of speed
	//	swarm[i]->speed = rand() / double(RAND_MAX) * 3;			// speed range 
	//	swarm[i]->Acounter = rand() % (SizeScene - start) + start; 		// rand range to nodes
	//	swarm[i]->Bcounter = rand() % (SizeScene - start) + start;		//
	//	swarm[i]->node_of_arrive = rand() % 2;							// rand target of travel
	//}


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

