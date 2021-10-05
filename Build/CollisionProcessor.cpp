#include "CollisionProcessor.h"

//Resuelve las colisiones basadas en la identidad de cada objeto
void CollisionProcessor::BeginContact(b2Contact* contact) {

	chekedaabb(contact->GetFixtureA(), contact->GetFixtureB());
	chekedaabb(contact->GetFixtureB(), contact->GetFixtureA());
}

void CollisionProcessor::EndContact(b2Contact* contact) {

}

void CollisionProcessor::chekedaabb(b2Fixture* fixtureA, b2Fixture* fixtureB) {
	Ragdoll* bodyA = (Ragdoll*)fixtureA->GetBody();

	WinObject* bodyB = (WinObject*)fixtureB->GetBody();

	/* TODO: solucionar esto*/

	if (bodyA->GetId() == 0) {
		printf("UN RAGDOLL CHOCO CON ALGO\n");
		int id_b = bodyB->GetId();
		printf("ID 1: %d\tID 2:%d\n\n", bodyA->GetId(), id_b);
		
		switch (id_b)
		{
			case 0:
				printf("---------------Colision:  RAGDOLL <-> RAGDOLL--------------\n");
				break;

			case 1:
				printf("---------------Colision:  RAGDOLL <-> WIN OBJECT--------------\n");
				break;

			default:
				break;
		}
	}
}