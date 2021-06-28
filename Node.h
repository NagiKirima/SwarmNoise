#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include "Agent.h"
using namespace std;
const int SizeScene = 800;
static int types = 3;
static double x_a = 200;
static double y_a = 200;
static double x_b = 500;
static double y_b = 400;
static double x_c = 400;
static double y_c = 700;
static const double radius = 25;
static double const pi = 3.14159265358979323846;

class Node
{
public:
	double x;
	double y;
	int type;
	double radius = 25;
	double speed = 0.05;
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
};
//static vector<Node> listOfNodes = { Node(0, x_a, y_a), Node(1, x_b, y_b), Node(2, x_c, y_c) };
