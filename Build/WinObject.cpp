#include "WinObject.h"

WinObject::WinObject(b2World* _world, RenderWindow* _wnd, b2Vec2 position){
	//SFML
	wnd = _wnd;

	//Setup
	float x = 5, y = 5;
	id = 1;

	//Bodydef
	bodyDef.position = position;
	bodyDef.type = b2_staticBody;

	body = _world->CreateBody(&bodyDef);

	//Polygon shape
	b2PolygonShape* shp_box;
	shp_box = new b2PolygonShape();
	shp_box->SetAsBox(x, y);

	int* i = new int();
	*i = 1;
	body->SetUserData(i);

	//Fixture def
	fixtureDef.shape = shp_box;
	fixtureDef.density = 0.1f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.8f;

	//Box
	fixture = body->CreateFixture(&fixtureDef);

	//Shape Box
	shape = new RectangleShape;
	shape->setSize(Vector2f(x * 2, y * 2));
	shape->setFillColor(Color::Cyan);
	
	shape->setOrigin(shape->getSize().x / 2, shape->getSize().y / 2);
}

//Dibuja los rectangulos (SFML)
void WinObject::Draw() {
	wnd->draw(*shape);
}

//Posiciona los rectangulos (SFML) en el mismo lugar que los cuerpos (Box2D)
void WinObject::UpdatePosition() {
	shape->setPosition(body->GetPosition().x, body->GetPosition().y);
	shape->setRotation(body->GetAngle() * 180 / 3.14f);
}

int WinObject::GetUserData() {
	return id;
}

int WinObject::GetId() {
	return id;
}

void WinObject::SetId(int _id) {
	id = _id;
}

void WinObject::ChangeColor(int color) {
	switch (color)
	{
	case 0:
		
		break;
	case 1:

		break;
	default:
		break;
	}
}