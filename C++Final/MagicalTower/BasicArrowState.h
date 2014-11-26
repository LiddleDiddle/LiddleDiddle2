#pragma once
#include "CharacterState.h"
#include "Arrow.h"

class BasicArrowState :
	public CharacterState
{
public:
	BasicArrowState();
	~BasicArrowState();
	CharacterState* update(b2Body &body, int controllerNumber);
	void draw(Bengine::SpriteBatch& spriteBatch, b2Body *body);
	void processInputs(int controllerNumber);
	void enter();
	void exit();
private:
	float _rotation;
	float _magnitude;
	float arrowSpeed;
	std::vector<Arrow> arrows;
};

