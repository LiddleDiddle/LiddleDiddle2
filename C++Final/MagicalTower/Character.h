#pragma once

#include <Bengine\SpriteBatch.h>
#include <Bengine\ResourceManager.h>
#include "CharacterState.h"
#include <Box2D/Box2D.h>
#include "Entity.h"
class Character : public Entity{
public:
	virtual void init(int controllerNumber, float x, float y, b2World* world) {}
	virtual void update(float timeStep) {}
	virtual void draw(Bengine::SpriteBatch& spriteBatch) {}
	int getEntityType() { return entityType; }
	void kill() { _alive = false; }
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