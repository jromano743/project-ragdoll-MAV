#include "GUI.h"

GUI::GUI() {
	font.loadFromFile("../Build/res/fonts/ZEROHOUR.ttf");
	text1.setFont(font);
	text2.setFont(font);
	textTilte.setFont(font);

	text1.setCharacterSize(24);
	text2.setCharacterSize(24);
	textTilte.setCharacterSize(24);

	text1.setFillColor(sf::Color::Black);
	text2.setFillColor(sf::Color::Black);
	textTilte.setFillColor(sf::Color::Black);

	text1.setStyle(sf::Text::Bold);
	text2.setStyle(sf::Text::Bold);
	textTilte.setStyle(sf::Text::Bold);

	text1.setString("Play");
	text2.setString("Exit");
	textTilte.setString("Wild Gang");

	texture.loadFromFile("../Build/res/images/button.png");
	button1.setTexture(texture);
	button2.setTexture(texture);

	//Posiciones de los botones
	button1.setPosition(300, 250);
	button2.setPosition(300, 350);

	text1.setPosition(350, 280);
	text2.setPosition(350, 380);
	textTilte.setPosition(300, 75);


	cursorTexture.loadFromFile("../Build/res/images/cursor.png");
	cursorSprite.setTexture(cursorTexture);
	cursorSprite.setPosition(400, 300);

	background.loadFromFile("../Build/res/images/mainScreen.png");
	bg.setTexture(background);

	selectSoundBuffer.loadFromFile("../Build/res/audio/GunShot.wav");
	selectSound.setBuffer(selectSoundBuffer);

	songBuffer.loadFromFile("../Build/res/audio/mainMenuSong.wav");
	musicSong.setBuffer(songBuffer);
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
					return(1);
				}
			}break;
			}

		}
		//Dibujado
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

GUI::~GUI() {

}