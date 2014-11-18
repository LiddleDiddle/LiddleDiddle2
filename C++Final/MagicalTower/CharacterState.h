#pragma once
#include <Bengine\SpriteBatch.h>
#include <Bengine\ResourceManager.h>
#include "GeneralManager.h"

#define GENERAL_MANAGER TheGeneralManager::Instance()

class CharacterState{
public:
	virtual void update(float timeStep) {};
	std::string getTexture() { return _texture; };
	virtual void processInputs(int controllerNumber) {};
	virtual void enter() {};
	virtual void quit() {};
protected:
	std::string _texture;
};