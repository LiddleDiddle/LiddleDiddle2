#include "MainMenuState.h"
#include "TilemapEditorState.h"
#include <iostream>
#include <Bengine/ResourceManager.h>
#include <SDL/SDL.h>
#include "MainMenuGameState.h"
#include "TylerMenuState.h"
#include "GeneralManager.h"
#include "ControllerMenuState.h"
#include "StartScreenState.h"
#include "MainGame.h"
#define MENUCONTROLLER TheGeneralManager::Instance()->MenuController

MainMenuState::MainMenuState(const std::shared_ptr<GameStateManager> &gameStateManager) :
    gameStateManager(gameStateManager) 
{

}

void MainMenuState::Entered() {
    std::cout << "IntroGameState has been entered" << std::endl;
	_time = 0.0f;
	rects = new glm::vec4[7];
	for (int i = 0; i < 7; i++)
	{
		rects[i] = glm::vec4(MainGame::Instance()->_camera.getScreenDimensions().x *.85, MainGame::Instance()->_camera.getScreenDimensions().y - (i + 1) * MainGame::Instance()->_camera.getScreenDimensions().y / 16 * 2, MainGame::Instance()->_camera.getScreenDimensions().x / 6.4, MainGame::Instance()->_camera.getScreenDimensions().y / 14.4);
	}
	_hover = 0;
	
					
}

void MainMenuState::Exiting() {
    std::cout << "IntroGameState is exiting" << std::endl;
}

void MainMenuState::Update(float elapsedTime, Bengine::InputManager& inputManager) {
	_time += elapsedTime;
	checkCollision(inputManager);
	if(MENUCONTROLLER != -1)
		processControllerInputs();
}

void MainMenuState::Draw(Bengine::SpriteBatch& spriteBatch)
{
	
	Bengine::ColorRGBA8 hoverColor(255,255,255,255);
	Bengine::ColorRGBA8 color(150,150,150,255);

	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static Bengine::GLTexture pink = Bengine::ResourceManager::getTexture("Textures/pinkBG.png");
	static Bengine::GLTexture mainMenuBG = Bengine::ResourceManager::getTexture("Textures/mainMenuBG.png");
	static Bengine::GLTexture tint = Bengine::ResourceManager::getTexture("Textures/tint.png");
	static Bengine::GLTexture singlePlayer = Bengine::ResourceManager::getTexture("Textures/MainMenu/singlePlayerText.png");
	static Bengine::GLTexture multiplayer = Bengine::ResourceManager::getTexture("Textures/MainMenu/multiplayerText.png");
	static Bengine::GLTexture mapEditor = Bengine::ResourceManager::getTexture("Textures/MainMenu/mapEditorText.png");
	static Bengine::GLTexture tutorial = Bengine::ResourceManager::getTexture("Textures/MainMenu/tutorialText.png");
	static Bengine::GLTexture settings = Bengine::ResourceManager::getTexture("Textures/MainMenu/settingsText.png");
	static Bengine::GLTexture extras = Bengine::ResourceManager::getTexture("Textures/MainMenu/extrasText.png");
	static Bengine::GLTexture exit = Bengine::ResourceManager::getTexture("Textures/MainMenu/exitText.png");

	


	glm::vec4 rectangle = glm::vec4(MainGame::Instance()->_camera.getScreenDimensions().x / 2, MainGame::Instance()->_camera.getScreenDimensions().y / 2, MainGame::Instance()->_camera.getScreenDimensions().x, MainGame::Instance()->_camera.getScreenDimensions().y);
	spriteBatch.draw(glm::vec4(MainGame::Instance()->_camera.getScreenDimensions().x / 2, MainGame::Instance()->_camera.getScreenDimensions().y / 2, MainGame::Instance()->_camera.getScreenDimensions().x, MainGame::Instance()->_camera.getScreenDimensions().y), 0, uv, pink.id, 0, hoverColor);
	spriteBatch.draw(glm::vec4(MainGame::Instance()->_camera.getScreenDimensions().x / 1.64102564103 / 2, MainGame::Instance()->_camera.getScreenDimensions().y / 2, MainGame::Instance()->_camera.getScreenDimensions().x / 1.64102564103, MainGame::Instance()->_camera.getScreenDimensions().y), 0, uv, mainMenuBG.id, 0, hoverColor);
	spriteBatch.draw(glm::vec4(MainGame::Instance()->_camera.getScreenDimensions().x * 0.875, MainGame::Instance()->_camera.getScreenDimensions().y / 2, MainGame::Instance()->_camera.getScreenDimensions().x / 4, MainGame::Instance()->_camera.getScreenDimensions().y), 0, uv, tint.id, 0, hoverColor);
	if(_hover == 0)
		spriteBatch.draw(rects[0],0,uv,singlePlayer.id,0,hoverColor);
	else
		spriteBatch.draw(rects[0],0,uv,singlePlayer.id,0,color);
	if(_hover == 1)
		spriteBatch.draw(rects[1],0,uv,multiplayer.id,0,hoverColor);
	else
		spriteBatch.draw(rects[1],0,uv,multiplayer.id,0,color);
	if(_hover == 2)
		spriteBatch.draw(rects[2],0,uv,mapEditor.id,0,hoverColor);
	else
		spriteBatch.draw(rects[2],0,uv,mapEditor.id,0,color);
	if(_hover == 3)
		spriteBatch.draw(rects[3],0,uv,tutorial.id,0,hoverColor);
	else
		spriteBatch.draw(rects[3],0,uv,tutorial.id,0,color);
	if(_hover == 4)
		spriteBatch.draw(rects[4],0,uv,settings.id,0,hoverColor);
	else
		spriteBatch.draw(rects[4],0,uv,settings.id,0,color);
	if(_hover == 5)
		spriteBatch.draw(rects[5],0,uv,extras.id,0,hoverColor);
	else
		spriteBatch.draw(rects[5],0,uv,extras.id,0,color);
	if(_hover == 6)
		spriteBatch.draw(rects[6],0,uv,exit.id,0,hoverColor);
	else
		spriteBatch.draw(rects[6],0,uv,exit.id,0,color);
}

void MainMenuState::checkCollision(Bengine::InputManager inputManager){
	
	glm::vec2 mouseCoords = inputManager.getMouseCoords();
	mouseCoords = TheMainGame::Instance()->_camera.convertScreenToWorld(mouseCoords);

	for (int i = 0; i < 7; i++)
	{
		if (mouseCoords.x < rects[i].x + rects[i][2] / 2 && mouseCoords.x > rects[i].x - rects[i][2] / 2 && mouseCoords.y < rects[i].y + rects[i][3] / 2 && mouseCoords.y > rects[i].y - rects[i][3] / 2)
		{
			if (inputManager.isKeyDown(SDL_BUTTON_LEFT))
			{
				switch (i)
				{
				case 0 :
					this->gameStateManager->Switch(std::shared_ptr<GameState>(new TylerMenuState(gameStateManager)));
					return;
					break;
				case 1 :
					this->gameStateManager->Switch(std::shared_ptr<GameState>(new ControllerMenuState(gameStateManager)));
					return;
					break;
				case 2 :
					this->gameStateManager->Switch(std::shared_ptr<GameState>(new TilemapEditorState(gameStateManager)));
					return;
					break;
				case 3 :
					this->gameStateManager->Switch(std::shared_ptr<GameState>(new TylerMenuState(gameStateManager)));
					return;
					break;
				case 4 :
					this->gameStateManager->Switch(std::shared_ptr<GameState>(new TylerMenuState(gameStateManager)));
					return;
					break;
				case 5 :
					this->gameStateManager->Switch(std::shared_ptr<GameState>(new TylerMenuState(gameStateManager)));
					return;
					break;
				case 6 :
					this->gameStateManager->Switch(std::shared_ptr<GameState>(new TylerMenuState(gameStateManager)));
					return;
					break;
				}
			}
			_hover = i;
		}
	}
}

void MainMenuState::processControllerInputs(){
	if(TheGeneralManager::Instance()->_players[MENUCONTROLLER].isKeyPressed(SDL_CONTROLLER_BUTTON_A))
	{
		switch (_hover)
		{
		case 0 :
			this->gameStateManager->Switch(std::shared_ptr<GameState>(new TylerMenuState(gameStateManager)));
			return;
			break;
		case 1 :
			this->gameStateManager->Switch(std::shared_ptr<GameState>(new ControllerMenuState(gameStateManager)));
			return;
			break;
		case 2 :
			this->gameStateManager->Switch(std::shared_ptr<GameState>(new TylerMenuState(gameStateManager)));
			return;
			break;
		case 3 :
			this->gameStateManager->Switch(std::shared_ptr<GameState>(new TylerMenuState(gameStateManager)));
			return;
			break;
		case 4 :
			this->gameStateManager->Switch(std::shared_ptr<GameState>(new TylerMenuState(gameStateManager)));
			return;
			break;
		case 5 :
			this->gameStateManager->Switch(std::shared_ptr<GameState>(new TylerMenuState(gameStateManager)));
			return;
			break;
		case 6 :
			this->gameStateManager->Switch(std::shared_ptr<GameState>(new TylerMenuState(gameStateManager)));
			return;
			break;
		}
	}

	if(TheGeneralManager::Instance()->_players[MENUCONTROLLER].isKeyPressed(SDL_CONTROLLER_BUTTON_DPAD_DOWN ))
	{
		_hover++;
		if(_hover > 6)
			_hover = 0;
	}

	if(TheGeneralManager::Instance()->_players[MENUCONTROLLER].isKeyPressed(SDL_CONTROLLER_BUTTON_DPAD_UP ))
	{
		_hover--;
		if(_hover < 0)
			_hover = 6;
	}

	if(TheGeneralManager::Instance()->_players[MENUCONTROLLER].isKeyPressed(SDL_CONTROLLER_BUTTON_B ))
	{
		this->gameStateManager->Switch(std::shared_ptr<GameState>(new StartScreenState(gameStateManager)));
	}
}

