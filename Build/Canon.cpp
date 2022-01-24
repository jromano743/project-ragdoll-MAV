#include "Canon.h"

Canon::Canon(b2World* _world, RenderWindow* _wnd) {
	//Box2D
	world = _world;

	//SFML
	wnd = _wnd;

	//Setup
	sizeCanon = b2Vec2(10.f,4.f);
	position = b2Vec2(10.f, 90.f);
	degreeRotation = 3;
	shootForce = 12.f;

	//Polygon shape
	b2PolygonShape* shp_canon;
	shp_canon = new b2PolygonShape();
	shp_canon->SetAsBox(sizeCanon.x, sizeCanon.y); // x = ancho del cuerpo (dimBody) del ragdoll

	//Shape
	shape_canon = new RectangleShape;
	shape_canon->setFillColor(Color::Red);
	shape_canon->setSize(Vector2f(sizeCanon.x * 2, sizeCanon.y * 2));
	shape_canon->setOrigin(0, shape_canon->getSize().y / 2);

	//Bodydef
	bodyDef_canon.type = b2_staticBody;
	bodyDef_canon.position = b2Vec2(position.x,position.y);

	body_canon = _world->CreateBody(&bodyDef_canon);

	//Fixture def
	fixDef_canon.shape = shp_canon;
	fixDef_canon.density = 1.f;
	fixDef_canon.restitution = 0.1f;
	fixDef_canon.friction = 0.3f;

	//Canon
	fix_canon = body_canon->CreateFixture(&fixDef_canon);

	bufferEmpty.loadFromFile("../Build/res/audio/canonEmpty.wav");
	emptySound.setBuffer(bufferEmpty);

	bufferShoot.loadFromFile("../Build/res/audio/canonShoot.wav");
	shooterSound.setBuffer(bufferShoot);
}

//Dibuja los rectangulos (SFML)
void Canon::Draw() {
	wnd->draw(*shape_canon);
	for (int i = 0; i < currentRagdoll; i++) {
		bulletRagdool[i]->Draw();
	}
}

//Posiciona los rectangulos (SFML) en el mismo lugar que los cuerpos (Box2D)
void Canon::UpdatePosition() {
	shape_canon->setPosition(body_canon->GetPosition().x, body_canon->GetPosition().y);
	shape_canon->setRotation(body_canon->GetAngle() * 180 / 3.14f);

	for (int i = 0; i < currentRagdoll; i++) {
		bulletRagdool[i]->UpdatePositions();
	}
}

//Gira el canon
void Canon::TurnCanon(bool right) {
	if(right){
		body_canon->SetTransform(body_canon->GetPosition(), body_canon->GetAngle() + degToRad(degreeRotation));
	} else {
		body_canon->SetTransform(body_canon->GetPosition(), body_canon->GetAngle() - degToRad(degreeRotation));
	}
	
}

//Gira el canon siguiendo el mouse
void Canon::TurnCanonWithMouse(Vector2f mouse_coords) {
	body_canon->SetTransform(body_canon->GetPosition(), atan2f(mouse_coords.y - body_canon->GetPosition().y, mouse_coords.x - body_canon->GetPosition().x));
}

//Pasar grados a radianes
float Canon::degToRad(float degree) {
	float rad = degree * 3.14f / 180;
	return rad;
}

//Disparar (instanciar) un ragdoll en la punta del canon
void Canon::ShootRagdoll() {
	if (currentRagdoll < 6) {
		bulletRagdool[currentRagdoll] = new Ragdoll(world, wnd, b2Vec2(body_canon->GetPosition().x + sizeCanon.x * 2 + 1.f, body_canon->GetPosition().y - sizeCanon.x * 2));
		bulletRagdool[currentRagdoll]->ApplyForce(shootForce, body_canon->GetAngle());
		currentRagdoll++;
		shooterSound.play();
	}
	else {
		emptySound.play();
	}
}

//Dispara un ragdoll desde la punta del canon utilizando la posicion del mouse como vector de fuerza
void Canon::ShootRagdollWithMouse(Vector2f mouse_position){
	if (currentRagdoll < 6) {
		bulletRagdool[currentRagdoll] = new Ragdoll(world, wnd, b2Vec2(body_canon->GetPosition().x + sizeCanon.x * 2 + 1.f, body_canon->GetPosition().y - sizeCanon.x * 2));
		bulletRagdool[currentRagdoll]->ApplyForce(Vector2f(mouse_position.x - body_canon->GetPosition().x, mouse_position.y - body_canon->GetPosition().y), shootForce,body_canon->GetAngle());
		currentRagdoll++;
		shooterSound.play();
	}
	else {
		emptySound.play();
	}
}