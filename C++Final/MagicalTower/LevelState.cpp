#include "LevelState.h"
#include <iostream>
#include <SDL/SDL.h>
#include <Bengine/ResourceManager.h>
#include "MainGame.h"
#include "Level.h"
#include "LevelWall.h"
#include "Ball.h"


#define WIDTH 32
#define HEIGHT 18
#define CAMERA TheMainGame::Instance()->_camera

b2World* LevelState::world;
std::vector<Item*> LevelState::items;

LevelState::LevelState(const std::shared_ptr<GameStateManager> &gameStateManager) :
gameStateManager(gameStateManager)
{
	
	Level* level = new Level("Hardcoded Level", "LevelFinal.png", "LevelFinal.xml");
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
	for (int i = 0; i < items.size(); i++)
	{
		delete items[i];
	}
	items.clear();
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

	for (int i = 0; i < items.size(); i++)
	{
		items[i]->update(elapsedTime);
	}
}

void LevelState::Draw(Bengine::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Bengine::ColorRGBA8 color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	static Bengine::GLTexture tile1 = Bengine::ResourceManager::getTexture("Textures/Tiles/tile001.png");
	static Bengine::GLTexture tile2 = Bengine::ResourceManager::getTexture("Textures/Tiles/tile002.png");
	static Bengine::GLTexture tile3 = Bengine::ResourceManager::getTexture("Textures/Tiles/tile003.png");
	static Bengine::GLTexture tile4 = Bengine::ResourceManager::getTexture("Textures/Tiles/tile004.png");
	static Bengine::GLTexture tile5 = Bengine::ResourceManager::getTexture("Textures/Tiles/tile005.png");
	static Bengine::GLTexture tile6 = Bengine::ResourceManager::getTexture("Textures/Tiles/tile006.png");
	static Bengine::GLTexture tile7 = Bengine::ResourceManager::getTexture("Textures/Tiles/tile007.png");
	static Bengine::GLTexture tile8 = Bengine::ResourceManager::getTexture("Textures/Tiles/tile008.png");
	static Bengine::GLTexture tile9 = Bengine::ResourceManager::getTexture("Textures/Tiles/tile009.png");
	static Bengine::GLTexture tile10 = Bengine::ResourceManager::getTexture("Textures/Tiles/tile010.png");
	static Bengine::GLTexture tile11 = Bengine::ResourceManager::getTexture("Textures/Tiles/tile011.png");
	static Bengine::GLTexture tile12 = Bengine::ResourceManager::getTexture("Textures/Tiles/tile012.png");

	
	for (int i = 0; i < GENERAL_MANAGER->_joinedPlayers.size(); i++)
	{
		_characters[i]->draw(spriteBatch);
	}

	for (int i = 0; i < items.size(); i++)
	{
		items[i]->draw(spriteBatch);
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
			else if (levelArray[i][j] == 4)
			{
				spriteBatch.draw(glm::vec4(CAMERA.getScreenDimensions().x / WIDTH / 2 + j*CAMERA.getScreenDimensions().x / WIDTH, CAMERA.getScreenDimensions().y / HEIGHT / 2 + i*CAMERA.getScreenDimensions().y / HEIGHT, CAMERA.getScreenDimensions().x / WIDTH, CAMERA.getScreenDimensions().y / HEIGHT), 0.0f, uv, tile4.id, 0.0f, color);
			}
			else if (levelArray[i][j] == 5)
			{
				spriteBatch.draw(glm::vec4(CAMERA.getScreenDimensions().x / WIDTH / 2 + j*CAMERA.getScreenDimensions().x / WIDTH, CAMERA.getScreenDimensions().y / HEIGHT / 2 + i*CAMERA.getScreenDimensions().y / HEIGHT, CAMERA.getScreenDimensions().x / WIDTH, CAMERA.getScreenDimensions().y / HEIGHT), 0.0f, uv, tile5.id, 0.0f, color);
			}
			else if (levelArray[i][j] == 6)
			{
				spriteBatch.draw(glm::vec4(CAMERA.getScreenDimensions().x / WIDTH / 2 + j*CAMERA.getScreenDimensions().x / WIDTH, CAMERA.getScreenDimensions().y / HEIGHT / 2 + i*CAMERA.getScreenDimensions().y / HEIGHT, CAMERA.getScreenDimensions().x / WIDTH, CAMERA.getScreenDimensions().y / HEIGHT), 0.0f, uv, tile6.id, 0.0f, color);
			}
			else if (levelArray[i][j] == 7)
			{
				spriteBatch.draw(glm::vec4(CAMERA.getScreenDimensions().x / WIDTH / 2 + j*CAMERA.getScreenDimensions().x / WIDTH, CAMERA.getScreenDimensions().y / HEIGHT / 2 + i*CAMERA.getScreenDimensions().y / HEIGHT, CAMERA.getScreenDimensions().x / WIDTH, CAMERA.getScreenDimensions().y / HEIGHT), 0.0f, uv, tile7.id, 0.0f, color);
			}
			else if (levelArray[i][j] == 8)
			{
				spriteBatch.draw(glm::vec4(CAMERA.getScreenDimensions().x / WIDTH / 2 + j*CAMERA.getScreenDimensions().x / WIDTH, CAMERA.getScreenDimensions().y / HEIGHT / 2 + i*CAMERA.getScreenDimensions().y / HEIGHT, CAMERA.getScreenDimensions().x / WIDTH, CAMERA.getScreenDimensions().y / HEIGHT), 0.0f, uv, tile8.id, 0.0f, color);
			}
			else if (levelArray[i][j] == 9)
			{
				spriteBatch.draw(glm::vec4(CAMERA.getScreenDimensions().x / WIDTH / 2 + j*CAMERA.getScreenDimensions().x / WIDTH, CAMERA.getScreenDimensions().y / HEIGHT / 2 + i*CAMERA.getScreenDimensions().y / HEIGHT, CAMERA.getScreenDimensions().x / WIDTH, CAMERA.getScreenDimensions().y / HEIGHT), 0.0f, uv, tile9.id, 0.0f, color);
			}
			else if (levelArray[i][j] == 10)
			{
				spriteBatch.draw(glm::vec4(CAMERA.getScreenDimensions().x / WIDTH / 2 + j*CAMERA.getScreenDimensions().x / WIDTH, CAMERA.getScreenDimensions().y / HEIGHT / 2 + i*CAMERA.getScreenDimensions().y / HEIGHT, CAMERA.getScreenDimensions().x / WIDTH, CAMERA.getScreenDimensions().y / HEIGHT), 0.0f, uv, tile10.id, 0.0f, color);
			}
			else if (levelArray[i][j] == 11)
			{
				spriteBatch.draw(glm::vec4(CAMERA.getScreenDimensions().x / WIDTH / 2 + j*CAMERA.getScreenDimensions().x / WIDTH, CAMERA.getScreenDimensions().y / HEIGHT / 2 + i*CAMERA.getScreenDimensions().y / HEIGHT, CAMERA.getScreenDimensions().x / WIDTH, CAMERA.getScreenDimensions().y / HEIGHT), 0.0f, uv, tile11.id, 0.0f, color);
			}
			else if (levelArray[i][j] == 12)
			{
				spriteBatch.draw(glm::vec4(CAMERA.getScreenDimensions().x / WIDTH / 2 + j*CAMERA.getScreenDimensions().x / WIDTH, CAMERA.getScreenDimensions().y / HEIGHT / 2 + i*CAMERA.getScreenDimensions().y / HEIGHT, CAMERA.getScreenDimensions().x / WIDTH, CAMERA.getScreenDimensions().y / HEIGHT), 0.0f, uv, tile12.id, 0.0f, color);
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

	objects.push_back(new LevelWall(world, 0.5, 16.5, 0.5, 1.5));
	objects.push_back(new LevelWall(world, 5.0, 17.5, 4.0, 0.5));
	objects.push_back(new LevelWall(world, 10.0, 15.5, 1.0, 2.5));
	objects.push_back(new LevelWall(world, 12.5, 13.5, 1.5, 0.5));
	objects.push_back(new LevelWall(world, 16.0, 17.5, 2.0, 0.5));
	objects.push_back(new LevelWall(world, 19.5, 13.5, 1.5, 0.5));
	objects.push_back(new LevelWall(world, 22.0, 15.5, 1.0, 2.5));
	objects.push_back(new LevelWall(world, 27.0, 17.5, 4.0, 0.5));
	objects.push_back(new LevelWall(world, 31.5, 16.5, 0.5, 1.5));
	
	objects.push_back(new LevelWall(world, 1.0, 10.0, 1.0, 2.0));
	objects.push_back(new LevelWall(world, 3.5, 8.5, 1.5, 0.5));
	objects.push_back(new LevelWall(world, 6.0, 4.5, 2.0, 0.5));
	objects.push_back(new LevelWall(world, 9.0, 7.0, 1.0, 3.0));
	objects.push_back(new LevelWall(world, 11.0, 7.5, 1.0, 0.5));
	objects.push_back(new LevelWall(world, 21.0, 7.5, 1.0, 0.5));
	objects.push_back(new LevelWall(world, 23.0, 7.0, 1.0, 3.0));
	objects.push_back(new LevelWall(world, 26.0, 4.5, 2.0, 0.5));
	objects.push_back(new LevelWall(world, 28.5, 8.5, 1.5, 0.5));
	objects.push_back(new LevelWall(world, 31.0, 10.0, 1.0, 2.0));
	
	objects.push_back(new LevelWall(world, 0.5, 4.5, 0.5, 3.5));
	objects.push_back(new LevelWall(world, 5.5, 0.5, 5.5, 0.5));
	objects.push_back(new LevelWall(world, 16.0, 0.5, 2.0, 0.5));
	objects.push_back(new LevelWall(world, 16.0, 2.5, 1.0, 1.5));
	objects.push_back(new LevelWall(world, 26.5, 0.5, 5.5, 0.5));
	objects.push_back(new LevelWall(world, 31.5, 4.5, 0.5, 3.5));
	

	b2BodyDef bodyDef;
	m_groundBody = world->CreateBody(&bodyDef);

	LevelState::world->SetContactListener(&myContactListenerInstance);
}
