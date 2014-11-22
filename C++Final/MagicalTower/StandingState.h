#pragma once
#include "CharacterState.h"
class StandingState :
	public CharacterState
{
public:
	StandingState();
	~StandingState();
	CharacterState* update(float timeStep);
	void draw(Bengine::SpriteBatch& spriteBatch, b2Body *body);
	void processInputs(int controllerNumber);
	void enter();
	void exit();
private:
};

