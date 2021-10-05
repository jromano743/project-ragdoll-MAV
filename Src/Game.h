#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFMLRenderer.h"
#include <list>
#include "../Build/Ragdoll.h"
#include "../Build/Canon.h"
#include "../Build/CollisionProcessor.h"
#include "../Build/Obstacle.h"
#include "../Build/Pendulum.h"
#include "../Build/WinObject.h"

using namespace sf;

class Game
{
private:
	// Propiedades de la ventana
	int alto;
	int ancho;
	RenderWindow *wnd;
	Color clearColor;

	// Objetos de box2d
	b2World *phyWorld;
	SFMLRenderer *debugRender;

	//SFML
	RectangleShape* walls[3];
	Texture texture_cursor;
	Sprite sprite_cursor;
	CollisionProcessor* collisionProcessor;

	//tiempo de frame
	float frameTime;
	int fps;

	// Cuerpo de box2d
	b2Body* controlBody;

	//Canon
	Canon* canon;

	//Ragdolls
	Ragdoll* rag;

	//Simple box
	Obstacle* box;

	//Pendulum
	Pendulum* pendulum;

	//WinObject
	WinObject* winObject;

public:

	// Constructores, destructores e inicializadores
	Game();
	void CheckCollitions();
	void CreateEnemy(int x, int y);
	~Game(void);
	void InitPhysics(); //Crea el suelo

	// Main game loop
	void Loop();
	void StartGame(RenderWindow* _wnd);
	void DrawGame();
	void UpdatePhysics();
	void DoEvents();
	void SetZoom();
};

