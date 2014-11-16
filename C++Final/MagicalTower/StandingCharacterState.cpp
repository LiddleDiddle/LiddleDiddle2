#include "StandingCharacterState.h"


StandingCharacterState::StandingCharacterState()
{
}


StandingCharacterState::~StandingCharacterState()
{
}

CharacterState* StandingCharacterState::handleInput(Character& character, int controller)
{
	if (true)
	{
		return new CharacterState;//return jump state
	}
		
	return NULL;
}

void StandingCharacterState::update()
{

}

void StandingCharacterState::enter(Character& character)
{
	_texture = Bengine::ResourceManager::getTexture("Textures/StartMenu/bg.png"); //replace this with a more correct image
	character.setTexture(_texture);
}
