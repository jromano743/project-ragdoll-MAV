#pragma once
#include <Box2D/Box2D.h>
#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Build//Ragdoll.h"

using namespace sf;

class Canon
{
private:
	b2Body* body_canon;
	b2BodyDef bodyDef_canon;
	b2Fixture* fix_canon;
	b2FixtureDef fixDef_canon;

	RectangleShape* shape_canon;

	SoundBuffer bufferEmpty, bufferShoot;
	Sound emptySound, shooterSound;

	b2World* world;

	//SFML
	RenderWindow* wnd;

	//Setup
	float degreeRotation;
	b2Vec2 sizeCanon;
	b2Vec2 position;

	//Ragdoll Canon
	int currentRagdoll = 0;
	Ragdoll* bulletRagdool[6];
	float shootForce;

public:
	Canon(b2World* _world, RenderWindow* _wnd);
	void UpdatePosition();
	void Draw();
	void TurnCanon(bool right);
	void TurnCanonWithMouse(Vector2f mouse_coords);
	float degToRad(float degree);
	void ShootRagdoll();
	void ShootRagdollWithMouse(Vector2f mouse_position);
};

