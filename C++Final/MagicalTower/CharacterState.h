#pragma once
#include <Bengine\SpriteBatch.h>
#include <Bengine\ResourceManager.h>
#include "GeneralManager.h"
#include "MainGame.h"

#define CAMERA TheMainGame::Instance()->_camera
#define GENERAL_MANAGER TheGeneralManager::Instance()

class CharacterState{
public:
	virtual CharacterState* update(float timeStep) { return NULL; };
	virtual void draw(Bengine::SpriteBatch& spriteBatch, int x, int y) {}
	virtual void processInputs(int controllerNumber) {};
	virtual void enter() {};
	virtual void exit() {};
protected:
	Bengine::GLTexture _texture;
};