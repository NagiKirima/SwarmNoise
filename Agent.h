#pragma once
//#ifndef AGENT_H
//#define AGENT_H
#include <iostream>
#include <vector>
using namespace std;
class Agent
{
public:
	double x;					// coords
	double y;					//
								//
	double angle;				// angle of speed vector
	double speed;				// speed of agent
	double range = 30;			// range of audibility
								//
	int Acounter;				// counters;
	int Bcounter;				//
								//
	int node_of_arrive;			// 0 or 1 (A or B)

	Agent();
	void Iteration();
	void Noise(vector<Agent*> &list);
};

//#endif

