#pragma once

#include <Bengine\SpriteBatch.h>
#include <Bengine\ResourceManager.h>
#include "CharacterState.h"
#include <Box2D/Box2D.h>

class Character{
public:
	virtual void init(int controllerNumber, float x, float y, b2World* world) {}
	virtual void update(float timeStep) {}
	virtual void draw(Bengine::SpriteBatch& spriteBatch) {}
protected:
	CharacterState* _currentState;
	CharacterState* _mainWeaponState;
	CharacterState* _item;
	bool _alive;
	int _mana;
	b2Body* _body;
	b2World* _world;
	int _controllerNumber;
private:
};