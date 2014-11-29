#pragma once
#include "Entity.h"
#include <Box2D/Box2D.h>
#include <Bengine\SpriteBatch.h>
#include <Bengine\ResourceManager.h>
#include "GeneralManager.h"

enum ItemEnum
{
	MANA_ORB
};

class Item :
	public Entity
{
public:
	virtual void draw(Bengine::SpriteBatch& spriteBatch) = 0;
	virtual void update(float elapsedTime) = 0;
	int getEntityType() { return EntityEnum::ITEM; }
	int getItemType() { return itemType; }
	
	void kill() { alive = false;}
	bool living() { return alive; }
	b2Body* body;
protected:
	bool alive;
	int itemType;
};

