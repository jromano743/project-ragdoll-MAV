#include "GUI.h"

GUI::GUI() {
	font.loadFromFile("../Build/res/fonts/ZEROHOUR.ttf");
	text1.setFont(font);
	textContinue.setFont(font);
	text2.setFont(font);
	textTilte.setFont(font);
	textWinGame.setFont(font);

	text1.setCharacterSize(24);
	textContinue.setCharacterSize(20);
	text2.setCharacterSize(24);
	textTilte.setCharacterSize(28);
	textWinGame.setCharacterSize(24);

	text1.setFillColor(sf::Color::Black);
	textContinue.setFillColor(sf::Color::Black);
	text2.setFillColor(sf::Color::Black);
	textTilte.setFillColor(sf::Color::Black);
	textWinGame.setFillColor(sf::Color::Black);

	text1.setStyle(sf::Text::Bold);
	textContinue.setStyle(sf::Text::Bold);
	text2.setStyle(sf::Text::Bold);
	textTilte.setStyle(sf::Text::Bold);
	textWinGame.setStyle(sf::Text::Bold);

	text1.setString("Play");
	text2.setString("Exit");
	textTilte.setString("Ragdoll Canon");
	textContinue.setString("Next Level");
	textWinGame.setString("Level Completed");

	texture.loadFromFile("../Build/res/images/button.png");
	button1.setTexture(texture);
	button2.setTexture(texture);
	buttonContinue.setTexture(texture);

	//Posiciones de los botones
	button1.setPosition(25, 200);
	button2.setPosition(25, 300);
	buttonContinue.setPosition(25, 200);

	text1.setPosition(75, 240);
	textContinue.setPosition(30, 240);
	text2.setPosition(75, 340);
	textTilte.setPosition(25, 50);
	textWinGame.setPosition(25, 50);


	cursorTexture.loadFromFile("../Build/res/images/cursor.png");
	cursorSprite.setTexture(cursorTexture);
	cursorSprite.setPosition(400, 300);

	background.loadFromFile("../Build/res/images/mainScreen.png");
	bg.setTexture(background);

	background.loadFromFile("../Build/res/images/winScreen.png");
	winBg.setTexture(background);

	selectSoundBuffer.loadFromFile("../Build/res/audio/click.wav");
	selectSound.setBuffer(selectSoundBuffer);

	songBuffer.loadFromFile("../Build/res/audio/menu.wav");
	musicSong.setBuffer(songBuffer);

	winMenuBuffer.loadFromFile("../Build/res/audio/menu.wav");
	winSong.setBuffer(songBuffer);
}

int GUI::mainMenu(RenderWindow* w) {
	//w->setMouseCursorVisible(false);
	musicSong.setLoop(true);
	musicSong.play();
	while (w->isOpen()) {
		Event e;
		//Control de eventos
		while (w->pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed: {
				musicSong.stop();
				w->close();
			}break;
			case sf::Event::MouseMoved: {
				cursorSprite.setPosition((float)e.mouseMove.x, (float)e.mouseMove.y);
			}break;
			case sf::Event::MouseButtonPressed: {
				if (button1.getGlobalBounds().intersects(cursorSprite.getGlobalBounds())) {
					selectSound.play();
					musicSong.stop();
					return(0);
				}
				if (button2.getGlobalBounds().intersects(cursorSprite.getGlobalBounds())) {
					selectSound.play();
					musicSong.stop();
					return(-1);
				}
			}break;
			}

		}
		w->clear();
		w->draw(bg);
		w->draw(button1);
		w->draw(text1);
		w->draw(button2);
		w->draw(text2);
		w->draw(textTilte);
		//w->draw(cursorSprite);
		w->display();
	}
	w->clear();
}

void GUI::winMenu(RenderWindow* w, bool haveNextLevel) {
	//w->setMouseCursorVisible(false);
	musicSong.setLoop(true);
	musicSong.play();
	if (!haveNextLevel) {
		textContinue.setString("Back to menu");
	}
	while (w->isOpen()) {
		Event e;
		//Control de eventos
		while (w->pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed: {
				musicSong.stop();
				w->close();
			}break;
			case sf::Event::MouseMoved: {
				cursorSprite.setPosition((float)e.mouseMove.x, (float)e.mouseMove.y);
			}break;
			case sf::Event::MouseButtonPressed: {
				if (button1.getGlobalBounds().intersects(cursorSprite.getGlobalBounds())) {
					selectSound.play();
					musicSong.stop();
					return;
				}
			}break;
			}

		}
		//Dibujado
		w->clear();
		w->draw(winBg);
		w->draw(buttonContinue);
		w->draw(textContinue);
		w->draw(textWinGame);
		//w->draw(cursorSprite);
		w->display();
		
	}
	w->clear();
}

GUI::~GUI() {

}