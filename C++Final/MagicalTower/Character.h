#pragma once

#include <Bengine\SpriteBatch.h>
#include <Bengine\ResourceManager.h>
#include "CharacterState.h"
#include "WeaponState.h"
#include <Box2D/Box2D.h>
#include "Entity.h"
class Character : public Entity{
public:
	virtual void init(int controllerNumber, float x, float y, b2World* world) {}
	virtual void update(float timeStep) {}
	virtual void draw(Bengine::SpriteBatch& spriteBatch) {}
	int getEntityType() { return EntityEnum::CHARACTER; }
	void kill() { _alive = false; }
	float _mana;

	int numFootContact = 0;
protected:
	CharacterState* _currentState;
	WeaponState* _mainWeaponState;
	bool _alive;
	b2Body* _body;
	b2World* _world;
	int _controllerNumber;
	float previousMana;
};