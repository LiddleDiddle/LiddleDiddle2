#include "IntroGameState.h"
#include <iostream>
#include "MainMenuGameState.h"
#include <Bengine\ResourceManager.h>
#include "StartScreenState.h"
#include "MainGame.h"
IntroGameState::IntroGameState(const std::shared_ptr<GameStateManager> &gameStateManager) :
    gameStateManager(gameStateManager) 
{

}

void IntroGameState::Entered() {
    std::cout << "IntroGameState has been entered" << std::endl;
	_time = 0.0f;
	_startTime = false;
}

void IntroGameState::Exiting() {
    std::cout << "IntroGameState is exiting" << std::endl;
}

void IntroGameState::Update(float elapsedTime, Bengine::InputManager& inputManager) {
}

void IntroGameState::Draw(Bengine::SpriteBatch& spriteBatch)
{

	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static Bengine::GLTexture bg = Bengine::ResourceManager::getTexture("Textures/Character/character.png");
	static Bengine::GLTexture logo = Bengine::ResourceManager::getTexture("Textures/Logo.png");
	Bengine::ColorRGBA8 color;
	color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

	glm::vec4 rectangle = glm::vec4(MainGame::Instance()->_camera.getScreenDimensions().x / 2, MainGame::Instance()->_camera.getScreenDimensions().y / 2, MainGame::Instance()->_camera.getScreenDimensions().x / 1.43928035982, MainGame::Instance()->_camera.getScreenDimensions().y / 5.19230769231);
	spriteBatch.draw(glm::vec4(MainGame::Instance()->_camera.getScreenDimensions().x / 2, MainGame::Instance()->_camera.getScreenDimensions().y / 2, MainGame::Instance()->_camera.getScreenDimensions().x, MainGame::Instance()->_camera.getScreenDimensions().y), 0, uv, bg.id, 0.0f, color);
	spriteBatch.draw(rectangle, 0, uv, logo.id, 0.0f, color);
	this->gameStateManager->Switch(std::shared_ptr<GameState>(new StartScreenState(gameStateManager)));
}