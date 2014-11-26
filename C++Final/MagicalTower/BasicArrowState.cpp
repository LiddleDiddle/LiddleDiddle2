#include "BasicArrowState.h"
#include <iostream>
#include "LevelState.h"
BasicArrowState::BasicArrowState()
{
}


BasicArrowState::~BasicArrowState()
{
}
CharacterState* BasicArrowState::update(b2Body &body, int controllerNumber){

	glm::vec2 rightStick(GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[controllerNumber]].getRightStick().x, GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[controllerNumber]].getRightStick().y);
	_magnitude = glm::length(rightStick);
	_rotation = atan2(rightStick.y, rightStick.x) - (3.14159265359 / 2);

	arrowSpeed = 1500;

	if (GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[controllerNumber]].isKeyPressed(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) && _magnitude >= 0.2)
	{
		glm::vec2 temp = glm::normalize(rightStick);
		arrows.emplace_back(body.GetPosition().x + (temp.x * 1.0f), body.GetPosition().y + (temp.y * 1.5f), b2Vec2(temp.x * arrowSpeed, temp.y * arrowSpeed));
		
	}
	return NULL;
}

void BasicArrowState::draw(Bengine::SpriteBatch& spriteBatch, b2Body *body)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Bengine::ColorRGBA8 color(255, 255, 255, 255);
	if (_magnitude >= 0.2)
	{
		spriteBatch.draw(glm::vec4(body->GetPosition().x* CAMERA.getScreenDimensions().x / 32, body->GetPosition().y * CAMERA.getScreenDimensions().y / 18, CAMERA.getScreenDimensions().x / 32, CAMERA.getScreenDimensions().y / 18 * 4), _rotation, uv, _texture.id, 0.0f, color);
	}
	for (int i = 0; i < arrows.size(); i++)
	{
		arrows[i].draw(spriteBatch);
	}
}
	


void BasicArrowState::processInputs(int controllerNumber){
	

}

void BasicArrowState::enter(){
	_texture = Bengine::ResourceManager::getTexture("Textures/Character/arrow.png");
	_rotation = 0;
}

void BasicArrowState::exit(){

}

