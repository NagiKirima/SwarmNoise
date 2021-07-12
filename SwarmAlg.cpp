#include <iostream>
#include <vector>
#include "Agent.h"
#include "glut.h"
using namespace std;
const int WINDOW_SIZE = 800;
vector<Agent*> swarm;
vector<Node*> listOfNodes;
void Draw()
{
	srand(time(0));
	glClear(GL_COLOR_BUFFER_BIT);
	// iterations
	for (size_t i = 0; i < listOfNodes.size(); i++)
	{
		double change_angle = rand() / double(RAND_MAX) * 0.5 * pi * (-1 + rand() % 2);
		listOfNodes[i]->Iteration(change_angle);
	}
	for (size_t i = 0; i < swarm.size(); i++)
	{
		double change_angle = rand() / double(RAND_MAX) * 0.01 * pi * (-1 + rand() % 2);
		swarm[i]->Iteration(swarm, listOfNodes, change_angle);
	}
	// drawing world
	glPointSize(2);
	glBegin(GL_POINTS);
		for (size_t i = 0; i < swarm.size(); i++)
		{
			if (swarm[i]->node_of_arrive == 2)
				glColor3f(100, 0, 0); // red
			else if (swarm[i]->node_of_arrive == 1)
				glColor3f(0, 100, 0); // blue
			else
				glColor3f(0, 0, 100); // green
			glVertex2f(swarm[i]->x, swarm[i]->y);
		}
	glEnd();
	glPointSize(radius);
	glBegin(GL_POINTS);
		for (auto &i : listOfNodes) 
		{
			if(i->type == 2)
				glColor3f(100, 0, 0); // red
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
	glOrtho(0, SizeScene, 0, SizeScene, -1, 1);
}
size_t GetSwarmSize() 
{
	size_t size;
	while (!(cin >> size) || (cin.peek() != '\n') || size < 500 || size > 2000)
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Введите корректное число:\t";
	}
	return size;
}
double GetNoise()
{
	double size;
	while (!(cin >> size) || (cin.peek() != '\n') || size < 20 || size > 50)
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Введите корректное число:\t";
	}
	return size;
}
int main(int argc, char* argv[])
{
	system("color 06");
	srand(time(0));
	setlocale(LC_ALL, "rus");

	// swarm init
	cout << "Введите размер роя, влияет на производительность и на скорость нахождения оптимального пути (500...2000)" << endl;
	size_t tempsize = GetSwarmSize();
	cout << "Введите радиус крика - влияет на скорость нахождения решения (20...50)" << endl;
	double noise = GetNoise();

	for (size_t i = 0; i < tempsize; i++) 
	{
		Agent* p = new Agent(noise);
		swarm.push_back(p);
	}
	// nodes init
	for (size_t i = 0; i < types; i++)
	{
		Node* p = new Node(i, rand() / double(RAND_MAX) * SizeScene, rand() / double(RAND_MAX) * SizeScene);
		listOfNodes.push_back(p);
	}

	// window init
	glutInit(&argc, argv);
	glutInitWindowPosition(500, 100);
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

