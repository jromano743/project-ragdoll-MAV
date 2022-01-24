#include "Game.h"
#include "Box2DHelper.h"

Game::Game()
{
	fps = 60;
	frameTime = 1.0f / fps;
	texture_cursor.loadFromFile("../Build/res/images/cursor-pointer.png");
	sprite_cursor.setTexture(texture_cursor);
	sprite_cursor.setPosition(50, 50);

	musicBuffer.loadFromFile("../Build/res/audio/game.wav");
	music.setBuffer(musicBuffer);
	walls[0] = new RectangleShape;
	walls[1] = new RectangleShape;
	walls[2] = new RectangleShape;
	InitPhysics();
}

int Game::StartGame(RenderWindow* _wnd, int _level) {
	//Setup
	wnd = _wnd;
	levelGame = _level;
	wnd->setVisible(true);
	SetZoom(true);
	wnd->setFramerateLimit(fps);
	InitLevels(levelGame);
	music.setLoop(true);
	music.play();
	Loop();
	SetZoom(false);

	return levelGame <= MAX_LEVELS ? levelGame : -1;
}

void Game::InitLevels(int level) {

	for (int i = 0; i < 3; i++)
	{
		box[i] = NULL;
		pendulum[i] = NULL;
	}
	switch (level)
	{
		case 1:
			rag = new Ragdoll(phyWorld, wnd);
			//Canon
			canon = new Canon(phyWorld, wnd);

			//Objetos de nivel
			box[0] = new Obstacle(phyWorld, wnd, b2Vec2(70.f, 50.f));
			pendulum[0] = new Pendulum(phyWorld, wnd, b2Vec2(50.f, 10.f));
			winObject = new WinObject(phyWorld, wnd, b2Vec2(75.f, 10.f));
			break;
		case 2:
			rag = new Ragdoll(phyWorld, wnd);
			//Canon
			canon = new Canon(phyWorld, wnd);

			//Objetos de nivel
			box[0] = new Obstacle(phyWorld, wnd, b2Vec2(90.f, 50.f));
			box[1] = new Obstacle(phyWorld, wnd, b2Vec2(70.f, 50.f));
			pendulum[0] = new Pendulum(phyWorld, wnd, b2Vec2(65.f, 10.f));
			pendulum[1] = new Pendulum(phyWorld, wnd, b2Vec2(45.f, 10.f));
			pendulum[2] = new Pendulum(phyWorld, wnd, b2Vec2(25.f, 10.f));
			winObject = new WinObject(phyWorld, wnd, b2Vec2(90.f, 30.f));
			break;
		default:
			break;
	}
	winObject->SetIsTouched(false);
}

void Game::Loop()
{
	while(wnd->isOpen() && !winObject->GetIsTouched())
	{
		wnd->clear(clearColor);
		DoEvents();
		CheckCollitions();
		UpdatePhysics();
		DrawGame();
		wnd->display();
	}

	if (winObject->GetIsTouched()) {
		levelGame++;
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

	box[0]->UpdatePosition();
	box[0]->Draw();

	if (box[1]) {
		box[1]->UpdatePosition();
		box[1]->Draw();
	}

	pendulum[0]->UpdatePosition();
	pendulum[0]->Draw();

	if (pendulum[1]) {
		pendulum[1]->UpdatePosition();
		pendulum[1]->Draw();
	}

	if (pendulum[2]) {
		pendulum[2]->UpdatePosition();
		pendulum[2]->Draw();
	}

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
				sprite_cursor.setPosition((float)evt.mouseMove.x, (float)evt.mouseMove.y);
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
void Game::SetZoom(bool isGame)
{
	View camara;
	Vector2f data = camara.getCenter();
	printf("%f    %f", data.x, data.y);
	// Posicion del view
	if (isGame) 
	{
		camara.setSize(100.0f, 100.0f);
		camara.setCenter(50.0f, 50.0f);
		wnd->setView(camara); //asignamos la camara
	}
	else 
	{
		wnd->setView(wnd->getDefaultView());
	}
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