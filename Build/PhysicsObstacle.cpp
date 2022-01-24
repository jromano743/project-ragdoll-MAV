#include "PhysicsObstacle.h"
PhysicsObstacle::PhysicsObstacle(b2World* _world, RenderWindow* _wnd, b2Vec2 position) {

	//Box2D
	world = _world;
	//SFML
	wnd = _wnd;

	//Setup
	float x = 5, y = 5;

	id = 2;

	//Polygon shape
	b2PolygonShape* shp_box;
	shp_box = new b2PolygonShape();
	shp_box->SetAsBox(x, y);

	//Shape Box
	shapeBox = new RectangleShape;
	shapeBox->setFillColor(Color::Yellow);
	shapeBox->setSize(Vector2f(x * 2, y * 2));
	shapeBox->setOrigin(shapeBox->getSize().x / 2, shapeBox->getSize().y / 2);

	//Bodydef
	bodyBoxdef.type = b2_dynamicBody;
	bodyBoxdef.position = position;

	bodyBox = _world->CreateBody(&bodyBoxdef);

	//Id de colision
	bodyBox->GetUserData().pointer = (uintptr_t)id;

	//Fixture def
	fixtureBoxDef.shape = shp_box;
	fixtureBoxDef.density = 0.3f;
	fixtureBoxDef.restitution = 0.1f;
	fixtureBoxDef.friction = 0.3f;

	//Box
	fixtureBox = bodyBox->CreateFixture(&fixtureBoxDef);
}

//Dibuja los rectangulos (SFML)
void PhysicsObstacle::Draw() {
	wnd->draw(*shapeBox);
}

//Posiciona los rectangulos (SFML) en el mismo lugar que los cuerpos (Box2D)
void PhysicsObstacle::UpdatePosition() {
	shapeBox->setPosition(bodyBox->GetPosition().x, bodyBox->GetPosition().y);
	shapeBox->setRotation(bodyBox->GetAngle() * 180 / 3.14f);
}