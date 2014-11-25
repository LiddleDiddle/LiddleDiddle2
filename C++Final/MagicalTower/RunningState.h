#pragma once
#include "CharacterState.h"
class RunningState :
	public CharacterState
{
public:
	RunningState();
	~RunningState();
	CharacterState* update(b2Body & body, int controllerNumber);
	void draw(Bengine::SpriteBatch& spriteBatch, b2Body *body);
	void processInputs(int controllerNumber);
	void enter();
	void exit();
};

