#include "Arrow.h"
#include "LevelState.h"
#include <iostream>

Arrow::~Arrow()
{
}

Arrow::Arrow(float x, float y, b2Vec2 linearVelocity)
{
	// Circle
	b2CircleShape shape;
	shape.m_radius = 0.5f;
	
	b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = 1.0f;
	fd.restitution = 0.7f;
	fd.friction = 0.3f;
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	//bd.position.Set(-1.0f , 20.0f);
	bd.position.Set(x, y);
	body = LevelState::world->CreateBody(&bd);
	body->CreateFixture(&fd);
	body->ApplyForceToCenter(linearVelocity,true);
}

void Arrow::draw(Bengine::SpriteBatch& spriteBatch)
{
	b2Vec2 position = body->GetPosition();
	float32 angle = -(atan2(body->GetLinearVelocity().x , body->GetLinearVelocity().y) - 3.14 / 2);

	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static Bengine::GLTexture spook = Bengine::ResourceManager::getTexture("Textures/arrow.png");
	Bengine::ColorRGBA8 color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	glm::vec4 rectangle = glm::vec4(position.x * TheMainGame::Instance()->_camera.getScreenDimensions().x / 32, position.y * TheMainGame::Instance()->_camera.getScreenDimensions().x / 32, TheMainGame::Instance()->_camera.getScreenDimensions().x / 32, TheMainGame::Instance()->_camera.getScreenDimensions().x / 32);
	spriteBatch.draw(rectangle, angle, uv, spook.id, 0.0f, color);
}

void Arrow::update()
{

}
