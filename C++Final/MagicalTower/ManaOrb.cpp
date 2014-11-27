#include "ManaOrb.h"
#include "LevelState.h"

ManaOrb::ManaOrb(float x, float y, float mana) 
: _mana(mana)
{
	// Circle
	b2CircleShape shape;
	shape.m_radius = _mana / 100;

	b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = 1.0f;
	fd.restitution = 0.3f;
	fd.friction = 0.5f;
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	//bd.position.Set(-1.0f , 20.0f);
	bd.position.Set(x, y);
	body = LevelState::world->CreateBody(&bd);
	body->CreateFixture(&fd);
	body->SetUserData(this);
	entityType = EntityEnum::PROJECTILE;
}


ManaOrb::~ManaOrb()
{
	LevelState::world->DestroyBody(body);
}

void ManaOrb::update(float elapsedTime)
{

}

void ManaOrb::draw(Bengine::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static Bengine::GLTexture orb = Bengine::ResourceManager::getTexture("Textures/Items/orb.png");
	Bengine::ColorRGBA8 color(255,255,255,255);
	glm::vec4 rectangle = glm::vec4(body->GetPosition().x * TheMainGame::Instance()->_camera.getScreenDimensions().x / 32, body->GetPosition().y * TheMainGame::Instance()->_camera.getScreenDimensions().y / 18, TheMainGame::Instance()->_camera.getScreenDimensions().x / 32 * (_mana / 50), TheMainGame::Instance()->_camera.getScreenDimensions().y / 18 * (_mana / 50));
	spriteBatch.draw(rectangle, body->GetAngle(), uv, orb.id, 0.0f, color);
}
