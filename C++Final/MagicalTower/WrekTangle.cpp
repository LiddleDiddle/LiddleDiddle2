#include "WrekTangle.h"
#include "StandingState.h"

WrekTangle::WrekTangle(){

}


WrekTangle::~WrekTangle(){

}

void WrekTangle::init(int x, int y, b2World* world) {
	_world = world;
	
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(x, y);
	bodyDef.fixedRotation = true;

	b2Vec2 v(0, 1.0f);

	_body = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.5f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	fixtureDef.friction = 0.6f;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.3f;

	_body->CreateFixture(&fixtureDef);

	_mana = 100;
	_alive = true;
	_currentState = new StandingState;
}

void WrekTangle::update(float timeStep){

	CharacterState* tempState = _currentState->update(timeStep);


	if (tempState != NULL)
	{
		_currentState->exit();
		delete _currentState;
		_currentState = tempState;
		_currentState->enter();
	}


	if (_alive)
	{
		glm::clamp(_mana, 0, 100);
	}
}

void WrekTangle::draw(Bengine::SpriteBatch spriteBatch){
	_currentState->draw(spriteBatch, _body->GetPosition().x, _body->GetPosition().y);
}