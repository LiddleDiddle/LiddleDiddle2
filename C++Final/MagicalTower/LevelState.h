#pragma once

#include "GameStateManager.h"
#include "GameState.h"
#include "Updateable.h"
#include "Drawable.h"
#include "GameObject.h"
#include "Ball.h"
#include <Bengine/InputManager.h>
#include <memory>
#include <Box2D/Box2D.h>
#include <Bengine/SpriteFont.h>
/// characters ----------
#include "WrekTangle.h"
#include "Homura.h"
#include "Mami.h"
#include "Sayaka.h"
///----------------------

#include "MyContactListener.h"
#include "Item.h"
#include "ManaOrb.h"

class LevelState : public GameState, public virtual Updateable, public virtual Drawable
{
public:
	/// <summary>Initializes a new intro game state</summary>
	/// <param name="gameStateManager">
	///   Game state manager that will be used to switch to various states
	/// </param>
	LevelState(const std::shared_ptr<GameStateManager> &gameStateManager);

	/// <summary>Called when the game state is entered</summary>
	void Entered();

	/// <summary>Called when the game state is about to be exited</summary>
	void Exiting();

	/// <summary>Updates the time in the game state's simulation</summary>
	/// <param name="elapsedTime">Time by which to advance the simulation</param>
	void Update(float elapsedTime, Bengine::InputManager& inputManager);

	void Draw(Bengine::SpriteBatch& spriteBatch);
	void ProcessInput(Bengine::InputManager _inputManager);
	void CreateBox2dWorld();
	static b2World* world;
	static std::vector<Item*> items;
	void drawWinner(int winner);
private:
	std::vector<Character*> _characters;
	std::shared_ptr<GameStateManager> gameStateManager;
	glm::vec4 startRect;
	int** levelArray;
	std::vector<GameObject*> objects;
	b2Body* m_groundBody;
	WrekTangle wrek;

	Bengine::SpriteBatch _fontSpriteBatch;
	Bengine::SpriteFont* _spriteFont;
	bool gameOver, check;
	int theWinner;
	MyContactListener myContactListenerInstance;
};