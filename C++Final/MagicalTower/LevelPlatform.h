#pragma once

#include "GameObject.h"

class LevelPlatform : public GameObject
{
public:
	LevelPlatform(b2World* world, float x, float y);
	~LevelPlatform();

	void CreateBox2dObject(float x, float y);
	void Draw(Bengine::SpriteBatch& spriteBatch);
	void addForceCenter(float x, float y);
};