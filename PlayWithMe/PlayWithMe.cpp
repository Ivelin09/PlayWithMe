#include <iostream>
#include <SFML/Graphics.hpp>

#include "Window.h"

#include "Images.h"
#include "Stars.h"

#include "Images.h"
#include "DragGame.h"

#include<fstream>

#include<vector>
#include<utility>

#include<unordered_set>

const double width = 1200;
const double height = 800;

sf::RenderWindow window(sf::VideoMode((unsigned int)width, (unsigned int)height), "Play with me!");

#include "Singleton.h"

Singleton& obj = Singleton::get();


int main()
{
	window.setFramerateLimit(120);

	sf::Texture file;
	sf::Sprite bg;

	file.loadFromFile(ImagePath + "newBG.jpg");
	bg.setTexture(file);

	bg.setScale(width / file.getSize().x, height / file.getSize().y);
	std::string q = AudioPath + "gameAudio.wav";

	//Singleton::WINDOW_STATE curr;
	Window* next = nullptr;
	std::cout << Window::FILE;
	obj.gameAudio.openFromFile(q);

	bool musicOn = false;
	sf::RectangleShape* onHover = nullptr, * save = nullptr;

	sf::Vector2f saveSize = obj.digits[0].first.getSize();
	double shrink = 5;

	sf::Vector2f shrinkDownTo = obj.digits[0].first.getSize();
	sf::Vector2f shrinkUpTo = sf::Vector2f(obj.digits[0].first.getSize().x + 100,
		obj.digits[0].first.getSize().x + 100);

	sf::Texture texture;
	texture.loadFromFile("cursor.png");
	sf::Sprite sprite(texture);

	sprite.setScale(sf::Vector2f(0.2, 0.2));
	window.setMouseCursorVisible(false);
	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed)
				window.close();
			else if (e.type == sf::Event::MouseButtonPressed) {
				const sf::Vector2f mouseCords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
				for (int i = 0; i < obj.digits.size(); i++) {
					auto objCords = obj.digits[i].first.getPosition();
					auto objSize = obj.digits[i].first.getSize();

					if (mouseCords.x >= objCords.x && mouseCords.x <= objCords.x + objSize.x &&
						mouseCords.y >= objCords.y && mouseCords.y <= objCords.y + objSize.y) {
						window.setMouseCursorVisible(true);
						next = obj.digits[i].second->start();

						while (next) {
							next = next->start();
						}
						window.setMouseCursorVisible(false);
						break;
					}
				}
				const sf::Vector2f buttonLoc = obj.musicButton.getShape().getPosition();
				auto buttonSize = obj.musicButton.getShape().getSize();

				if (mouseCords.x >= buttonLoc.x && mouseCords.x <= buttonLoc.x + buttonSize.x &&
					mouseCords.y >= buttonLoc.y && mouseCords.y <= buttonLoc.y + buttonSize.y) {
					musicOn = !musicOn;
					if (musicOn)
						obj.gameAudio.play();
					else
						obj.gameAudio.stop();
				}
			}
		}

		sprite.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));

		window.clear();
		window.draw(bg);

		for (const auto& k : obj.digits)
			window.draw(k.first);

		window.draw(obj.playWithMe.getShape());
		window.draw(obj.musicButton.getShape());

		window.draw(sprite);

		window.display();
	}

	for (int i = 0; i < obj.digits.size(); i++)
		delete obj.digits[i].second;
}