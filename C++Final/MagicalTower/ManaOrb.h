#pragma once
#include "Item.h"
class ManaOrb : public Item
{
public:
	ManaOrb(float x, float y, float mana);
	~ManaOrb();
	void update(float elapsedTime);
	void draw(Bengine::SpriteBatch& spriteBatch);
	int getItemType() { return itemType; }
	float getMana() { return _mana; }
private:
	float _mana;
};

