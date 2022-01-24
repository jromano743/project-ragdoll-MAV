#include "CollisionProcessor.h"

//Resuelve las colisiones basadas en la identidad de cada objeto
void CollisionProcessor::BeginContact(b2Contact* contact) {

	chekedaabb(contact->GetFixtureA(), contact->GetFixtureB());
	chekedaabb(contact->GetFixtureB(), contact->GetFixtureA());
}

void CollisionProcessor::EndContact(b2Contact* contact) {

}

void CollisionProcessor::chekedaabb(b2Fixture* fixtureA, b2Fixture* fixtureB) {
	b2Body* bodyA = fixtureA->GetBody();

	b2Body* bodyB = fixtureB->GetBody();

	int id1 = (int)bodyA->GetUserData().pointer;
	int id2 = (int)bodyB->GetUserData().pointer;

	if (id1 == 0) {
		switch (id2)
		{
			case 0:
				//printf("---------------Colision:  WIN OBJECTN -> OTRA COLISION--------------\n");
				break;

			case 1:
				//printf("---------------Colision:  RAGDOLL -> WIN OBJECT--------------\n");
				bodyB->GetUserData().pointer = (uintptr_t)0;
				break;
			case 2:
				//printf("---------------Colision:  OTRA COLISION -> WIN OBJECT--------------\n");
				break;

			default:
				break;
		}
	}
}