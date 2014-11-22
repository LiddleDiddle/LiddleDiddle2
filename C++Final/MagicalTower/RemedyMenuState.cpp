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
}

void RemedyMenuState::Exiting()
{

}

void RemedyMenuState::Update(float elapsedTime, Bengine::InputManager& inputManager)
{
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	world->Step(elapsedTime, velocityIterations, positionIterations);
}

void RemedyMenuState::Draw(Bengine::SpriteBatch& spriteBatch)
{
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
				tiles.push_back(new PhysicsTile(world, b2Vec2(j + HALF_TILE_WIDTH, i + HALF_TILE_WIDTH), level[i][j]));
			}
		}
	}
}