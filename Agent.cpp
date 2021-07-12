#include "Agent.h"
using namespace std;

Agent::Agent()
{
	x = rand() / double(RAND_MAX) * SizeScene;				// rand coords (0..scenesize)
	y = rand() / double(RAND_MAX) * SizeScene;				//
	angle = rand() / double(RAND_MAX) * 2 * pi;				// rand vector of speed
	speed = rand() / double(RAND_MAX) * 3;
	node_of_arrive = rand() % types;						// rand type of arrive
	counters.assign(types, SizeScene);
}
Agent::Agent(double noise) : Agent()
{
	range = noise;
}
void Agent::Iteration(vector<Agent*>& list, vector<Node*>& listOfNodes, double Rand)
{
	for (auto& i : counters)								//increase all counters
		i++;
	// check the walls
	if (x + cos(angle) * speed <= 0 || y + sin(angle) * speed <= 0 || x + cos(angle) * speed >= SizeScene || y + sin(angle) * speed >= SizeScene)
		angle += pi;


	x += cos(angle) * speed;								// rotate in world
	y += sin(angle) * speed;
	angle += Rand;

	// if curent coords == coords of node:
	if (((x - listOfNodes[0]->x) * (x - listOfNodes[0]->x) + (y - listOfNodes[0]->y) * (y - listOfNodes[0]->y)) <= listOfNodes[0]->radius)
	{
		counters[0] = 0;
		if (node_of_arrive == 0)
		{
			int r = node_of_arrive;
			while (r == node_of_arrive)
				r = rand() % types;
			node_of_arrive = r;
			angle += pi;
		}
	}
	if (((x - listOfNodes[1]->x) * (x - listOfNodes[1]->x) + (y - listOfNodes[1]->y) * (y - listOfNodes[1]->y)) <= listOfNodes[1]->radius)
	{
		counters[1] = 0;
		if (node_of_arrive == 1)
		{
			int r = node_of_arrive;
			while (r == node_of_arrive)
				r = rand() % types;
			node_of_arrive = r;
			angle += pi;
		}
	}
	if (((x - listOfNodes[2]->x) * (x - listOfNodes[2]->x) + (y - listOfNodes[2]->y) * (y - listOfNodes[2]->y)) <= listOfNodes[2]->radius)
	{
		counters[2] = 0;
		if (node_of_arrive == 2)
		{
			int r = node_of_arrive;
			while (r == node_of_arrive)
				r = rand() % types;
			node_of_arrive = r;
			angle += pi;
		}
	}
	Noise(list, listOfNodes);
}

void Agent::Noise(vector<Agent*> &list, vector<Node*>& listOfNodes)
{
	int rangeToA = counters[0] + range;
	int rangeToB = counters[1] + range;
	int rangeToC = counters[2] + range;

	for (size_t i = 0; i < list.size(); i++)
	{
		if (this != list[i])
			if (pow(this->x - list[i]->x, 2) + pow(this->y - list[i]->y, 2) <= range * range)
			{

				if (rangeToA < list[i]->counters[0])
				{
					list[i]->counters[0] = rangeToA;
					if (list[i]->node_of_arrive == 0)
					{
						double shift_angle = 0;
						if (this->y > list[i]->y && this->x > list[i]->x)
						{
							shift_angle = atan((this->y - list[i]->y) / (this->x - list[i]->x));
						}
						else if ((this->y < list[i]->y && this->x < list[i]->x))
						{
							shift_angle = atan((this->y - list[i]->y) / (this->x - list[i]->x)) + pi;
						}
						else if ((this->y < list[i]->y && this->x > list[i]->x))
						{
							shift_angle = atan((this->y - list[i]->y) / (this->x - list[i]->x));
						}
						else if ((this->y > list[i]->y && this->x < list[i]->x))
						{
							shift_angle = atan((this->y - list[i]->y) / (this->x - list[i]->x)) + pi;
						}
						list[i]->angle = shift_angle;
					}
				}
				if (rangeToB < list[i]->counters[1])
				{
					list[i]->counters[1] = rangeToB;
					if (list[i]->node_of_arrive == 1)
					{
						double shift_angle = 0;
						if (this->y > list[i]->y && this->x > list[i]->x)
						{
							shift_angle = atan((this->y - list[i]->y) / (this->x - list[i]->x));
						}
						else if ((this->y < list[i]->y && this->x < list[i]->x))
						{
							shift_angle = atan((this->y - list[i]->y) / (this->x - list[i]->x)) + pi;
						}
						else if ((this->y < list[i]->y && this->x > list[i]->x))
						{
							shift_angle = atan((this->y - list[i]->y) / (this->x - list[i]->x));
						}
						else if ((this->y > list[i]->y && this->x < list[i]->x))
						{
							shift_angle = atan((this->y - list[i]->y) / (this->x - list[i]->x)) + pi;
						}
						list[i]->angle = shift_angle;
					}
				}
				if (rangeToC < list[i]->counters[2])
				{
					list[i]->counters[2] = rangeToC;
					if (list[i]->node_of_arrive == 2)
					{
						double shift_angle = 0;
						if (this->y > list[i]->y && this->x > list[i]->x)
						{
							shift_angle = atan((this->y - list[i]->y) / (this->x - list[i]->x));
						}
						else if ((this->y < list[i]->y && this->x < list[i]->x))
						{
							shift_angle = atan((this->y - list[i]->y) / (this->x - list[i]->x)) + pi;
						}
						else if ((this->y < list[i]->y && this->x > list[i]->x))
						{
							shift_angle = atan((this->y - list[i]->y) / (this->x - list[i]->x));
						}
						else if ((this->y > list[i]->y && this->x < list[i]->x))
						{
							shift_angle = atan((this->y - list[i]->y) / (this->x - list[i]->x)) + pi;
						}
						list[i]->angle = shift_angle;
					}
				}
			}
	}
}