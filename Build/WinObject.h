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
	bool isTouched;

	RectangleShape* shape;

	//SFML
	RenderWindow* wnd;


public:
	WinObject(b2World* _world, RenderWindow* _wnd, b2Vec2 position);
	void Draw();
	void UpdatePosition();
	void ChangeColor();
	int GetUserData();
	bool GetIsTouched();
	void SetIsTouched(bool _isTouched);
};

