#include "Pendulum.h"

Pendulum::Pendulum(b2World* _world, RenderWindow* _wnd, b2Vec2 position) {

	//Box2D
	world = _world;
	//SFML
	wnd = _wnd;

	//Setup
	float x = 2.5f, y = 2.5f;

	//BOX A
	// 
	//Polygon shape
	b2PolygonShape* shp_box;
	shp_box = new b2PolygonShape();
	shp_box->SetAsBox(x, y);

	//Shape Box
	shapeBox = new RectangleShape;
	shapeBox->setFillColor(Color::Red);
	shapeBox->setSize(Vector2f(x * 2, y * 2));
	shapeBox->setOrigin(shapeBox->getSize().x / 2, shapeBox->getSize().y / 2);

	//Bodydef
	bodyBoxdef.type = b2_staticBody;
	bodyBoxdef.position = position;

	bodyBox = _world->CreateBody(&bodyBoxdef);

	//Fixture def
	fixtureBoxDef.shape = shp_box;
	fixtureBoxDef.density = 1.f;
	fixtureBoxDef.restitution = 0.1f;
	fixtureBoxDef.friction = 0.3f;

	//Box
	fixtureBox = bodyBox->CreateFixture(&fixtureBoxDef);

	//BOX B
	//
	b2PolygonShape* shp_boxB;
	shp_boxB = new b2PolygonShape();
	shp_boxB->SetAsBox(x, y);

	//Shape Box
	shapeBoxB = new RectangleShape;
	shapeBoxB->setFillColor(Color::Blue);
	shapeBoxB->setSize(Vector2f(x * 2, y * 2));
	shapeBoxB->setOrigin(shapeBoxB->getSize().x / 2, shapeBoxB->getSize().y / 2);

	//Bodydef
	bodyBoxBdef.type = b2_dynamicBody;
	bodyBoxBdef.position = b2Vec2(position.x-10.f, position.y+10.f);

	bodyBoxB = _world->CreateBody(&bodyBoxBdef);

	//Fixture def
	fixtureBoxBDef.shape = shp_box;
	fixtureBoxBDef.density = 1.f;
	fixtureBoxBDef.restitution = 0.1f;
	fixtureBoxBDef.friction = 0.3f;

	//Box
	fixtureBoxB = bodyBoxB->CreateFixture(&fixtureBoxBDef);

	//Joint
	jointDef.Initialize
	(bodyBox, bodyBoxB, 
		b2Vec2(bodyBox->GetPosition().x, bodyBoxB->GetPosition().y + y + 0.1f), b2Vec2(bodyBoxB->GetPosition().x, bodyBoxB->GetPosition().y - y - 0.1f));

	jointDef.damping = 0.3f;
	jointDef.collideConnected = true;
	joint = (b2DistanceJoint*)_world->CreateJoint(&jointDef);
}

//Dibuja los rectangulos (SFML)
void Pendulum::Draw() {
	wnd->draw(*shapeBox);
	wnd->draw(*shapeBoxB);
}

//Posiciona los rectangulos (SFML) en el mismo lugar que los cuerpos (Box2D)
void Pendulum::UpdatePosition() {
	shapeBox->setPosition(bodyBox->GetPosition().x, bodyBox->GetPosition().y);
	shapeBox->setRotation(bodyBox->GetAngle() * 180 / 3.14f);

	shapeBoxB->setPosition(bodyBoxB->GetPosition().x, bodyBoxB->GetPosition().y);
	shapeBoxB->setRotation(bodyBoxB->GetAngle() * 180 / 3.14f);
}