#pragma once
#include <Box2D/Box2D.h>
#include "../Build/Ragdoll.h"
#include "../Build/WinObject.h"

class CollisionProcessor : public b2ContactListener
{
public :
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void chekedaabb(b2Fixture *fixtureA, b2Fixture *fixtureB);
};

