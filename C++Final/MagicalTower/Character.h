#pragma once

#include <Bengine\SpriteBatch.h>
#include <Bengine\ResourceManager.h>
#include "CharacterState.h"

class Character{
public:
	virtual void init() {}
	virtual void update(float timeStep) {}
	virtual void draw(Bengine::SpriteBatch spriteBatch) {}
protected:
	CharacterState* _currentState;
	bool _isAlive;
	int _mana;
private:
};