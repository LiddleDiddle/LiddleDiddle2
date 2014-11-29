#pragma once
#include "WeaponState.h"
#include "Arrow.h"

class BasicArrowState :
	public WeaponState
{
public:
	BasicArrowState();
	~BasicArrowState();
	WeaponState* update(float x, float y, int controllerNumber, float& mana);
	void draw(Bengine::SpriteBatch& spriteBatch, float x, float y);
	void processInputs(int controllerNumber);
	void enter();
	void exit();
private:
	float _manaCost;
	float _rotation;
	float _magnitude;
	float arrowSpeed;
	std::vector<Arrow*> arrows;
};

