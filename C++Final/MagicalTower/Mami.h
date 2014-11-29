#pragma once
#include "Character.h"
class Mami :
	public Character
{
public:
	Mami();
	~Mami();
	void init(int controllerNumber, float x, float y, b2World* world);
	void update(float timeStep);
	void draw(Bengine::SpriteBatch& spriteBatch);
private:
	bool justDied;
	float _alpha;
	Bengine::ColorRGBA8 color;
};

