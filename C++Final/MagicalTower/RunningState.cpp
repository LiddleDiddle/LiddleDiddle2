#include "RunningState.h"
#include <iostream>

RunningState::RunningState()
{
}


RunningState::~RunningState()
{
}

CharacterState* RunningState::update(float timeStep){
	return NULL;
}

void RunningState::draw(Bengine::SpriteBatch spriteBatch, int x, int y) {
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Bengine::ColorRGBA8 color(255, 255, 255, 255);

	spriteBatch.draw(glm::vec4(x, y, CAMERA.getScreenDimensions().x / 32, CAMERA.getScreenDimensions().y / 18 * 2), 0, uv, _texture.id, 0.0f, color);
}

void RunningState::processInputs(int controllerNumber){
	if (GENERAL_MANAGER->_players[controllerNumber].isKeyPressed(SDL_CONTROLLER_BUTTON_A))
	{
		std::cout << "holy fuck I'm jumping\n";
	}

	if (GENERAL_MANAGER->_players[controllerNumber].isKeyPressed(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER))
	{
		std::cout << "Wow, I'm dodging. I can feel the wind in my hair!\n";
	}

}

void RunningState::enter(){
	_texture = Bengine::ResourceManager::getTexture("Textures/madokis/running.png");
}

void RunningState::exit(){

}