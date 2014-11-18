#pragma once
#include "CharacterState.h"
class JumpingState :
	public CharacterState
{
public:
	JumpingState();
	~JumpingState();
	CharacterState* update(float timeStep);
	void draw(Bengine::SpriteBatch spriteBatch, int x, int y);
	void processInputs(int controllerNumber);
	void enter();
	void exit();
};

