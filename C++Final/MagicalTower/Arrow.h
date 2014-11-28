#pragma once

#include <Box2D/Box2D.h>
#include <Bengine\SpriteBatch.h>
#include <Bengine\ResourceManager.h>
#include "GeneralManager.h"
#include "MainGame.h"
#include "Entity.h"

class Arrow : public Entity
{
public:
	Arrow(float x, float y, b2Vec2 linearVelocity);
	~Arrow();
	void update();
	void draw(Bengine::SpriteBatch& spriteBatch);
	void startContact() { _contacting++; }
	void endContact() { _contacting--; }
	bool getContacting() { return _contacting; }
	int getEntityType() { return EntityEnum::PROJECTILE; }
	b2Vec2 getPos() { return body->GetPosition(); }
	b2Body* body;

	
private:
	int _contacting;
	b2Vec2 position;
	float32 angle;

};

