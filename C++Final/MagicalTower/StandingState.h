#pragma once
#include "CharacterState.h"
class StandingState :
	public CharacterState
{
public:
	StandingState();
	~StandingState();
	void update(float timeStep);
	void processInputs(int controllerNumber);
	void enter();
	void quit();
private:
};

