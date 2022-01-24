#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
class GUI
{
private:
	Texture texture, cursorTexture, background;
	Sprite button1, button2, buttonContinue, cursorSprite, bg, winBg;
	SoundBuffer selectSoundBuffer, songBuffer, winMenuBuffer;
	Sound selectSound, musicSong, winSong;
	Font font;
	Text text1, text2, textTilte, textContinue, textWinGame;

public:
	GUI();
	int mainMenu(RenderWindow* w);
	void winMenu(RenderWindow* w, bool haveNextLevel);
	~GUI();
};