#include "MultiCharacterSelectState.h"
#include "TylerMenuState.h"
#include "MainMenuState.h"
#include "StageSelectState.h"
#include <iostream>
#include <SDL/SDL.h>
#include <Bengine/ResourceManager.h>
#include "ControllerMenuState.h"
#include "GeneralManager.h"
#include "MainGame.h"
#include "LevelState.h"
#define GENERAL_MANAGER TheGeneralManager::Instance()

MultiCharacterSelectState::MultiCharacterSelectState(const std::shared_ptr<GameStateManager> &gameStateManager) :
    gameStateManager(gameStateManager) 
{
	
}

MultiCharacterSelectState::~MultiCharacterSelectState()
{
	delete _character;
	delete _ready;
	delete _joined;
}

void MultiCharacterSelectState::Entered() {
    std::cout << "MainMenuState has been entered" << std::endl;

	float quarterScreen = TheMainGame::Instance()->_camera.getScreenDimensions().x / 4;

	_one = glm::vec4(quarterScreen/2, TheMainGame::Instance()->_camera.getScreenDimensions().y / 2, quarterScreen, TheMainGame::Instance()->_camera.getScreenDimensions().y);
	_two = glm::vec4(quarterScreen / 2 + quarterScreen, TheMainGame::Instance()->_camera.getScreenDimensions().y / 2, quarterScreen, TheMainGame::Instance()->_camera.getScreenDimensions().y);
	_three = glm::vec4(quarterScreen / 2 + quarterScreen * 2, TheMainGame::Instance()->_camera.getScreenDimensions().y / 2, quarterScreen, TheMainGame::Instance()->_camera.getScreenDimensions().y);
	_four = glm::vec4(quarterScreen + quarterScreen * 3, TheMainGame::Instance()->_camera.getScreenDimensions().y / 2, quarterScreen, TheMainGame::Instance()->_camera.getScreenDimensions().y);
	_mousePressed = true;

	_ready = new bool[4];
	_character = new int[4];
	_direction = new Direction[4];
	_joined = new bool[4];
	for (int i = 0; i < 4; i++)
	{
		_ready[i] = false;
		_joined[i] = false;
		_character[i] = i;
		_direction[i] = Direction::NEUTRAL;
	}
	
	_numPlayers = TheGeneralManager::Instance()->_joinedPlayers.size();
	for (int i = 0; i < _numPlayers; i++)
	{
		_joined[i] = true;
	}
}

void MultiCharacterSelectState::Exiting() {
    std::cout << "MainMenuState is exiting" << std::endl;
}

void MultiCharacterSelectState::Update(float elapsedTime, Bengine::InputManager& _inputManager) {
	for (int i = 0; i < _numPlayers; i++)
	{
		if(GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[i]].isKeyPressed(SDL_CONTROLLER_BUTTON_DPAD_UP ) && !_ready[i]){
			_character[i]++;
			if(_character[i] > 3)
				_character[i] = 0;
		}

		if (GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[i]].isKeyPressed(SDL_CONTROLLER_BUTTON_DPAD_DOWN) && !_ready[i]){
			_character[i]--;
			if(_character[i] < 0)
				_character[i] = 3;
		}

		_direction[i] = Direction::NEUTRAL;


		if (GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[i]].isKeyDown(SDL_CONTROLLER_BUTTON_DPAD_UP) && !_ready[i]){
			_direction[i] = Direction::UP;
		}

		if (GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[i]].isKeyDown(SDL_CONTROLLER_BUTTON_DPAD_DOWN) && !_ready[i]){
			_direction[i] = Direction::DOWN;
		}

		if(GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[i]].isKeyPressed(SDL_CONTROLLER_BUTTON_A )){
			_ready[i] = true;
			GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[i]].selectedCharacter = _character[i];
		}

		if(GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[i]].isKeyPressed(SDL_CONTROLLER_BUTTON_B )){
			if(!_ready[i])
			{
				this->gameStateManager->Switch(std::shared_ptr<GameState>(new ControllerMenuState(gameStateManager)));
				return;
			}
			if(_ready[i])
				_ready[i] = false;
		}
		if(GENERAL_MANAGER->_players[GENERAL_MANAGER->_joinedPlayers[i]].isKeyPressed(SDL_CONTROLLER_BUTTON_START)){
			bool isEveryoneReady = true;
			for (int j = 0; j < _numPlayers; j++)
			{
				if (!_ready[j])
				{
					isEveryoneReady = false;
				}
			}
			if (isEveryoneReady)
			{
				this->gameStateManager->Switch(std::shared_ptr<GameState>(new LevelState(gameStateManager)));
				return;
			}
		}
	}

}

void MultiCharacterSelectState::Draw(Bengine::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Bengine::ColorRGBA8 color;
	color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

	Bengine::ColorRGBA8 green;
	green.r = 0;
    green.g = 255;
    green.b = 0;
    green.a = 255;

	static Bengine::GLTexture bg = Bengine::ResourceManager::getTexture("Textures/CharacterSelect/blankBG.png");
	static Bengine::GLTexture join = Bengine::ResourceManager::getTexture("Textures/CharacterSelect/join.png");

	//characters
	static Bengine::GLTexture madoka = Bengine::ResourceManager::getTexture("Textures/CharacterSelect/madoka.png");
	static Bengine::GLTexture homura = Bengine::ResourceManager::getTexture("Textures/CharacterSelect/homura.png");
	static Bengine::GLTexture mami = Bengine::ResourceManager::getTexture("Textures/CharacterSelect/mami.png");
	static Bengine::GLTexture sayaka = Bengine::ResourceManager::getTexture("Textures/CharacterSelect/sayaka.png");

	static Bengine::GLTexture ready = Bengine::ResourceManager::getTexture("Textures/CharacterSelect/ready.png");
	static Bengine::GLTexture border = Bengine::ResourceManager::getTexture("Textures/CharacterSelect/border.png");
	static Bengine::GLTexture arrow = Bengine::ResourceManager::getTexture("Textures/CharacterSelect/arrowUp.png");
	static Bengine::GLTexture beginBar = Bengine::ResourceManager::getTexture("Textures/CharacterSelect/beginBar.png");
	bool isEveryoneReady = true;
	for (int j = 0; j < _numPlayers; j++)
	{
		if (!_ready[j])
		{
			isEveryoneReady = false;
		}
	}
	if (isEveryoneReady)
	{
		spriteBatch.draw(glm::vec4(TheMainGame::Instance()->_camera.getScreenDimensions().x/2, TheMainGame::Instance()->_camera.getScreenDimensions().y/2,TheMainGame::Instance()->_camera.getScreenDimensions().x,TheMainGame::Instance()->_camera.getScreenDimensions().y / 8.64), 0, uv, beginBar.id, 0.0f, color);
	}
	for (int i = 0; i < 4; i++)
	{
		spriteBatch.draw(glm::vec4(TheMainGame::Instance()->_camera.getScreenDimensions().x / 8 + TheMainGame::Instance()->_camera.getScreenDimensions().x / 4 * i, TheMainGame::Instance()->_camera.getScreenDimensions().y / 2, TheMainGame::Instance()->_camera.getScreenDimensions().x / 4, TheMainGame::Instance()->_camera.getScreenDimensions().y), 0, uv, border.id, 0.0f, color);
		if(!_joined[i])
		{
			spriteBatch.draw(glm::vec4(TheMainGame::Instance()->_camera.getScreenDimensions().x / 8 + TheMainGame::Instance()->_camera.getScreenDimensions().x / 4 * i, TheMainGame::Instance()->_camera.getScreenDimensions().y / 2, TheMainGame::Instance()->_camera.getScreenDimensions().x / 4, TheMainGame::Instance()->_camera.getScreenDimensions().y), 0, uv, bg.id, 0.0f, color);
			spriteBatch.draw(glm::vec4(TheMainGame::Instance()->_camera.getScreenDimensions().x / 8 + TheMainGame::Instance()->_camera.getScreenDimensions().x / 4 * i, TheMainGame::Instance()->_camera.getScreenDimensions().y / 2, TheMainGame::Instance()->_camera.getScreenDimensions().x / 5.3781512605, TheMainGame::Instance()->_camera.getScreenDimensions().y / 3.89189189189), 0, uv, join.id, -1.0f, color);
		}
		if(_joined[i])
		{
			
			switch (_character[i])
			{
			case 0:
				spriteBatch.draw(glm::vec4(TheMainGame::Instance()->_camera.getScreenDimensions().x / 8 + TheMainGame::Instance()->_camera.getScreenDimensions().x / 4 * i, TheMainGame::Instance()->_camera.getScreenDimensions().y / 2, TheMainGame::Instance()->_camera.getScreenDimensions().x / 4, TheMainGame::Instance()->_camera.getScreenDimensions().y), 0, uv, madoka.id, 0.0f, color);
				break;
			case 1:
				spriteBatch.draw(glm::vec4(TheMainGame::Instance()->_camera.getScreenDimensions().x / 8 + TheMainGame::Instance()->_camera.getScreenDimensions().x / 4 * i, TheMainGame::Instance()->_camera.getScreenDimensions().y / 2, TheMainGame::Instance()->_camera.getScreenDimensions().x / 4, TheMainGame::Instance()->_camera.getScreenDimensions().y), 0, uv, homura.id, 0.0f, color);
				break;
			case 2:
				spriteBatch.draw(glm::vec4(TheMainGame::Instance()->_camera.getScreenDimensions().x / 8 + TheMainGame::Instance()->_camera.getScreenDimensions().x / 4 * i, TheMainGame::Instance()->_camera.getScreenDimensions().y / 2, TheMainGame::Instance()->_camera.getScreenDimensions().x / 4, TheMainGame::Instance()->_camera.getScreenDimensions().y), 0, uv, mami.id, 0.0f, color);
				break;
			case 3:
				spriteBatch.draw(glm::vec4(TheMainGame::Instance()->_camera.getScreenDimensions().x / 8 + TheMainGame::Instance()->_camera.getScreenDimensions().x / 4 * i, TheMainGame::Instance()->_camera.getScreenDimensions().y / 2, TheMainGame::Instance()->_camera.getScreenDimensions().x / 4, TheMainGame::Instance()->_camera.getScreenDimensions().y), 0, uv, sayaka.id, 0.0f, color);
				break;
			}

			switch (_direction[i])
			{
			case Direction::NEUTRAL:
				spriteBatch.draw(glm::vec4(TheMainGame::Instance()->_camera.getScreenDimensions().x / 8 + TheMainGame::Instance()->_camera.getScreenDimensions().x / 4 * i, TheMainGame::Instance()->_camera.getScreenDimensions().y - TheMainGame::Instance()->_camera.getScreenDimensions().y / 20.5714285714, TheMainGame::Instance()->_camera.getScreenDimensions().x / 21.3333333333, TheMainGame::Instance()->_camera.getScreenDimensions().y / 24), 0, uv, arrow.id, 0.0f, color);
				spriteBatch.draw(glm::vec4(TheMainGame::Instance()->_camera.getScreenDimensions().x / 8 + TheMainGame::Instance()->_camera.getScreenDimensions().x / 4 * i, TheMainGame::Instance()->_camera.getScreenDimensions().y / 20.5714285714, TheMainGame::Instance()->_camera.getScreenDimensions().x / 21.3333333333, TheMainGame::Instance()->_camera.getScreenDimensions().y / 24), 3.14159265359, uv, arrow.id, 0.0f, color);
				break;
			case Direction::UP:
				spriteBatch.draw(glm::vec4(TheMainGame::Instance()->_camera.getScreenDimensions().x / 8 + TheMainGame::Instance()->_camera.getScreenDimensions().x / 4 * i, TheMainGame::Instance()->_camera.getScreenDimensions().y - TheMainGame::Instance()->_camera.getScreenDimensions().y / 20.5714285714, TheMainGame::Instance()->_camera.getScreenDimensions().x / 21.3333333333, TheMainGame::Instance()->_camera.getScreenDimensions().y / 24), 0, uv, arrow.id, 0.0f, green);
				spriteBatch.draw(glm::vec4(TheMainGame::Instance()->_camera.getScreenDimensions().x / 8 + TheMainGame::Instance()->_camera.getScreenDimensions().x / 4 * i, TheMainGame::Instance()->_camera.getScreenDimensions().y / 20.5714285714, TheMainGame::Instance()->_camera.getScreenDimensions().x / 21.3333333333, TheMainGame::Instance()->_camera.getScreenDimensions().y / 24), 3.14159265359, uv, arrow.id, 0.0f, color);
				break;
			case Direction::DOWN:
				spriteBatch.draw(glm::vec4(TheMainGame::Instance()->_camera.getScreenDimensions().x / 8 + TheMainGame::Instance()->_camera.getScreenDimensions().x / 4 * i, TheMainGame::Instance()->_camera.getScreenDimensions().y - TheMainGame::Instance()->_camera.getScreenDimensions().y / 20.5714285714, TheMainGame::Instance()->_camera.getScreenDimensions().x / 21.3333333333, TheMainGame::Instance()->_camera.getScreenDimensions().y / 24), 0, uv, arrow.id, 0.0f, color);
				spriteBatch.draw(glm::vec4(TheMainGame::Instance()->_camera.getScreenDimensions().x / 8 + TheMainGame::Instance()->_camera.getScreenDimensions().x / 4 * i, TheMainGame::Instance()->_camera.getScreenDimensions().y / 20.5714285714, TheMainGame::Instance()->_camera.getScreenDimensions().x / 21.3333333333, TheMainGame::Instance()->_camera.getScreenDimensions().y / 24), 3.14159265359, uv, arrow.id, 0.0f, green);
				break;
			}
		}
		if(_ready[i])
		{
			spriteBatch.draw(glm::vec4(TheMainGame::Instance()->_camera.getScreenDimensions().x / 8 + TheMainGame::Instance()->_camera.getScreenDimensions().x / 4 * i, TheMainGame::Instance()->_camera.getScreenDimensions().y / 2, TheMainGame::Instance()->_camera.getScreenDimensions().x / 5.12, TheMainGame::Instance()->_camera.getScreenDimensions().y / 2.88), 0, uv, ready.id, 0.0f, color);
		}
	}
}