#pragma once

#include "GameObject.h"

class LevelWall : public GameObject
{
public:
	LevelWall();
	LevelWall(b2World* world, float x, float y, float w, float h);
	~LevelWall();

	void CreateBox2dObject(float x, float y, float w, float h);
	void Draw(Bengine::SpriteBatch& spriteBatch);
	void addForceCenter(float x, float y);
};