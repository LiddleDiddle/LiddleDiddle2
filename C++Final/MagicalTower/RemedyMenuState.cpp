#include "RemedyMenuState.h"
#include "MainMenuGameState.h"
#include "MainGame.h"
#include "Level.h"
#include "Drawable.h"
#include <SDL/SDL.h>
#include <iostream>
#include <cmath>
#include "tinyxml2.h"
#include "GeneralManager.h"

using namespace tinyxml2;

#define CAMERA TheMainGame::Instance()->_camera
#define WIDTH 32
#define HEIGHT 18
const float HALF_TILE_WIDTH = 0.5;

RemedyMenuState::RemedyMenuState(const std::shared_ptr<GameStateManager> &gameStateManager) :
	gameStateManager(gameStateManager) 
{

}

void RemedyMenuState::Entered()
{
	BuildLevel(TheGeneralManager::Instance()->_levels[TheGeneralManager::Instance()->currentLevel].LoadLevel());
	for (int i = 0; i < GENERAL_MANAGER->_joinedPlayers.size(); i++)
	{
		_characters.push_back(new WrekTangle());
	}
	switch (GENERAL_MANAGER->_joinedPlayers.size())
	{
	case 1 :
		_characters[0]->init(0, 3, 14, world);
		break;
	case 2:
		_characters[0]->init(0, 6, 14, world);
		_characters[1]->init(1, 27, 14, world);
		break;
	case 3:
		_characters[0]->init(0, 6, 14, world);
		_characters[1]->init(1, 27, 14, world);
		_characters[2]->init(2, 6, 3, world);
		break;
	case 4:
		_characters[0]->init(0, 6, 14, world);
		_characters[1]->init(1, 27, 14, world);
		_characters[3]->init(2, 6, 3, world);
		_characters[4]->init(3, 27, 3, world);
		break;
	default:
		break;
	}
}

void RemedyMenuState::Exiting()
{

}

void RemedyMenuState::Update(float elapsedTime, Bengine::InputManager& inputManager)
{
	for (int i = 0; i < GENERAL_MANAGER->_joinedPlayers.size(); i++)
	{
		_characters[i]->update(elapsedTime);
	}
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	world->Step(elapsedTime, velocityIterations, positionIterations);
}

void RemedyMenuState::Draw(Bengine::SpriteBatch& spriteBatch)
{
	for (int i = 0; i < GENERAL_MANAGER->_joinedPlayers.size(); i++)
	{
		_characters[i]->draw(spriteBatch);
	}
	for (int i = 0; i < tiles.size(); ++i)
	{
		tiles[i]->Draw(spriteBatch);
	}
}

void RemedyMenuState::BuildLevel(int** level)
{
	world = new b2World(b2Vec2(0.0f, -20.0f));
	//create box if tile exists
	for (int i = 0; i < HEIGHT; ++i)
	{	
		for (int j = 0; j < WIDTH; ++j)
		{
			if (level[i][j] != 0)
			{
				tiles.emplace_back(new PhysicsTile(world, b2Vec2(j + HALF_TILE_WIDTH, i + HALF_TILE_WIDTH), level[i][j]));
			}
		}
	}
}