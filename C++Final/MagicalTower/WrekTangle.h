#pragma once
#include "Character.h"
class WrekTangle :
	public Character
{
public:
	WrekTangle();
	~WrekTangle();
	void init();
	void update(float timeStep);
	void draw(Bengine::SpriteBatch spriteBatch);
};

