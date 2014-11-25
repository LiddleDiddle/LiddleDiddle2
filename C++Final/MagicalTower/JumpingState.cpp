#include "JumpingState.h"
#include <iostream>
#include "StandingState.h"
JumpingState::JumpingState()
{
}


JumpingState::~JumpingState()
{
}

CharacterState* JumpingState::update(b2Body & body, int controllerNumber){
	if (body.GetLinearVelocity().y == 0)
	{
		return new StandingState;
	}

	if (GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[controllerNumber]].getLeftStick().x > 0.05f || GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[controllerNumber]].getLeftStick().x < -0.05f)
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
	if (GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[controllerNumber]].isKeyPressed(SDL_CONTROLLER_BUTTON_A) && jumpUsed == false)
	{
		std::cout << "A pressed" << std::endl;
		body.SetLinearVelocity(b2Vec2(body.GetLinearVelocity().x, 0.0f));
		body.ApplyForceToCenter(b2Vec2(0, 2000), true);
		jumpUsed = true;
	}
	return NULL;
}

void JumpingState::draw(Bengine::SpriteBatch& spriteBatch, b2Body *body){
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Bengine::ColorRGBA8 color(255, 255, 255, 255);

	spriteBatch.draw(glm::vec4(body->GetPosition().x* CAMERA.getScreenDimensions().x / 32, body->GetPosition().y * CAMERA.getScreenDimensions().y / 18, CAMERA.getScreenDimensions().x / 32, CAMERA.getScreenDimensions().y / 18 * 2), 0, uv, _texture.id, 0.0f, color);
}

void JumpingState::processInputs(int controllerNumber){

}

void JumpingState::enter(){
	_texture = Bengine::ResourceManager::getTexture("Textures/madokis/jumping.png");
	jumpUsed = false;
}

void JumpingState::exit(){

}