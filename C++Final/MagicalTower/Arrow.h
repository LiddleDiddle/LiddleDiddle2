#pragma once

#include <Box2D/Box2D.h>
#include <Bengine\SpriteBatch.h>
#include <Bengine\ResourceManager.h>
#include "GeneralManager.h"
#include "MainGame.h"

class Arrow
{
public:
	Arrow(float x, float y, b2Vec2 linearVelocity);
	~Arrow();
	void update();
	void draw(Bengine::SpriteBatch& spriteBatch);
	b2Body* body;
};

