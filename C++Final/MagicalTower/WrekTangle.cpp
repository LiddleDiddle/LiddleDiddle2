#include "WrekTangle.h"
#include "StandingState.h"
#include "BasicArrowState.h"

WrekTangle::WrekTangle(){

}


WrekTangle::~WrekTangle(){
	delete _currentState;
	delete _mainWeaponState;
}

void WrekTangle::init(int controllerNumber, float x, float y, b2World* world) {
	_world = world;
	
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(x, y);
	printf("x is equal to %f\n", x);
	bodyDef.fixedRotation = true;
	b2Vec2 v(0, 1.0f);

	_body = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.5f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	fixtureDef.friction = 1.0f;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.0f;

	_body->CreateFixture(&fixtureDef);

	_mana = 100;
	_alive = true;
	_currentState = new StandingState;
	_currentState->enter();
	_mainWeaponState = new BasicArrowState;
	_mainWeaponState->enter();
	_controllerNumber = controllerNumber;
	entityType = EntityEnum::CHARACTER;
}

void WrekTangle::update(float timeStep){

	CharacterState* tempState = _currentState->update(*_body, _controllerNumber);
	_mainWeaponState->update(*_body, _controllerNumber);

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

void WrekTangle::draw(Bengine::SpriteBatch& spriteBatch){
	_currentState->draw(spriteBatch, _body);
	_mainWeaponState->draw(spriteBatch,_body);
}