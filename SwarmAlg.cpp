#include <iostream>
#include <vector>
#include "Agent.h"
#include "glut.h"
using namespace std;
const int WINDOW_SIZE = 800;
vector<Agent*> swarm(1000);
vector<Node*> listOfNodes;
void Draw()
{
	srand(time(0));
	glClear(GL_COLOR_BUFFER_BIT);
	for (size_t i = 0; i < swarm.size(); i++)
	{
		double change_angle = rand() / double(RAND_MAX) * 0.01 * pi * (-1 + rand() % 2);
		swarm[i]->Iteration(swarm, listOfNodes, change_angle);
	}
	glPointSize(2);
	glBegin(GL_POINTS);
		glColor3f(255, 255, 255);
		for (size_t i = 0; i < swarm.size(); i++)
			glVertex2f(swarm[i]->x, swarm[i]->y);
	glEnd();
	glPointSize(radius);
	glBegin(GL_POINTS);
		for (auto &i : listOfNodes) 
		{
			if(i->type == 2)
				glColor3f(100, 0, 0); // base
			else if(i->type == 1)
				glColor3f(0, 100, 0); // blue
			else
				glColor3f(0, 0, 100); // green
			glVertex2f(i->x, i->y);
		}
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
	
	// nodes list init (random)
	/*int size = rand() % 9 + 2;
	Node* p = 0;
	p = new Node(2, rand() / double(RAND_MAX) * SizeScene, rand() / double(RAND_MAX)* SizeScene, radius, 0.005, rand() / double(RAND_MAX) * SizeScene); // base;
	listOfNodes.push_back(p);
	for (size_t i = 1; i < size; i++)
	{
		p = new Node(rand() % (types - 1), rand() / double(RAND_MAX) * SizeScene, rand() / double(RAND_MAX) * SizeScene, radius, 0.005, rand() / double(RAND_MAX) * SizeScene);
		listOfNodes.push_back(p);
	}*/

	// nodes list init (example)
	
	Node* p = 0;
	p = new Node(2, 25, 25);  // base
	listOfNodes.push_back(p);
	p = new Node(0, 775, 25); // 1-type
	listOfNodes.push_back(p);
	p = new Node(1, 400, 775); // 2-type
	listOfNodes.push_back(p);

	

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

	//clear memory
	for (size_t i = 0; i < swarm.size(); i++)
		delete swarm[i];
	for (size_t i = 0; i < listOfNodes.size(); i++)
		delete listOfNodes[i];
}

