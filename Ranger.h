#pragma once
#include "Agent.h"
class Ranger : public Agent
{
public:
	Ranger() : Agent() 
	{
		if (node_of_arrive == 0) 
		{
			
		}
		else 
		{
		
		}
	}
	void Ear() = delete;
	void Iteration(vector<Agent*>& list, double rand) override;

};

