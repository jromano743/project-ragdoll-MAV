#include "Game.h"
#include <tchar.h>
#include <iostream>
#include "../Build/GUI.h"
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include "Game.h"
#define LEVELS 2
using namespace sf;

int main(int argc, char* argv[]) {
	Game* game;
	GUI* menu = new GUI();
	int opc = 0;
	int level = 1;
	RenderWindow* window = new RenderWindow(VideoMode(800, 600), "TPF");
	opc = menu->mainMenu(window);
	do {
		switch (opc) {
		case 0:
			game = new Game();
			level = game->StartGame(window, level);
			delete game;
			printf("Current level %d", level);
			if (level > -1) {
				menu->winMenu(window, true);
			}
			else 
			{
				menu->winMenu(window, false);
				opc = 1;
				level = 1;
			}
			break;
		case 1:
			opc = menu->mainMenu(window);
			break;
		default:
			opc = -1;
			break;
		}
	} while (opc != -1);

	return 0;
}