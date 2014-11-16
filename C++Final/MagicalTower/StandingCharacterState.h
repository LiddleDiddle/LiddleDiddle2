#pragma once
#include "CharacterState.h"

class StandingCharacterState : public CharacterState
{
public:
	StandingCharacterState();
	~StandingCharacterState();

	CharacterState* handleInput(Character& character, int controller);
	void update();
	void enter(Character& character);
};


