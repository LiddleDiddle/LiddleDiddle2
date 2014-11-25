#include "StandingState.h"
#include <iostream>
#include "JumpingState.h"
StandingState::StandingState()
{
}


StandingState::~StandingState()
{
}

CharacterState* StandingState::update(b2Body &body , int controllerNumber){
	if (GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[controllerNumber]].isKeyPressed(SDL_CONTROLLER_BUTTON_A))
	{
		std::cout << "A pressed" << std::endl;
		body.ApplyForceToCenter(b2Vec2(0, 2000), true);
	}

	if (body.GetLinearVelocity().y > 0.1 || body.GetLinearVelocity().y < -0.1)
	{
		return new JumpingState;
	}

	if (GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[controllerNumber]].getLeftStick().x > 0.05f || GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[controllerNumber]].getLeftStick().x < -0.05f)
	{
		body.ApplyForceToCenter(b2Vec2(GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[controllerNumber]].getLeftStick().x* 1000,0), true);
	}

	if (body.GetLinearVelocity().x > 3)
	{
		body.SetLinearVelocity(b2Vec2(3, body.GetLinearVelocity().y));
	}
	else if (body.GetLinearVelocity().x < -3)
	{
		body.SetLinearVelocity(b2Vec2(-3, body.GetLinearVelocity().y));
	}

	return NULL;
}

void StandingState::draw(Bengine::SpriteBatch& spriteBatch, b2Body *body)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Bengine::ColorRGBA8 color(255, 255, 255, 255);
	
	spriteBatch.draw(glm::vec4(body->GetPosition().x* CAMERA.getScreenDimensions().x / 32, body->GetPosition().y * CAMERA.getScreenDimensions().y / 18, CAMERA.getScreenDimensions().x / 32, CAMERA.getScreenDimensions().y / 18 * 2), 0, uv, _texture.id, 0.0f, color);
}


void StandingState::processInputs(int controllerNumber){
	

	if (GENERAL_MANAGER->_players[controllerNumber].isKeyPressed(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER))
	{
		std::cout << "Wow, I'm dodging. I can feel the wind in my hair!\n";
	}

}

void StandingState::enter(){
	_texture = Bengine::ResourceManager::getTexture("Textures/madokis/standing.png");
}

void StandingState::exit(){
	
}

