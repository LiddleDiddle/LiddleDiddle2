#include "JumpingState.h"
#include <iostream>
#include "StandingState.h"
JumpingState::JumpingState()
{
}


JumpingState::~JumpingState()
{
}

CharacterState* JumpingState::update(b2Body & body, int controllerNumber, int contacts){
	if (contacts == 0)
	{
		body.GetFixtureList()->SetFriction(0);
	}
	
	if (contacts > 0)
	{
		body.GetFixtureList()[0].SetFriction(1.0f);
		return new StandingState;
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
	_texture = Bengine::ResourceManager::getTexture("Textures/madokis/jumping.png");

	if (body.GetLinearVelocity().y > 0)
		uv = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	else
		uv = glm::vec4(currentFrame / frames, 0, 1.0 / frames, 1.0f);

	if (body.GetLinearVelocity().y <= 0)
	{
		_texture = Bengine::ResourceManager::getTexture("Textures/madokis/falling.png");
		frameTimer += 0.01666666;
		if (frameTimer >= frameRate)
		{
			currentFrame++;
			if (currentFrame > frames)
				currentFrame = 0;
				uv = glm::vec4(currentFrame / frames, 0, 1.0 / frames, 1.0f);
			frameTimer = 0;
		}
	}

	return NULL;
}

void JumpingState::draw(Bengine::SpriteBatch& spriteBatch, b2Body *body){
	
	Bengine::ColorRGBA8 color(255, 255, 255, 255);

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

	
	if (body->GetLinearVelocity().y > 0)
	spriteBatch.draw(glm::vec4(body->GetPosition().x* CAMERA.getScreenDimensions().x / 32, body->GetPosition().y * CAMERA.getScreenDimensions().y / 18, CAMERA.getScreenDimensions().x / 32, CAMERA.getScreenDimensions().y / 18 * 1.5), 0, uv, _texture.id, 0.0f, color);
	else
	spriteBatch.draw(glm::vec4(body->GetPosition().x* CAMERA.getScreenDimensions().x / 32, body->GetPosition().y * CAMERA.getScreenDimensions().y / 18, CAMERA.getScreenDimensions().x / 32 * 1.1, CAMERA.getScreenDimensions().y / 18 * 1.6), 0, uv, _texture.id, 0.0f, color);
}

void JumpingState::processInputs(int controllerNumber){

}

void JumpingState::enter(){
	_texture = Bengine::ResourceManager::getTexture("Textures/madokis/jumping.png");
	jumpUsed = false;
	frames = 3;
	frameRate = 0.15f;
	frameTimer = 0;
	currentFrame = 0;
	uv = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
}

void JumpingState::exit(){

}