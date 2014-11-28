#pragma once
#include <Bengine\SpriteBatch.h>
#include <Bengine\ResourceManager.h>
#include "GeneralManager.h"
#include "MainGame.h"
#include <Box2D/Box2D.h>

#define CAMERA TheMainGame::Instance()->_camera
#define GENERAL_MANAGER TheGeneralManager::Instance()

class WeaponState{
public:
	virtual WeaponState* update(float x, float y, int controllerNumber) { return NULL; };
	virtual void draw(Bengine::SpriteBatch& spriteBatch, float x, float y) {}
	virtual void processInputs(int controllerNumber) {};
	virtual void enter() {};
	virtual void exit() {};
protected:
	Bengine::GLTexture _texture;
};