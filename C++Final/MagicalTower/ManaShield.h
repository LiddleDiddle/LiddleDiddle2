#pragma once
#include "WeaponState.h"
class ManaShield :
	public WeaponState
{
public:
	ManaShield();
	~ManaShield();
	WeaponState* update(float x, float y, int controllerNumber, float& mana);
	void draw(Bengine::SpriteBatch& spriteBatch, float x, float y);
	void processInputs(int controllerNumber);
	void enter();
	void exit();
	bool isActive() { return _active; }
private:
	float _timer;
	float _manaCost;
	bool _active;
	float _rotation;
};

