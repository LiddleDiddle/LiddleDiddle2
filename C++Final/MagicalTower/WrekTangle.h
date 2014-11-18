#pragma once
#include "Character.h"
class WrekTangle :
	public Character
{
public:
	WrekTangle();
	~WrekTangle();
	void init(int x, int y, b2World* world);
	void update(float timeStep);
	void draw(Bengine::SpriteBatch spriteBatch);
};

