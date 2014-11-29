#pragma once
#include "CharacterState.h"
class MamiGround :
	public CharacterState
{
public:
	MamiGround();
	~MamiGround();
	CharacterState* update(b2Body &body, int controllerNumber, int contacts);
	void draw(Bengine::SpriteBatch& spriteBatch, b2Body *body);
	void processInputs(int controllerNumber);
	void enter();
	void exit();
private:

};

