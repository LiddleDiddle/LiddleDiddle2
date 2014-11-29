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

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(0.5f, 0.75f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygonShape;

	fixtureDef.friction = 1.0f;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.0f;

	_body->CreateFixture(&fixtureDef);

	//add foot sensor fixture
	polygonShape.SetAsBox(0.4, 0.3, b2Vec2(0, -.75), 0);
	fixtureDef.isSensor = true;
	b2Fixture* footSensorFixture = _body->CreateFixture(&fixtureDef);
	footSensorFixture->SetUserData(this);

	numFootContact = 0;
	_mana = 100;
	_alive = true;
	_currentState = new StandingState;
	_currentState->enter();
	_mainWeaponState = new BasicArrowState;
	_mainWeaponState->enter();
	_controllerNumber = controllerNumber;
	justDied = true;
	_body->SetUserData(this);
	color.a = 255;
	color.r = 255;
	color.b = 255;
	color.g = 255;
	_alpha = 255;
	previousMana = 100;
}

void WrekTangle::update(float timeStep){
	if (_alive)
	{
		if (_mana == previousMana)
		{
			_alpha -= 1;
			if (_alpha <= 0)
				_alpha = 0;
		}
		if (_mana != previousMana)
		{
			_alpha = 255;
		}
		previousMana = _mana;
		color.a = _alpha;

		
		CharacterState* tempState = _currentState->update(*_body, _controllerNumber, numFootContact);
		WeaponState* tempWeap =_mainWeaponState->update(_body->GetPosition().x, _body->GetPosition().y, _controllerNumber, _mana);

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
	if (_mana < 0)
		_mana = 0;
	else if (_mana > 100)
		_mana = 100;
	// horizontal teleport -------------------------------------------------------------
	if (_body->GetPosition().x > 32.5)
	{
		_body->SetTransform(b2Vec2(0.0f, _body->GetPosition().y), _body->GetAngle());
	}
	else if (_body->GetPosition().x < -0.05)
	{
		_body->SetTransform(b2Vec2(32.0f, _body->GetPosition().y), _body->GetAngle());
	}
	//----------------------------------------------------------------------------------

	// vertical teleport ---------------------------------------------------------------
	if (_body->GetPosition().y > 18.5)
	{
		_body->SetTransform(b2Vec2(_body->GetPosition().x, 0.0f), _body->GetAngle());
	}
	else if (_body->GetPosition().y < -0.05)
	{
		_body->SetTransform(b2Vec2(_body->GetPosition().x, 18.0f), _body->GetAngle());
	}
	//----------------------------------------------------------------------------------
}

void WrekTangle::draw(Bengine::SpriteBatch& spriteBatch){

	//draw the mana bar -----------------------------------------------------------------------------------------------------------------
	static Bengine::GLTexture manaBarBG = Bengine::ResourceManager::getTexture("Textures/Character/manaBarBG.png");
	static Bengine::GLTexture manaBarTick = Bengine::ResourceManager::getTexture("Textures/Character/manaBarTick.png");
	static Bengine::GLTexture manaBarFrame = Bengine::ResourceManager::getTexture("Textures/Character/manaBarFrame.png");
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	
	if (_alive)
	{
		spriteBatch.draw(glm::vec4(_body->GetPosition().x * TheMainGame::Instance()->_camera.getScreenDimensions().x / 32,
			_body->GetPosition().y * TheMainGame::Instance()->_camera.getScreenDimensions().y / 18 + TheMainGame::Instance()->_camera.getScreenDimensions().y / 18,
			TheMainGame::Instance()->_camera.getScreenDimensions().x / 16.7320261438, TheMainGame::Instance()->_camera.getScreenDimensions().y / 36), 0.0f, uv, manaBarBG.id, 0.0f, color);

		for (int i = 0; i < _mana; i++)
		{
			spriteBatch.draw(glm::vec4(_body->GetPosition().x * TheMainGame::Instance()->_camera.getScreenDimensions().x / 32 - TheMainGame::Instance()->_camera.getScreenDimensions().x / 34.1333333333 + (TheMainGame::Instance()->_camera.getScreenDimensions().x / 1706.66666667 * i),
				_body->GetPosition().y * TheMainGame::Instance()->_camera.getScreenDimensions().y / 18 + TheMainGame::Instance()->_camera.getScreenDimensions().y / 18,
				TheMainGame::Instance()->_camera.getScreenDimensions().x / 1706.66666667, TheMainGame::Instance()->_camera.getScreenDimensions().y / 36), 0.0f, uv, manaBarTick.id, 0.0f, color);
		}

		spriteBatch.draw(glm::vec4(_body->GetPosition().x * TheMainGame::Instance()->_camera.getScreenDimensions().x / 32,
			_body->GetPosition().y * TheMainGame::Instance()->_camera.getScreenDimensions().y / 18 + TheMainGame::Instance()->_camera.getScreenDimensions().y / 18,
			TheMainGame::Instance()->_camera.getScreenDimensions().x / 16.7320261438, TheMainGame::Instance()->_camera.getScreenDimensions().y / 36), 0.0f, uv, manaBarFrame.id, 0.0f, color);

		//---------------------------------------------------------------------------------------------------------------------
		_currentState->draw(spriteBatch, _body);
		_mainWeaponState->draw(spriteBatch,_body->GetPosition().x, _body->GetPosition().y);
	}

	
	
	
}