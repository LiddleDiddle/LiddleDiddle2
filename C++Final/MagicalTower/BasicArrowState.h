#pragma once
#include "CharacterState.h"
class BasicArrowState :
	public CharacterState
{
public:
	BasicArrowState();
	~BasicArrowState();
	CharacterState* update(float timeStep);
	void draw(Bengine::SpriteBatch& spriteBatch, int x, int y);
	void processInputs(int controllerNumber);
	void enter();
	void exit();
};

