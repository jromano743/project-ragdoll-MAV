#include "Obstacle.h"

Obstacle::Obstacle(b2World* _world, RenderWindow* _wnd,b2Vec2 position) {

	//Box2D
	world = _world;
	//SFML
	wnd = _wnd;

	//Setup
	float x = 5, y = 5;

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
}

//Dibuja los rectangulos (SFML)
void Obstacle::Draw() {
	wnd->draw(*shapeBox);
}

//Posiciona los rectangulos (SFML) en el mismo lugar que los cuerpos (Box2D)
void Obstacle::UpdatePosition() {
	shapeBox->setPosition(bodyBox->GetPosition().x, bodyBox->GetPosition().y);
	shapeBox->setRotation(bodyBox->GetAngle() * 180 / 3.14f);
}