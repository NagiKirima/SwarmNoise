#include "Agent.h"
#include <cmath>
using namespace std;

//extern const int SizeScene;
//extern double x_a;											// coords of nodes
//extern double y_a;											//
//extern double x_b;											//
//extern double y_b;											//
//extern const double radius;									// node radius

double const pi = 3.14159265358979323846;
const int SizeScene = 500;
// ! the movement occurs in the 1 coordinate plane !
double x_a = rand() / double(RAND_MAX) * SizeScene;
double y_a = rand() / double(RAND_MAX) * SizeScene;
double x_b = rand() / double(RAND_MAX) * SizeScene;
double y_b = rand() / double(RAND_MAX) * SizeScene;
const double radius = 10;

Agent::Agent() 
{
	x = rand() / double(RAND_MAX) * SizeScene;				// rand coords (0..scenesize)
	y = rand() / double(RAND_MAX) * SizeScene;				//
	angle = rand() / double(RAND_MAX) * 2 * pi;				// rand vector of speed
	speed = rand() / double(RAND_MAX) * 5;					// speed range is 0 .. 5
	Acounter = rand() % 450 + 50;							// rand range to nodes
	Bcounter = rand() % 450 + 50;							//
	node_of_arrive = rand() % 2;							// rand target of travel
}

void Agent::Iteration() 
{
	Acounter++;												// inc counters
	Bcounter++;
	// check the walls
	if (x + cos(angle) <= 0 || y + sin(angle) <= 0 || x + cos(angle) >= SizeScene || y + sin(angle) >= SizeScene)
		angle += pi;
	x += cos(angle) * speed;								// rotate in world
	y += sin(angle) * speed;

	// if curent coords == coords of node:
	if (((x - x_a) * (x - x_a) + (y - y_a) * (y - y_a)) <= radius * radius && node_of_arrive == 0)
	{
		Acounter = 0;
		node_of_arrive = 1;
		angle += pi;
	}
	else if (((x - x_b) * (x - x_b) + (y - y_b) * (y - y_b)) <= radius * radius && node_of_arrive == 1)
	{
		Bcounter = 0;
		node_of_arrive = 0;
		angle += pi;
	}
}

void Agent::Noise(vector<Agent*> &list) 
{
	int rangeToA = Acounter + int(range);
	int rangeToB = Bcounter + int(range);
	for (size_t i = 0; i < list.size(); i++) 
	{
		if (this != list[i]) 
		{
			if (pow(this->x - list[i]->x, 2) + pow(this->y - list[i]->y, 2) <= range * range)
			{
				if (this->Acounter < list[i]->Acounter)
				{
					list[i]->Acounter = this->Acounter;
					if (list[i]->node_of_arrive == 0) 
					{
						angle = tan((this->x - list[i]->x)/(this->y - list[i]->y));
					}
				}
				if (this->Bcounter < list[i]->Bcounter)
				{
					list[i]->Bcounter = this->Bcounter;
					if (list[i]->node_of_arrive == 1)
					{
						angle = tan((this->x - list[i]->x) / (this->y - list[i]->y));
					}
				}
			}
		}
	}
}