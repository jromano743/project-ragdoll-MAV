#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "SFMLRenderer.h"
#include <list>
#include "../Build/Ragdoll.h"
#include "../Build/Canon.h"
#include "../Build/CollisionProcessor.h"
#include "../Build/Obstacle.h"
#include "../Build/PhysicsObstacle.h"
#include "../Build/Pendulum.h"
#include "../Build/WinObject.h"
#define MAX_LEVELS 2
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

	//Music
	SoundBuffer musicBuffer;
	Sound music;

	//SFML
	RectangleShape* walls[3];
	Texture texture_cursor;
	Sprite sprite_cursor;
	CollisionProcessor* collisionProcessor;

	//tiempo de frame
	float frameTime;
	int fps;

	//Nivel del juego
	int levelGame;
	bool exit;

	// Cuerpo de box2d
	b2Body* controlBody;

	//Canon
	Canon* canon;

	//Ragdolls
	//Ragdoll* rag;

	//Simple box
	Obstacle* box[3];

	//Physics Box
	PhysicsObstacle* pyBox[3];

	//Pendulum
	Pendulum* pendulum[3];

	//WinObject
	WinObject* winObject;

	void CheckCollitions();
	void InitPhysics(); //Crea el suelo
	void InitLevels(int level);
	void Loop();
	void DrawGame();
	void UpdatePhysics();
	void DoEvents();
	void SetZoom(bool isGame);
public:

	// Constructores, destructores e inicializadores
	Game();
	~Game(void);

	// Main game loop
	int StartGame(RenderWindow* _wnd, int _level);
};

