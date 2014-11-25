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
	return NULL;
}

void JumpingState::draw(Bengine::SpriteBatch& spriteBatch, b2Body *body){
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Bengine::ColorRGBA8 color(255, 255, 255, 255);

	spriteBatch.draw(glm::vec4(body->GetPosition().x* CAMERA.getScreenDimensions().x / 32, body->GetPosition().y * CAMERA.getScreenDimensions().y / 18, CAMERA.getScreenDimensions().x / 32, CAMERA.getScreenDimensions().y / 18 * 2), 0, uv, _texture.id, 0.0f, color);
}

void JumpingState::processInputs(int controllerNumber){
	if (GENERAL_MANAGER->_players[controllerNumber].isKeyPressed(SDL_CONTROLLER_BUTTON_A))
	{
		std::cout << "holy fuck I'm jumping\n";
	}

	if (GENERAL_MANAGER->_players[controllerNumber].isKeyPressed(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER))
	{
		std::cout << "Wow, I'm dodging. I can feel the wind in my hair!\n";
	}

}

void JumpingState::enter(){
	_texture = Bengine::ResourceManager::getTexture("Textures/madokis/jumping.png");
}

void JumpingState::exit(){

}