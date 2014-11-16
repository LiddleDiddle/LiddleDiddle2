#pragma once
#include "Character.h"
#include "GeneralManager.h"
#include <Bengine/ResourceManager.h>

#define GENERAL_MANAGER TheGeneralManager::Instance()->

class CharacterState 
{
public:
	virtual ~CharacterState() {}
	virtual CharacterState* handleInput(Character& character, int controller) = 0;
	virtual void update(Character& character) {}
	virtual void enter(Character& character) {}
protected:
	Bengine::GLTexture _texture;
};