#pragma once
#include "CharacterState.h"
class RunningState :
	public CharacterState
{
public:
	RunningState();
	~RunningState();
	CharacterState* update(float timeStep);
	void draw(Bengine::SpriteBatch spriteBatch, int x, int y);
	void processInputs(int controllerNumber);
	void enter();
	void exit();
};

