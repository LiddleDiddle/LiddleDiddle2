#pragma once
#include "CharacterState.h"
#include <Bengine/SpriteBatch.h>

class Character
{
public:
	Character();
	~Character();

	void handleInput(int controller);
	void update();
	void setTexture(Bengine::GLTexture texture) { _texture = texture; }
	void draw(Bengine::SpriteBatch& spriteBatch);
private:
	CharacterState* _state;
	Bengine::GLTexture _texture;
};

