#pragma once
#include <Box2D/Box2D.h>
#include <SFML\Graphics.hpp>

using namespace sf;

class Ragdoll
{
private:

	//Setup
	b2Vec2 position;
	b2Vec2 dimHead;
	b2Vec2 dimBody;
	b2Vec2 dimEdge;
	int id;

	//SFML
	RenderWindow* wnd;
	
	//Ragdoll
	b2Body* body[6];
	b2BodyDef bodydef[6];
	b2Fixture* fixture[6];
	b2FixtureDef fixtureDef[6];

	//Rectangulos del ragdoll
	RectangleShape* rectShape[6];

	//Joint
	b2DistanceJoint* joint[5];
	b2DistanceJointDef jointDef[5];

public:
	Ragdoll(b2World* _world, RenderWindow* _wnd);
	Ragdoll(b2World* _world, RenderWindow* _wnd, b2Vec2 _position);
	void ApplyForce(float force, float rad_angle);
	void ApplyForce(Vector2f mouse_position, float force, float rad_angle);
	void UpdatePositions();
	void Draw();
	int GetUserData();
};