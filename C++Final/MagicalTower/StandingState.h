#pragma once
#include "CharacterState.h"
class StandingState :
	public CharacterState
{
public:
	StandingState();
	~StandingState();
	CharacterState* update(float timeStep);
	void draw(Bengine::SpriteBatch& spriteBatch, int x, int y);
	void processInputs(int controllerNumber);
	void enter();
	void exit();
private:
};

