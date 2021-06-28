#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include "Node.h"
using namespace std;

class Agent
{
public:
	double x;						// coords
	double y;						//
									//
	double angle;					// angle of speed vector
	double speed;					// speed of agent
	double range = 35;					// range of audibility
									
	vector<int> counters;			// counterlist			
	int node_of_arrive;				// arrive node

	Agent();
	virtual void Iteration(vector<Agent*>& list, vector<Node*> &listOfNodes, double Rand);
	void Noise(vector<Agent*> &list, vector<Node*>& listOfNodes);
};

