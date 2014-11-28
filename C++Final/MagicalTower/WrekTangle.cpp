#include "WrekTangle.h"
#include "StandingState.h"
#include "BasicArrowState.h"
#include "LevelState.h"
#include "ManaOrb.h"

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
	justDied = true;
	_body->SetUserData(this);
}

void WrekTangle::update(float timeStep){
	if (_alive)
	{
		CharacterState* tempState = _currentState->update(*_body, _controllerNumber);
		WeaponState* tempWeap =_mainWeaponState->update(_body->GetPosition().x, _body->GetPosition().y, _controllerNumber);

		if (tempState != NULL)
		{
			_currentState->exit();
			delete _currentState;
			_currentState = tempState;
			_currentState->enter();
		}

		if (tempWeap != NULL)
		{
			_mainWeaponState->exit();
			delete _mainWeaponState;
			_mainWeaponState = tempWeap;
			_mainWeaponState->enter();
		}
	}
	else
	{
		if (justDied)
		{
			LevelState::items.push_back(new ManaOrb(_body->GetPosition().x, _body->GetPosition().y, _mana));
			justDied = false;
			_body->SetTransform(b2Vec2(-1, -1), 0);
		}
		else
		{
			
		}
	}
	glm::clamp(_mana, 0, 100);
}

void WrekTangle::draw(Bengine::SpriteBatch& spriteBatch){
	if (_alive)
	{
		_currentState->draw(spriteBatch, _body);
		_mainWeaponState->draw(spriteBatch,_body->GetPosition().x, _body->GetPosition().y);
	}
}