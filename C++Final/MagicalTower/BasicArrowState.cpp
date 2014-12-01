#include "BasicArrowState.h"
#include <iostream>
#include "LevelState.h"
#include "ManaOrb.h"
BasicArrowState::BasicArrowState()
{
}


BasicArrowState::~BasicArrowState()
{
}
WeaponState* BasicArrowState::update(float x, float y, int controllerNumber, float& mana){

	for (int i = 0; i < arrows.size(); i++)
	{
		if (arrows[i]->getContacting() > 0)
		{

			LevelState::items.push_back(new ManaOrb(arrows[i]->getPos().x,arrows[i]->getPos().y, _manaCost));
			delete arrows[i];
			arrows.erase(arrows.begin() + i);
			i = 0;
		}
	}

	for (int i = 0; i < arrows.size(); i++)
	{
		arrows[i]->update();
	}

	glm::vec2 rightStick(GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[controllerNumber]].getRightStick().x, GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[controllerNumber]].getRightStick().y);
	_magnitude = glm::length(rightStick);
	_rotation = atan2(rightStick.y, rightStick.x) - (3.14159265359 / 2);

	arrowSpeed = 1500;

	if (GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[controllerNumber]].isKeyPressed(SDL_CONTROLLER_BUTTON_LEFTSTICK) && _magnitude >= 0.2 && mana >= 25)
	{
		glm::vec2 temp = glm::normalize(rightStick);
		arrows.push_back(new Arrow(x + (temp.x * 1.5f),y + (temp.y * 1.7f), b2Vec2(temp.x * arrowSpeed, temp.y * arrowSpeed)));
		mana -= _manaCost;
	}

	

	return NULL;
}

void BasicArrowState::draw(Bengine::SpriteBatch& spriteBatch, float x, float y)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Bengine::ColorRGBA8 color(255, 255, 255, 255);
	if (_magnitude >= 0.2)
	{
		spriteBatch.draw(glm::vec4(x* CAMERA.getScreenDimensions().x / 32, y * CAMERA.getScreenDimensions().y / 18, CAMERA.getScreenDimensions().x / 32, CAMERA.getScreenDimensions().y / 18 * 4), _rotation, uv, _texture.id, 0.0f, color);
	}
	for (int i = 0; i < arrows.size(); i++)
	{
		arrows[i]->draw(spriteBatch);
	}

}
	


void BasicArrowState::processInputs(int controllerNumber){
	

}

void BasicArrowState::enter(){
	_manaCost = 25.0f;
	_texture = Bengine::ResourceManager::getTexture("Textures/Character/arrow.png");
	_rotation = 0;
	
}

void BasicArrowState::exit(){

}

