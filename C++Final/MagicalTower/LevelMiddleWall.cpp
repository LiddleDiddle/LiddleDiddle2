#include "LevelMiddleWall.h"
#include <Bengine\ResourceManager.h>
#include "MainGame.h"

#define CAMERA TheMainGame::Instance()->_camera.getScreenDimensions();

LevelMiddleWall::LevelMiddleWall(b2World* world, float x, float y)
	:GameObject(world)
{
	CreateBox2dObject(x, y);
}

LevelMiddleWall::~LevelMiddleWall(void)
{

}

void LevelMiddleWall::CreateBox2dObject(float x, float y)
{
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2PolygonShape staticBox;
	staticBox.SetAsBox(0.5f, 3.0f);

	bodyDef.type = b2_staticBody;
	fixtureDef.friction = 0.3f;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.0f;

	bodyDef.position.Set(x, y);

	body = world->CreateBody(&bodyDef);

	fixtureDef.shape = &staticBox;

	body->CreateFixture(&fixtureDef);
}

void LevelMiddleWall::Draw(Bengine::SpriteBatch& spriteBatch)
{

}

void LevelMiddleWall::addForceCenter(float x, float y)
{

}