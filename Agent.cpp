#include "Agent.h"
using namespace std;

double const pi = 3.14159265358979323846;
int start = 200;

Agent::Agent() 
{
	x = rand() / double(RAND_MAX) * SizeScene;				// rand coords (0..scenesize)
	y = rand() / double(RAND_MAX) * SizeScene;				//
	angle = rand() / double(RAND_MAX) * 2 * pi;				// rand vector of speed
	speed = rand() / double(RAND_MAX) * 1.5 + 0.5;			// speed range 
	Acounter = rand() % (SizeScene - start) + start; 		// rand range to nodes
	Bcounter = rand() % (SizeScene - start) + start;		//
	node_of_arrive = rand() % 2;							// rand target of travel
}

void Agent::Iteration(vector<Agent*>& list)
{
	Acounter++;												// inc counters
	Bcounter++;

	// check the walls
	if (x + cos(angle) * speed <= 0 || y + sin(angle) * speed <= 0 || x + cos(angle) * speed >= SizeScene || y + sin(angle) * speed >= SizeScene)
		angle += pi;


	x += cos(angle) * speed;								// rotate in world
	y += sin(angle) * speed;
	angle += (-1 + rand() % 2) * pi / (rand() % 500 + 100);

	// if curent coords == coords of node:
	if (((x - x_a) * (x - x_a) + (y - y_a) * (y - y_a)) <= radius * radius)
	{
		Acounter = 0;
		if (node_of_arrive == 0)
		{
			node_of_arrive = 1;
			angle += pi;
			Noise(list);
		}
	}
	if (((x - x_b) * (x - x_b) + (y - y_b) * (y - y_b)) <= radius * radius)
	{
		Bcounter = 0;
		if (node_of_arrive == 1)
		{
			node_of_arrive = 0;
			angle += pi;
			Noise(list);
		}
	}
	//Noise(list);
	Ear(list);
}

void Agent::Noise(vector<Agent*> &list) 
{
	int rangeToA = Acounter + range;
	int rangeToB = Bcounter + range;
	for (size_t i = 0; i < list.size(); i++) 
	{
		if (this != list[i]) 
			if (pow(this->x - list[i]->x, 2) + pow(this->y - list[i]->y, 2) <= range * range)
			{
				if (rangeToA < list[i]->Acounter)
				{
					list[i]->Acounter = rangeToA;
					if (list[i]->node_of_arrive == 0) 
						list[i]->angle = atan((this->x - list[i]->x)/(this->y - list[i]->y));
				}
				if (rangeToB < list[i]->Bcounter)
				{
					list[i]->Bcounter = rangeToB;
					if (list[i]->node_of_arrive == 1)
						list[i]->angle = atan((this->x - list[i]->x) / (this->y - list[i]->y));
				}
			}
	}
}
void Agent::Ear(vector<Agent*>& list) 
{

	for (size_t i = 0; i < list.size(); i++)
	{
		if (this != list[i])
		{
			int rangeToA = list[i]->Acounter + range;
			int rangeToB = list[i]->Bcounter + range;
			if (pow(this->x - list[i]->x, 2) + pow(this->y - list[i]->y, 2) <= range * range)
			{
				if (this->Acounter > rangeToA)
				{
					this->Acounter = rangeToA;
					if (this->node_of_arrive == 0)
						this->angle = atan((list[i]->x - this->x) / (list[i]->y - this->y));
				}
				if (this->Bcounter > rangeToB)
				{
					this->Bcounter = rangeToB;
					if (list[i]->node_of_arrive == 1)
						list[i]->angle = atan((list[i]->x - this->x) / (list[i]->y - this->y));
				}
			}
		}
	}
}