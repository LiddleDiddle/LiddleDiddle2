#pragma once

#include <Bengine\SpriteBatch.h>
#include <Bengine\ResourceManager.h>
#include "CharacterState.h"
#include <Box2D/Box2D.h>

class Character{
public:
	virtual void init(int x, int y, b2World* world) {}
	virtual void update(float timeStep) {}
	virtual void draw(Bengine::SpriteBatch spriteBatch) {}
protected:
	CharacterState* _currentState;
	bool _alive;
	int _mana;
	b2Body* _body;
	b2World* _world;
private:
};