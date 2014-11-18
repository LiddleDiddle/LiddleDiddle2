#include "StandingState.h"
#include <iostream>

StandingState::StandingState()
{
}


StandingState::~StandingState()
{
}

void StandingState::update(float timeStep){

}

void StandingState::processInputs(int controllerNumber){
	if(GENERAL_MANAGER->_players[controllerNumber].isKeyPressed(SDL_CONTROLLER_BUTTON_A))
	{
		std::cout << "holy fuck I'm jumping\n";
	}

	if (GENERAL_MANAGER->_players[controllerNumber].isKeyPressed(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER))
	{
		std::cout << "Wow, I'm dodging. I can feel the wind in my hair!\n";
	}

}

void StandingState::enter(){

}

void StandingState::quit(){
	
}