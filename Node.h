#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include "Agent.h"
using namespace std;
const int SizeScene = 800;
static int types = 3;
static const double radius = 25;
static double const pi = 3.14159265358979323846;

class Node
{
public:
	double x;
	double y;
	int type;
	double radius = 25;
	double speed = 0.25;
	double angle;
	Node()
	{
		x = rand() / double(RAND_MAX) * SizeScene;
		y = rand() / double(RAND_MAX) * SizeScene;
		type = rand() % types;
		angle = rand() / double(RAND_MAX) * 2 * pi;
	}
	Node(int a, double X, double Y) :Node() { type = a; x = X; y = Y; } // for init ant-base
	Node(int Type, double X, double Y, double R, double V, double Ang)
	{
		x = X;
		y = Y;
		type = Type;
		radius = R;
		speed = V;
		angle = Ang;
	}
	void Iteration(double Rand)
	{
		if (x + cos(angle) * speed <= 0 || y + sin(angle) * speed <= 0 || x + cos(angle) * speed >= SizeScene
			|| y + sin(angle) * speed >= SizeScene)
		{
			angle = angle + pi;
			x += cos(angle) * speed;
			y += sin(angle) * speed;
		}
		else
		{
			x += cos(angle) * speed;
			y += sin(angle) * speed;
			angle += Rand;
		}
	}
};