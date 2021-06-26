#include <iostream>
#include <vector>
#include "Agent.h"
using namespace std;

int main()
{
	// swarm init
	vector<Agent*> swarm(20);
	for (size_t i = 0; i < swarm.size(); i++) 
		swarm[i] = new Agent();

	while (true) 
	{
		for (size_t i = 0; i < swarm.size(); i++) 
		{
			swarm[i]->Iteration();
			swarm[i]->Noise(swarm);
		}
	}
}

