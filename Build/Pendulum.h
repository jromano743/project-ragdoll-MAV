#pragma once
#include <Box2D/Box2D.h>
#include <SFML\Graphics.hpp>

using namespace sf;
class Pendulum
{
private:
	//StaticBox
	b2Body* bodyBox;
	b2BodyDef bodyBoxdef;
	b2Fixture* fixtureBox;
	b2FixtureDef fixtureBoxDef;

	RectangleShape* shapeBox;

	//Dinamic Box
	b2Body* bodyBoxB;
	b2BodyDef bodyBoxBdef;
	b2Fixture* fixtureBoxB;
	b2FixtureDef fixtureBoxBDef;

	RectangleShape* shapeBoxB;

	//SFML
	RenderWindow* wnd;

	//Box2D
	b2World* world;

	//Joint
	b2DistanceJoint* joint;
	b2DistanceJointDef jointDef;


public:
	Pendulum(b2World* _world, RenderWindow* _wnd, b2Vec2 position);
	void Draw();
	void UpdatePosition();
};

