#include "SayakaAir.h"
#include <iostream>
#include "SayakaGround.h"
SayakaAir::SayakaAir()
{
}


SayakaAir::~SayakaAir()
{
}

CharacterState* SayakaAir::update(b2Body & body, int controllerNumber, int contacts){
	if (contacts == 0)
	{
		body.GetFixtureList()->SetFriction(0);
	}

	if (contacts > 0)
	{
		body.GetFixtureList()[0].SetFriction(1.0f);
		return new SayakaGround;
	}

	if (GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[controllerNumber]].getLeftStick().x > 0.1f || GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[controllerNumber]].getLeftStick().x < -0.1f)
	{
		body.ApplyForceToCenter(b2Vec2(GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[controllerNumber]].getLeftStick().x * 50, 0), true);
	}

	if (body.GetLinearVelocity().x > 10)
	{
		body.SetLinearVelocity(b2Vec2(10, body.GetLinearVelocity().y));
	}
	else if (body.GetLinearVelocity().x < -10)
	{
		body.SetLinearVelocity(b2Vec2(-10, body.GetLinearVelocity().y));
	}
	if (GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[controllerNumber]].isKeyPressed(SDL_CONTROLLER_BUTTON_LEFTSHOULDER) && jumpUsed == false)
	{
		std::cout << "A pressed" << std::endl;
		body.SetLinearVelocity(b2Vec2(body.GetLinearVelocity().x, 0.0f));
		body.ApplyForceToCenter(b2Vec2(0, 1500), true);
		jumpUsed = true;
	}

	return NULL;
}

void SayakaAir::draw(Bengine::SpriteBatch& spriteBatch, b2Body *body){

	Bengine::ColorRGBA8 color(255, 255, 255, 255);
	if (body->GetLinearVelocity().y > 0)
		_texture = Bengine::ResourceManager::getTexture("Textures/Sayaka/jump.png");
	uv = glm::vec4(0, 0, 1, 1);

	if (body->GetLinearVelocity().y <= 0)
	{
		_texture = Bengine::ResourceManager::getTexture("Textures/Sayaka/fall.png");
		uv = glm::vec4(0, 0, 1, 1);
	}

	if (body->GetLinearVelocity().x > 0)
	{
		if (uv[2] < 0)
			uv[2] *= -1;
	}
	if (body->GetLinearVelocity().x < 0)
	{
		if (uv[2] > 0)
			uv[2] *= -1;
	}


	spriteBatch.draw(glm::vec4(body->GetPosition().x* CAMERA.getScreenDimensions().x / 32, body->GetPosition().y * CAMERA.getScreenDimensions().y / 18, CAMERA.getScreenDimensions().x / 32, CAMERA.getScreenDimensions().y / 18 * 1.5), 0, uv, _texture.id, 0.0f, color);
	
}

void SayakaAir::processInputs(int controllerNumber){

}

void SayakaAir::enter(){
	_texture = Bengine::ResourceManager::getTexture("Textures/madokis/jumping.png");
	jumpUsed = false;
	frames = 3;
	frameRate = 0.15f;
	frameTimer = 0;
	currentFrame = 0;
	uv = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
}

void SayakaAir::exit(){

}