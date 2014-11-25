#include "LevelGround.h"
#include <Bengine\ResourceManager.h>
#include "MainGame.h"

#define CAMERA TheMainGame::Instance()->_camera.getScreenDimensions();

LevelGround::LevelGround(b2World* world, float x, float y)
	:GameObject(world)
{
	CreateBox2dObject(x, y);
}

LevelGround::~LevelGround(void)
{

}

void LevelGround::CreateBox2dObject(float x, float y)
{
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2PolygonShape staticBox;
	staticBox.SetAsBox(16.0f, 0.5f);

	bodyDef.type = b2_staticBody;
	fixtureDef.friction = 0.5f;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.0f;

	bodyDef.position.Set(x, y);

	body = world->CreateBody(&bodyDef);

	fixtureDef.shape = &staticBox;

	body->CreateFixture(&fixtureDef);
}

void LevelGround::Draw(Bengine::SpriteBatch& spriteBatch)
{

}

void LevelGround::addForceCenter(float x, float y)
{

}