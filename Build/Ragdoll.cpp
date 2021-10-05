#include "Ragdoll.h"

Ragdoll::Ragdoll(b2World* _world, RenderWindow* _wnd) {
	//Setup
	wnd = _wnd;
	position = b2Vec2(50.f, 50.f);	//Position
	dimHead = b2Vec2(1,1);			//Size of head
	dimBody = b2Vec2(1.5,2.4);			//Size of body
	dimEdge = b2Vec2(0.75,2);		//Size of arms and legs
	id = 0;

	//Posicion del cuerpo
	bodydef[0].position = b2Vec2(position.x, position.y);												//	HEAD
	bodydef[1].position = b2Vec2(position.x, position.y + dimHead.y * 2);								//	BODY
	bodydef[2].position = b2Vec2(position.x + dimEdge.x * 2, position.y + dimHead.y * 2);				//	RIGHT ARM
	bodydef[3].position = b2Vec2(position.x - dimEdge.x * 2, position.y + dimHead.y * 2);				//	LEFT ARM
	bodydef[4].position = b2Vec2(position.x + dimEdge.x, position.y + dimHead.y * 2 + dimBody.y * 2);	//	RIGHT LEG
	bodydef[5].position = b2Vec2(position.x - dimEdge.x, position.y + dimHead.y * 2 + dimBody.y * 2);	//	LEFT LEG

	//Definicion de tipo de cuerpo y asignacion al mundo

	for (int i = 0; i < 6; i++) {
		bodydef[i].type = b2_dynamicBody;
		body[i] = _world->CreateBody(&bodydef[i]);
	}


	//Creacion de las figuras del cuerpo
	b2PolygonShape* shape[6];
	for (int i = 0; i < 6; i++) {
		shape[i] = new b2PolygonShape();
	}
	shape[0]->SetAsBox(dimHead.x, dimHead.y); //HEAD
	shape[1]->SetAsBox(dimBody.x, dimBody.y); //BODY
	shape[2]->SetAsBox(dimEdge.x, dimEdge.y); //RIGHT ARM
	shape[3]->SetAsBox(dimEdge.x, dimEdge.y); //LEFT ARM
	shape[4]->SetAsBox(dimEdge.x, dimEdge.y); //RIGHT LEG
	shape[5]->SetAsBox(dimEdge.x, dimEdge.y); //LEFT LEG

	//Configuracion y asignacion del fixture
	for (int i = 0; i < 6; i++) {
		fixtureDef[i].shape = shape[i];
		fixtureDef[i].density = 0.1f;
		fixtureDef[i].friction = 0.3f;
		fixtureDef[i].restitution = 0.8f;
		fixture[i] = body[i]->CreateFixture(&fixtureDef[i]);
	}

	//Joints (Resortes)
	//HEAD <-> BODY
	jointDef[0].Initialize(body[0], body[1], b2Vec2(body[0]->GetPosition().x, body[0]->GetPosition().y + dimHead.y), b2Vec2(body[1]->GetPosition().x, body[1]->GetPosition().y - dimBody.y));

	//BODY <-> RIGHT ARM
	jointDef[1].Initialize(body[1], body[2], b2Vec2(body[1]->GetPosition().x + dimBody.x, body[1]->GetPosition().y - dimBody.y), b2Vec2(body[2]->GetPosition().x - dimEdge.x, body[2]->GetPosition().y - dimEdge.y));

	//BODY <-> LEFT ARM
	jointDef[2].Initialize(body[1], body[3], b2Vec2(body[1]->GetPosition().x - dimBody.x, body[1]->GetPosition().y - dimBody.y), b2Vec2(body[3]->GetPosition().x + dimEdge.x, body[3]->GetPosition().y - dimEdge.y));

	//BODY <-> RIGHT LEG
	jointDef[3].Initialize(body[1], body[4], b2Vec2(body[1]->GetPosition().x + dimBody.x / 2, body[1]->GetPosition().y + dimBody.y), b2Vec2(body[4]->GetPosition().x, body[4]->GetPosition().y - dimEdge.y));

	//BODY <-> LEFT LEG
	jointDef[4].Initialize(body[1], body[5], b2Vec2(body[1]->GetPosition().x - dimBody.x / 2, body[1]->GetPosition().y + dimBody.y), b2Vec2(body[5]->GetPosition().x, body[5]->GetPosition().y - dimEdge.y));

	//Configuracion de los joints
	for (int i = 0; i < 5; i++) {
		jointDef[i].damping = 0.3f;
		jointDef[i].collideConnected = true;
		joint[i] = (b2DistanceJoint*)_world->CreateJoint(&jointDef[i]);
	}

	//Inicializacion de rectangulos
	for (int i = 0; i < 6; i++) {
		rectShape[i] = new RectangleShape;
	}

	//HEAD
	rectShape[0]->setSize(Vector2f(dimHead.x * 2, dimHead.y * 2));
	rectShape[0]->setFillColor(Color::Yellow);

	//BODY
	rectShape[1]->setSize(Vector2f(dimBody.x * 2, dimBody.y * 2));
	rectShape[1]->setFillColor(Color::Red);

	//RIGHT ARM
	rectShape[2]->setSize(Vector2f(dimEdge.x * 2, dimEdge.y * 2));
	rectShape[2]->setFillColor(Color::Yellow);

	//LEFT ARM
	rectShape[3]->setSize(Vector2f(dimEdge.x * 2, dimEdge.y * 2));
	rectShape[3]->setFillColor(Color::Yellow);

	//RIGHT LEG
	rectShape[4]->setSize(Vector2f(dimEdge.x * 2, dimEdge.y * 2));
	rectShape[4]->setFillColor(Color::Blue);

	//LEFT LEG
	rectShape[5]->setSize(Vector2f(dimEdge.x * 2, dimEdge.y * 2));
	rectShape[5]->setFillColor(Color::Blue);

	//Configuracion de origen de los rectangulos (SFML) como centro de los objetos (Box2D)
	for (int i = 0; i < 6; i++) {
		rectShape[i]->setOrigin(rectShape[i]->getSize().x / 2, rectShape[i]->getSize().y / 2);
	}
}

Ragdoll::Ragdoll(b2World* _world, RenderWindow* _wnd, b2Vec2 _position) {
	//Setup
	wnd = _wnd;
	position = _position;	//Position
	dimHead = b2Vec2(1, 1);			//Size of head
	dimBody = b2Vec2(1.5, 2.4);			//Size of body
	dimEdge = b2Vec2(0.75, 2);		//Size of arms and legs
	id = 0;

	//Posicion del cuerpo
	bodydef[0].position = b2Vec2(position.x, position.y);												//	HEAD
	bodydef[1].position = b2Vec2(position.x, position.y + dimHead.y * 2);								//	BODY
	bodydef[2].position = b2Vec2(position.x + dimEdge.x * 2, position.y + dimHead.y * 2);				//	RIGHT ARM
	bodydef[3].position = b2Vec2(position.x - dimEdge.x * 2, position.y + dimHead.y * 2);				//	LEFT ARM
	bodydef[4].position = b2Vec2(position.x + dimEdge.x, position.y + dimHead.y * 2 + dimBody.y * 2);	//	RIGHT LEG
	bodydef[5].position = b2Vec2(position.x - dimEdge.x, position.y + dimHead.y * 2 + dimBody.y * 2);	//	LEFT LEG

	//Definicion de tipo de cuerpo y asignacion al mundo
	for (int i = 0; i < 6; i++) {
		bodydef[i].type = b2_dynamicBody;
		body[i] = _world->CreateBody(&bodydef[i]);
	}


	//Creacion de las figuras del cuerpo
	b2PolygonShape* shape[6];
	for (int i = 0; i < 6; i++) {
		shape[i] = new b2PolygonShape();
	}
	shape[0]->SetAsBox(dimHead.x, dimHead.y); //HEAD
	shape[1]->SetAsBox(dimBody.x, dimBody.y); //BODY
	shape[2]->SetAsBox(dimEdge.x, dimEdge.y); //RIGHT ARM
	shape[3]->SetAsBox(dimEdge.x, dimEdge.y); //LEFT ARM
	shape[4]->SetAsBox(dimEdge.x, dimEdge.y); //RIGHT LEG
	shape[5]->SetAsBox(dimEdge.x, dimEdge.y); //LEFT LEG

	//Configuracion y asignacion del fixture
	for (int i = 0; i < 6; i++) {
		fixtureDef[i].shape = shape[i];
		fixtureDef[i].density = 0.1f;
		fixtureDef[i].friction = 0.3f;
		fixtureDef[i].restitution = 0.8f;
		fixture[i] = body[i]->CreateFixture(&fixtureDef[i]);
	}

	//Joints (Resortes)
	//HEAD <-> BODY
	jointDef[0].Initialize(body[0], body[1], b2Vec2(body[0]->GetPosition().x, body[0]->GetPosition().y + dimHead.y), b2Vec2(body[1]->GetPosition().x, body[1]->GetPosition().y - dimBody.y));

	//BODY <-> RIGHT ARM
	jointDef[1].Initialize(body[1], body[2], b2Vec2(body[1]->GetPosition().x + dimBody.x, body[1]->GetPosition().y - dimBody.y), b2Vec2(body[2]->GetPosition().x - dimEdge.x, body[2]->GetPosition().y - dimEdge.y));

	//BODY <-> LEFT ARM
	jointDef[2].Initialize(body[1], body[3], b2Vec2(body[1]->GetPosition().x - dimBody.x, body[1]->GetPosition().y - dimBody.y), b2Vec2(body[3]->GetPosition().x + dimEdge.x, body[3]->GetPosition().y - dimEdge.y));

	//BODY <-> RIGHT LEG
	jointDef[3].Initialize(body[1], body[4], b2Vec2(body[1]->GetPosition().x + dimBody.x / 2, body[1]->GetPosition().y + dimBody.y), b2Vec2(body[4]->GetPosition().x, body[4]->GetPosition().y - dimEdge.y));

	//BODY <-> LEFT LEG
	jointDef[4].Initialize(body[1], body[5], b2Vec2(body[1]->GetPosition().x - dimBody.x / 2, body[1]->GetPosition().y + dimBody.y), b2Vec2(body[5]->GetPosition().x, body[5]->GetPosition().y - dimEdge.y));

	//Configuracion de los joints
	for (int i = 0; i < 5; i++) {
		jointDef[i].damping = 0.3f;
		jointDef[i].collideConnected = true;
		joint[i] = (b2DistanceJoint*)_world->CreateJoint(&jointDef[i]);
	}

	//Inicializacion de rectangulos
	for (int i = 0; i < 6; i++) {
		rectShape[i] = new RectangleShape;
	}

	//HEAD
	rectShape[0]->setSize(Vector2f(dimHead.x * 2, dimHead.y * 2));
	rectShape[0]->setFillColor(Color::Yellow);

	//BODY
	rectShape[1]->setSize(Vector2f(dimBody.x * 2, dimBody.y * 2));
	rectShape[1]->setFillColor(Color::Red);

	//RIGHT ARM
	rectShape[2]->setSize(Vector2f(dimEdge.x * 2, dimEdge.y * 2));
	rectShape[2]->setFillColor(Color::Yellow);

	//LEFT ARM
	rectShape[3]->setSize(Vector2f(dimEdge.x * 2, dimEdge.y * 2));
	rectShape[3]->setFillColor(Color::Yellow);

	//RIGHT LEG
	rectShape[4]->setSize(Vector2f(dimEdge.x * 2, dimEdge.y * 2));
	rectShape[4]->setFillColor(Color::Blue);

	//LEFT LEG
	rectShape[5]->setSize(Vector2f(dimEdge.x * 2, dimEdge.y * 2));
	rectShape[5]->setFillColor(Color::Blue);

	//Configuracion de origen de los rectangulos (SFML) como centro de los objetos (Box2D)
	for (int i = 0; i < 6; i++) {
		rectShape[i]->setOrigin(rectShape[i]->getSize().x / 2, rectShape[i]->getSize().y / 2);
	}
}

//Dibuja los rectangulos (SFML)
void Ragdoll::Draw() {
	for (int i = 0; i < 6; i++) {
		wnd->draw(*rectShape[i]);
	}
}

//Posiciona los rectangulos (SFML) en el mismo lugar que los cuerpos (Box2D)
void Ragdoll::UpdatePositions() {
	for (int i = 0; i < 6; i++) {
		rectShape[i]->setPosition(body[i]->GetPosition().x, body[i]->GetPosition().y);
		rectShape[i]->setRotation(body[i]->GetAngle() * 180 / 3.14f);
	}
}

//Aplicar una fuerza al ragdoll
void Ragdoll::ApplyForce(float force, float rad_angle) {
	//Se aplica la fuerza sobre el body
	force = force * 100;
	body[1]->ApplyForceToCenter(b2Vec2(body[1]->GetPosition().x * force * cos(rad_angle), body[1]->GetPosition().y * force * sin(rad_angle)), false);
}

void Ragdoll::ApplyForce(Vector2f mouse_position, float force, float rad_angle) {
	body[1]->ApplyForceToCenter(b2Vec2(mouse_position.x*500, mouse_position.y*500), false);
}

int Ragdoll::GetUserData() {
	
	return id;
}

int Ragdoll::GetId() {
	return id;
}

void Ragdoll::SetId(int _id) {
	id = _id;
}