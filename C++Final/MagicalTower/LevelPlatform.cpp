#include "LevelPlatform.h"
#include <Bengine\ResourceManager.h>
#include "MainGame.h"

#define CAMERA TheMainGame::Instance()->_camera.getScreenDimensions();

LevelPlatform::LevelPlatform(b2World* world, float x, float y)
	:GameObject(world)
{
	CreateBox2dObject(x, y);
}

LevelPlatform::~LevelPlatform(void)
{

}

void LevelPlatform::CreateBox2dObject(float x, float y)
{
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2PolygonShape staticBox;
	staticBox.SetAsBox(3.5f, 0.5f);

	bodyDef.type = b2_staticBody;
	fixtureDef.friction = 0.3f;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.0f;

	bodyDef.position.Set(x, y);

	body = world->CreateBody(&bodyDef);

	fixtureDef.shape = &staticBox;

	body->CreateFixture(&fixtureDef);
}

void LevelPlatform::Draw(Bengine::SpriteBatch& spriteBatch)
{

}

void LevelPlatform::addForceCenter(float x, float y)
{

}