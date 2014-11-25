#include "LevelState.h"
#include <iostream>
#include <SDL/SDL.h>
#include <Bengine/ResourceManager.h>
#include "MainGame.h"
#include "Level.h"
#include "LevelGround.h"
#include "LevelMiddleWall.h"
#include "LevelPlatform.h"
#include "LevelWall.h"


#define WIDTH 32
#define HEIGHT 18
#define CAMERA TheMainGame::Instance()->_camera

LevelState::LevelState(const std::shared_ptr<GameStateManager> &gameStateManager) :
gameStateManager(gameStateManager)
{
	Level* level = new Level("Hardcoded Level", "Level001.png", "Level001.xml");
	levelArray = level->LoadLevel();
}

void LevelState::Entered() {
	CreateBox2dWorld();
	for (int i = 0; i < GENERAL_MANAGER->_joinedPlayers.size(); i++)
	{
		_characters.push_back(new WrekTangle());
	}
	switch (GENERAL_MANAGER->_joinedPlayers.size())
	{
	case 1:
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

void LevelState::Exiting() {
	std::cout << "_______________ is exiting" << std::endl;  //change this
}

void LevelState::Update(float elapsedTime, Bengine::InputManager& _inputManager) {
	//ProcessInput(_inputManager);

	for (int i = 0; i < GENERAL_MANAGER->_joinedPlayers.size(); i++)
	{
		_characters[i]->update(elapsedTime);
	}

	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	world->Step(elapsedTime, velocityIterations, positionIterations);


}

void LevelState::Draw(Bengine::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Bengine::ColorRGBA8 color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	static Bengine::GLTexture tile1 = Bengine::ResourceManager::getTexture("Textures/Assignment 4/Box.png");
	static Bengine::GLTexture tile2 = Bengine::ResourceManager::getTexture("Textures/Tile2.png");
	static Bengine::GLTexture tile3 = Bengine::ResourceManager::getTexture("Textures/Tile3.png");

	for (int i = 0; i < GENERAL_MANAGER->_joinedPlayers.size(); i++)
	{
		_characters[i]->draw(spriteBatch);
	}

	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			if (levelArray[i][j] == 1)
			{
				spriteBatch.draw(glm::vec4(CAMERA.getScreenDimensions().x / WIDTH / 2 + j*CAMERA.getScreenDimensions().x / WIDTH, CAMERA.getScreenDimensions().y / HEIGHT / 2 + i*CAMERA.getScreenDimensions().y / HEIGHT, CAMERA.getScreenDimensions().x / WIDTH, CAMERA.getScreenDimensions().y / HEIGHT), 0.0f, uv, tile1.id, 0.0f, color);
			}
			else if (levelArray[i][j] == 2)
			{
				spriteBatch.draw(glm::vec4(CAMERA.getScreenDimensions().x / WIDTH / 2 + j*CAMERA.getScreenDimensions().x / WIDTH, CAMERA.getScreenDimensions().y / HEIGHT / 2 + i*CAMERA.getScreenDimensions().y / HEIGHT, CAMERA.getScreenDimensions().x / WIDTH, CAMERA.getScreenDimensions().y / HEIGHT), 0.0f, uv, tile2.id, 0.0f, color);
			}
			else if (levelArray[i][j] == 3)
			{
				spriteBatch.draw(glm::vec4(CAMERA.getScreenDimensions().x / WIDTH / 2 + j*CAMERA.getScreenDimensions().x / WIDTH, CAMERA.getScreenDimensions().y / HEIGHT / 2 + i*CAMERA.getScreenDimensions().y / HEIGHT, CAMERA.getScreenDimensions().x / WIDTH, CAMERA.getScreenDimensions().y / HEIGHT), 0.0f, uv, tile3.id, 0.0f, color);
			}
		}
	}

}

void LevelState::ProcessInput(Bengine::InputManager inputManager){

}

void LevelState::CreateBox2dWorld()
{
	b2Vec2 gravity(0.0f, -30.0f);

	world = new b2World(gravity);

	objects.push_back(new LevelGround(world, 15.5, 0.5));
	objects.push_back(new LevelGround(world, 15.5, 17.5));

	objects.push_back(new LevelWall(world, 0.5, 8.5));
	objects.push_back(new LevelWall(world, 31.5, 8.5));

	objects.push_back(new LevelPlatform(world, 8.5, 9.5));
	objects.push_back(new LevelPlatform(world, 24.5, 9.5));
	objects.push_back(new LevelPlatform(world, 16.5, 4.5));

	objects.push_back(new LevelMiddleWall(world, 16.5, 14.));

	b2BodyDef bodyDef;
	m_groundBody = world->CreateBody(&bodyDef);
}