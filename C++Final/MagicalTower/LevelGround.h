#pragma once

#include "GameObject.h"

class LevelGround : public GameObject
{
public:
	LevelGround(b2World* world, float x, float y);
	~LevelGround();

	void CreateBox2dObject(float x, float y);
	void Draw(Bengine::SpriteBatch& spriteBatch);
	void addForceCenter(float x, float y);
};