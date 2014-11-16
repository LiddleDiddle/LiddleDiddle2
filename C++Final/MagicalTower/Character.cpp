#include "Character.h"


Character::Character()
{
}


Character::~Character()
{
}

void Character::handleInput(int controller)
{
	CharacterState* state = state->handleInput(*this, controller);
	if (state != NULL)
	{
		delete _state;
		_state = state;

		//call enter on the new state
		_state->enter(*this);
	}
}

void Character::update()
{

}

void Character::draw(Bengine::SpriteBatch& spriteBatch)
{
	//draw stuff here
}
