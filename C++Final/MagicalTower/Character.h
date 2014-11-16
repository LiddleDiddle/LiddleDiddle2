#pragma once
#include <Bengine/SpriteBatch.h>
#include <Bengine/ResourceManager.h>
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
	//CharacterState* _state;
	Bengine::GLTexture _texture;
};

