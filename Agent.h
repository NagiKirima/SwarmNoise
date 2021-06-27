#pragma once
#ifndef AGENT_H
#define AGENT_H
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
const int SizeScene = 800;
static double x_a = 100;
static double y_a = 500;
static double x_b = 500;
static double y_b = 100;
static const double radius = 25;
static double const pi = 3.14159265358979323846;
class Agent
{
public:
	double x;					// coords
	double y;					//
								//
	double angle;				// angle of speed vector
	double speed;				// speed of agent
	double range = 35;			// range of audibility
								//
	int Acounter;				// counters;
	int Bcounter;				//
								//
	int node_of_arrive;			// 0 or 1 (A or B)

	Agent();
	virtual void Iteration(vector<Agent*>& list, double rand);
	void Noise(vector<Agent*> &list);
	void Ear(vector<Agent*>& list);
};
#endif

