#include "LevelWall.h"
#include <Bengine\ResourceManager.h>
#include "MainGame.h"

#define CAMERA TheMainGame::Instance()->_camera.getScreenDimensions();

LevelWall::LevelWall(b2World* world, float x, float y, float w, float h)
	:GameObject(world)
{
	CreateBox2dObject(x, y, w, h);
}

LevelWall::~LevelWall(void)
{

}

void LevelWall::CreateBox2dObject(float x, float y, float w, float h)
{
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2PolygonShape staticBox;
	staticBox.SetAsBox(w, h);

	bodyDef.type = b2_staticBody;
	fixtureDef.friction = 0.3f;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.0f;

	bodyDef.position.Set(x, y);

	body = world->CreateBody(&bodyDef);

	fixtureDef.shape = &staticBox;

	body->CreateFixture(&fixtureDef);
}

void LevelWall::Draw(Bengine::SpriteBatch& spriteBatch)
{

}

void LevelWall::addForceCenter(float x, float y)
{

}