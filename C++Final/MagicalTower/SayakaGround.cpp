#include "SayakaGround.h"
#include <iostream>
#include "SayakaAir.h"
SayakaGround::SayakaGround()
{
}


SayakaGround::~SayakaGround()
{
}

CharacterState* SayakaGround::update(b2Body &body, int controllerNumber, int contacts){
	if (GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[controllerNumber]].isKeyPressed(SDL_CONTROLLER_BUTTON_LEFTSHOULDER))
	{
		body.ApplyForceToCenter(b2Vec2(0, 1500), true);
	}

	if (contacts == 0)
	{
		return new SayakaAir;
	}

	if (GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[controllerNumber]].getLeftStick().x > 0.1f || GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[controllerNumber]].getLeftStick().x < -0.1f)
	{
		body.ApplyForceToCenter(b2Vec2(GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[controllerNumber]].getLeftStick().x * 500, 0), true);
	}

	if (body.GetLinearVelocity().x > 3)
	{
		body.SetLinearVelocity(b2Vec2(3, body.GetLinearVelocity().y));
	}
	else if (body.GetLinearVelocity().x < -3)
	{
		body.SetLinearVelocity(b2Vec2(-3, body.GetLinearVelocity().y));
	}

	if (body.GetLinearVelocity().x <= 0.3 && body.GetLinearVelocity().x >= -0.3)
	{
		_texture = Bengine::ResourceManager::getTexture("Textures/Sayaka/idle.png");
		frameTimer += 0.01666666;
		if (frameTimer >= 0.15)
		{
			currentFrame++;
			if (currentFrame > 5)
				currentFrame = 0;
			frameTimer = 0;
		}
	}
	else
	{
		_texture = Bengine::ResourceManager::getTexture("Textures/Sayaka/run.png");
		frameTimer += 0.01666666;
		if (frameTimer >= 0.1)
		{
			currentFrame++;
			if (currentFrame > 8)
				currentFrame = 0;
			frameTimer = 0;
		}
	}

	return NULL;
}

void SayakaGround::draw(Bengine::SpriteBatch& spriteBatch, b2Body *body)
{
	if (body->GetLinearVelocity().x <= 0.3 && body->GetLinearVelocity().x >= -0.3)
	{
		_texture = Bengine::ResourceManager::getTexture("Textures/Sayaka/idle.png");
		uv = glm::vec4(currentFrame / 5, 0, 1.0 / 5, 1.0f);
	}
	else
	{
		_texture = Bengine::ResourceManager::getTexture("Textures/Sayaka/run.png");
		if (body->GetLinearVelocity().x >= 0.3)
			uv = glm::vec4(currentFrame / 8, 0, 1.0 / 8, 1.0f);
		if (body->GetLinearVelocity().x <= -0.3)
			uv = glm::vec4(currentFrame / 8, 0, -1.0 / 8, 1.0f);
	}
	Bengine::ColorRGBA8 color(255, 255, 255, 255);

	spriteBatch.draw(glm::vec4(body->GetPosition().x* CAMERA.getScreenDimensions().x / 32, body->GetPosition().y * CAMERA.getScreenDimensions().y / 18, CAMERA.getScreenDimensions().x / 32, CAMERA.getScreenDimensions().y / 18 * 1.5), 0, uv, _texture.id, 0.0f, color);
}


void SayakaGround::processInputs(int controllerNumber){


	if (GENERAL_MANAGER->_players[controllerNumber].isKeyPressed(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER))
	{
		std::cout << "Wow, I'm dodging. I can feel the wind in my hair!\n";
	}

}

void SayakaGround::enter(){
	_texture = Bengine::ResourceManager::getTexture("Textures/madokis/idle.png");
	frames = 8;
	frameRate = 0.15f;
	frameTimer = 0;
	currentFrame = 0;
	uv = glm::vec4(0.0f, 0.0f, 1.0f / frames, 1.0f);
}

void SayakaGround::exit(){

}

