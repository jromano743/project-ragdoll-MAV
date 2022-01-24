#pragma once
#include <Box2D/Box2D.h>
#include <SFML\Graphics.hpp>

using namespace sf;

class Obstacle
{
private:
	//SimpleBox
	b2Body* bodyBox;
	b2BodyDef bodyBoxdef;
	b2Fixture* fixtureBox;
	b2FixtureDef fixtureBoxDef;

	RectangleShape* shapeBox;

	//SFML
	RenderWindow* wnd;

	//Box2D
	b2World* world;

	int id;


public:
	Obstacle(b2World* _world, RenderWindow* _wnd, b2Vec2 position);
	void Draw();
	void UpdatePosition();
};

