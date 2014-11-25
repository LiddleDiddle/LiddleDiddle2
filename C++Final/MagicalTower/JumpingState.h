#pragma once
#include "CharacterState.h"
class JumpingState :
	public CharacterState
{
public:
	JumpingState();
	~JumpingState();
	CharacterState* update(b2Body &body, int controllerNumber);
	void draw(Bengine::SpriteBatch& spriteBatch, b2Body *body);
	void processInputs(int controllerNumber);
	void enter();
	void exit();
private:
	bool jumpUsed;
};

