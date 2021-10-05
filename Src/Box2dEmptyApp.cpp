#include "Game.h"
#include <tchar.h>
#include <iostream>
#include "../Build/GUI.h"
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include "Game.h"

using namespace sf;

int main(int argc, char* argv[]) {
	Game* game = new Game();
	GUI* menu = new GUI();
	int opc = 0;
	RenderWindow* window = new RenderWindow(VideoMode(800, 600), "TPF");
	do {
		opc = menu->mainMenu(window);
		switch (opc) {
		case 0: {
			game->StartGame(window);
		}break;
		case 1: {

		}break;
		}
	} while (opc != 1);

	return 0;
}