#pragma once
#include "CharacterState.h"
class HomuraGround :
	public CharacterState
{
public:
	HomuraGround();
	~HomuraGround();
	CharacterState* update(b2Body &body, int controllerNumber, int contacts);
	void draw(Bengine::SpriteBatch& spriteBatch, b2Body *body);
	void processInputs(int controllerNumber);
	void enter();
	void exit();
private:

};

