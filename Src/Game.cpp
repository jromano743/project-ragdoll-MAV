#include "Game.h"
#include "Box2DHelper.h"

Game::Game()
{
	fps = 60;
	frameTime = 1.0f / fps;
	texture_cursor.loadFromFile("../Build/res/images/cursor-pointer.png");
	sprite_cursor.setTexture(texture_cursor);
	sprite_cursor.setPosition(50, 50);
	walls[0] = new RectangleShape;
	walls[1] = new RectangleShape;
	walls[2] = new RectangleShape;
	InitPhysics();
}

void Game::StartGame(RenderWindow* _wnd) {
	//Setup
	wnd = _wnd;
	wnd->setVisible(true);
	SetZoom();
	wnd->setFramerateLimit(fps);

	//Objects
	rag = new Ragdoll(phyWorld, wnd);
	canon = new Canon(phyWorld, wnd);

	//Objetos de nivel
	//box = new Obstacle(phyWorld, wnd, b2Vec2(50.f, 50.f));
	//pendulum = new Pendulum(phyWorld, wnd, b2Vec2(50.f, 10.f));
	winObject = new WinObject(phyWorld, wnd, b2Vec2(75.f, 10.f));
	printf("EL ID DEL WIN OBJECT PRINCIPAL ES: %d", winObject->GetId());
	Loop();
}

void Game::Loop()
{
	while(wnd->isOpen())
	{
		wnd->clear(clearColor);
		DoEvents();
		CheckCollitions();
		UpdatePhysics();
		DrawGame();
		wnd->display();
	}
}

void Game::UpdatePhysics()
{
	phyWorld->Step(frameTime, 8, 8);
	//phyWorld->ClearForces();
	//phyWorld->DebugDraw();
}

void Game::DrawGame()
{ 
	//Dibujado del ragdoll
	rag->UpdatePositions();
	rag->Draw();

	//Dibujado del canon
	canon->UpdatePosition();
	canon->Draw();

	//Paredes
	wnd->draw(*walls[0]);
	wnd->draw(*walls[1]);
	wnd->draw(*walls[2]);

	//box->UpdatePosition();
	//box->Draw();

	//pendulum->UpdatePosition();
	//pendulum->Draw();

	//Win object
	winObject->UpdatePosition();
	winObject->Draw();
}

void Game::DoEvents()
{
	Event evt;
	while(wnd->pollEvent(evt))
	{
		switch(evt.type)
		{
			case Event::Closed:
				wnd->close();
				break;
			case Event::KeyPressed:
				if (Keyboard::isKeyPressed(Keyboard::Right)) {
					canon->TurnCanon(true);
				}
				if (Keyboard::isKeyPressed(Keyboard::Left)) {
					canon->TurnCanon(false);
				}
				if (Keyboard::isKeyPressed(Keyboard::Space)) {
					canon->ShootRagdoll();
				}
				break;
			case sf::Event::MouseMoved:
				//sprite_cursor.setPosition((float)evt.mouseMove.x, (float)evt.mouseMove.y);
				break;
			case Event::MouseButtonPressed:
				Vector2i mouse_position = Mouse::getPosition(*wnd);
				Vector2f mouse_coords = wnd->mapPixelToCoords(mouse_position);
				canon->TurnCanonWithMouse(mouse_coords);
				canon->ShootRagdollWithMouse(mouse_coords);
				break;
		}
	}
}

void Game::CheckCollitions()
{
	// Veremos mas adelante
}

// Definimos el area del mundo que veremos en nuestro juego
// Box2D tiene problemas para simular magnitudes muy grandes
void Game::SetZoom()
{
	View camara;
	// Posicion del view
	camara.setSize(100.0f, 100.0f);
	camara.setCenter(50.0f, 50.0f);
	wnd->setView(camara); //asignamos la camara
}

void Game::InitPhysics()
{
	// Inicializamos el mundo con la gravedad por defecto
	phyWorld = new b2World(b2Vec2(0.0f, 9.8f));
	collisionProcessor = new CollisionProcessor();
	phyWorld->SetContactListener(collisionProcessor);

	//MyContactListener* l= new MyContactListener();
	//phyWorld->SetContactListener(l);
	

	// Creamos el renderer de debug y le seteamos las banderas para que dibuje TODO
	debugRender = new SFMLRenderer(wnd);
	debugRender->SetFlags(UINT_MAX);
	phyWorld->SetDebugDraw(debugRender);

	//***** Creamos un piso y paredes*****//
	b2Body* groundBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
	groundBody->SetTransform(b2Vec2(50.0f, 100.0f), 0.0f);

	walls[0]->setSize(Vector2f(100, 10));
	walls[0]->setOrigin(Vector2f(walls[0]->getSize().x / 2, walls[0]->getSize().y / 2));
	walls[0]->setPosition(Vector2f(groundBody->GetPosition().x, groundBody->GetPosition().y));
	walls[0]->setFillColor(Color::Green);

	b2Body* leftWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
	leftWallBody->SetTransform(b2Vec2(0.0f, 50.0f), 0.0f);

	walls[1]->setSize(Vector2f(5, 100));
	walls[1]->setOrigin(Vector2f(walls[1]->getSize().x / 2, walls[1]->getSize().y / 2));
	walls[1]->setPosition(Vector2f(leftWallBody->GetPosition().x, leftWallBody->GetPosition().y));
	walls[1]->setFillColor(Color::Green);

	b2Body* rightWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
	rightWallBody->SetTransform(b2Vec2(100.0f, 50.0f), 0.0f);

	walls[2]->setSize(Vector2f(5, 100));
	walls[2]->setOrigin(Vector2f(walls[2]->getSize().x / 2, walls[2]->getSize().y / 2));
	walls[2]->setPosition(Vector2f(rightWallBody->GetPosition().x, rightWallBody->GetPosition().y));
	walls[2]->setFillColor(Color::Green);
}


Game::~Game(void)
{ }