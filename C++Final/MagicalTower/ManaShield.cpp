#include "ManaShield.h"
#include <iostream>
#include "LevelState.h"
#include "ManaOrb.h"
ManaShield::ManaShield()
{
}


ManaShield::~ManaShield()
{
}

void ManaShield::enter(){
	_manaCost = 60 * 0.016666666 / 2;
	_rotation = 0;
	_timer = 0;
	_texture = Bengine::ResourceManager::getTexture("Textures/Character/betterManaShield.png");
}

WeaponState* ManaShield::update(float x, float y, int controllerNumber, float& mana){

	_timer += 0.0166666666;

	_active = false;
	if (GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[controllerNumber]].isKeyDown(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) && mana >= _manaCost)
	{
		_active = true;
		mana -= _manaCost;
		_rotation += 100 * 0.01666666;
	}



	return NULL;
}

void ManaShield::draw(Bengine::SpriteBatch& spriteBatch, float x, float y)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Bengine::ColorRGBA8 color((sin(_timer * 10) + 1) / 2 * 200 + 50, (sin(_timer * 15) + 1) / 2 * 200 + 50, (sin(_timer * 20) + 1) / 2 * 200 + 50, 200);
	
	if (_active)
		spriteBatch.draw(glm::vec4(x * CAMERA.getScreenDimensions().x / 32, y * CAMERA.getScreenDimensions().y / 18, CAMERA.getScreenDimensions().x / 32 * 1.6, CAMERA.getScreenDimensions().y / 18 * 1.6), _rotation, uv, _texture.id, 0.0f, color);
	

}



void ManaShield::processInputs(int controllerNumber){


}



void ManaShield::exit(){

}

