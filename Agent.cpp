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

void Agent::Iteration(vector<Agent*>& list, vector<Node*>& listOfNodes, double Rand)
{
	for (auto& i : counters)								//increase all counters
		i++;

	//checking the walls
	if (x + cos(angle) * speed <= 0 || y + sin(angle) * speed <= 0 || x + cos(angle) * speed >= SizeScene 
		|| y + sin(angle) * speed >= SizeScene)				
		angle += pi;

	x += cos(angle) * speed;								// rotating in world
	y += sin(angle) * speed;
	angle += Rand;

	for (int i = 0; i < listOfNodes.size(); i++)
	{
		if (pow(x - listOfNodes[i]->x, 2) + pow(y - listOfNodes[i]->y, 2) <= pow(listOfNodes[i]->radius, 2))
		{
			counters[listOfNodes[i]->type] = 0;
			//if (node_of_arrive == listOfNodes[i].type)      //testing, mb correct
				//angle += pi;

			//random choise after finded needed node
			if (listOfNodes[i]->type == types - 1 && listOfNodes[i]->type == node_of_arrive)
			{
				node_of_arrive = rand() % 2;
			}
			else if (listOfNodes[i]->type == node_of_arrive)
			{
				int r = node_of_arrive;
				while (r == node_of_arrive)
				{
					r = rand() % types;
				}
				node_of_arrive = r;
			}
		}
	}
	Noise(list, listOfNodes);
}

void Agent::Noise(vector<Agent*> &list, vector<Node*>& listOfNodes)
{
	//init rangelist
	vector<int> rangelist;
	for (auto i : counters)
		rangelist.push_back(i + range);

	for (size_t i = 0; i < list.size(); i++)
	{
		if (this != list[i])
			for (size_t j = 0; j < rangelist.size(); j++)
			{
				if (rangelist[j] < list[i]->counters[j] && (pow(this->x - list[i]->x, 2) + pow(this->y - list[i]->y, 2) <= range * range))
				{
					list[i]->counters[j] = rangelist[j];
					if (node_of_arrive == list[i]->node_of_arrive)
					{
						//rotating towards noise 
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