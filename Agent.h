#pragma once
#ifndef AGENT_H
#define AGENT_H
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
const int SizeScene = 800;
static double x_a = rand() / double(RAND_MAX) * SizeScene;
static double y_a = rand() / double(RAND_MAX) * SizeScene;
static double x_b = rand() / double(RAND_MAX) * SizeScene;
static double y_b = rand() / double(RAND_MAX) * SizeScene;
static const double radius = 10;
class Agent
{
public:
	double x;					// coords
	double y;					//
								//
	double angle;				// angle of speed vector
	double speed;				// speed of agent
	double range = 40;			// range of audibility
								//
	int Acounter;				// counters;
	int Bcounter;				//
								//
	int node_of_arrive;			// 0 or 1 (A or B)

	Agent();
	void Iteration(vector<Agent*>& list);
	void Noise(vector<Agent*> &list);
	void Ear(vector<Agent*>& list);
};

#endif

