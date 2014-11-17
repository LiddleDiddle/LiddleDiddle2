#pragma once

#include "GameObject.h"

class LevelMiddleWall : public GameObject
{
public:
	LevelMiddleWall(b2World* world, float x, float y);
	~LevelMiddleWall();

	void CreateBox2dObject(float x, float y);
	void Draw(Bengine::SpriteBatch& spriteBatch);
	void addForceCenter(float x, float y);
};