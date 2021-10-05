#pragma once
#include <Box2D/Box2D.h>
#include <SFML\Graphics.hpp>

using namespace sf;
class WinObject
{
private:
	//SimpleBox
	b2Body* body;
	b2BodyDef bodyDef;
	b2Fixture* fixture;
	b2FixtureDef fixtureDef;
	int id;

	RectangleShape* shape;

	//SFML
	RenderWindow* wnd;


public:
	WinObject(b2World* _world, RenderWindow* _wnd, b2Vec2 position);
	WinObject(int _id) : id{ _id } {};
	void Draw();
	void UpdatePosition();
	void ChangeColor(int color);

	//user data
	int GetUserData();
	int GetId();
	void SetId(int _id);
};

