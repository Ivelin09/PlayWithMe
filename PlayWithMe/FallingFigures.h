#pragma once

#include <iostream>

#include "Window.h"
#include "Symetric.h"

#include "DragGame.h"
#include<cstdlib>
#include<ctime>

#include <chrono>
#include "Graph.h"

#include "Stars.h"
#include<fstream>

#include "Singleton.h"


class FallingFigures : public Window
{
private:

	std::vector<Stars>* stars;
	bool Start = true;

	std::vector<Graph> positions;
	std::vector<Image> objects;

	std::vector<Image> defaultObjects;

	int starLevel = 1;

	Image currObj;
	float frames = 2;

	int correct = 0, generated = 0, strike = 0;
	int startFrameRate = 90;

	const int maxObj = 4;
	int currObjects = 2;

	sf::RectangleShape box;
	bool isSound = false;

	std::string gameName = "FallingGame";
	std::string secName;
	void uptade() {
		using namespace std::chrono_literals;

		window.draw(background);

		int sum = 0;
		int time = 2;

		for (int i = 0; i < positions.size(); i++) {
			const sf::Vector2f pos = this->objects.at(i).getShape().getPosition();
			const sf::Vector2f size = this->objects.at(i).getShape().getSize();

			if (pos.y >= height) {
				sum++;
			}

			positions.at(i).uptade(frames);
			this->objects.at(i).getShape().setPosition(positions.at(i).getPos());

			window.draw(objects.at(i).getShape());
		}

		if (Start || sum == positions.size()) {
			if (Start == false && correct == generated && currObjects != maxObj) {
				currObjects++;
			}
			else if (currObjects == maxObj && frames > 1.05) {
				starLevel = 1;
				frames -= 0.1;

				strike++;
				if (strike > 3)
					starLevel = 2;
				else if (strike > 6)
					starLevel = 3;
			}

			if (correct != generated) {
				strike = 0;
			}

			generated = 1;
			Start = false;

			correct = 0;

			objects.clear();
			positions.clear();

			objects.resize(currObjects);
			positions.resize(currObjects);

			int randObject = rand() % objects.size();

			for (int i = 0; i < currObjects; i++) {
				int index = rand() % defaultObjects.size();
				if (index == randObject)
					generated++;

				objects.at(i).getShape().setTexture(defaultObjects[index].getShape().getTexture());
				objects.at(i).setSound(defaultObjects[index].getSound());

				objects.at(i).getShape().setSize(defaultObjects[index].getShape().getSize());
				objects.at(i).getShape().setPosition(defaultObjects[index].getShape().getPosition());

				objects[i].pathImage = defaultObjects[index].pathImage;
				objects[i].pathSound = defaultObjects[index].pathSound;
			}

			currObj = objects[randObject];
			isSound = true;

			for (int i = 0; i < this->objects.size(); i++) {
				positions[i].setSize(this->objects[i].getShape().getSize());
				positions[i].randomize();
			}

			for (auto& k : positions) {
				k.randomize();
			}
			//setSymetric(objects, 0, width, objects[0].getShape().getSize().x, objects[0].getShape().getSize().y);
		}

	}

public:
	FallingFigures(sf::RenderWindow& window, std::vector<Image>& objects,
		const std::string& background, std::vector<std::pair<Image, Window*>> nav) : Window(window, background, nav), defaultObjects(objects) {
		
		// NAVIGATION

		this->nav.erase(this->nav.begin() + 1, this->nav.end());
		this->nav[Home].first.getShape().setPosition({ 0,0 });

		// =========

		this->positions.resize(this->objects.size());

		for (int i = 0; i < this->objects.size(); i++) {
			positions[i].setSize(this->objects[i].getShape().getSize());
			positions[i].randomize();
		}
	}

	void linkUp(std::vector<Stars>& star, std::string secName) {
		this->secName = secName;
		this->stars = &star;
	}

	Window* start() override {
		window.setFramerateLimit(120);
		while (window.isOpen()) {
			sf::Event e;
			while (window.pollEvent(e)) {
				if (e.type == sf::Event::Closed) {
					window.close();
				}
				else if (e.type == sf::Event::MouseButtonPressed) {
					const sf::Vector2f mouseCords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
					for (int i = 0; i < objects.size(); i++) {
						sf::Vector2f size = objects[i].getShape().getSize();
						sf::Vector2f position = objects[i].getShape().getPosition();

						if (mouseCords.x >= position.x && mouseCords.x <= position.x + size.x &&
							mouseCords.y >= position.y && mouseCords.y <= position.y + size.y) {
							if (currObj == this->objects[i]) {
								correct++;
								objects[i].getShape().setSize(sf::Vector2f(0, 0));
							}
							else {
								Singleton::get().incorrect.play();
							}
						}
					}

					for (int i = 0; i < nav.size(); i++)
					{
						sf::Vector2f size = nav[i].first.getShape().getSize();
						sf::Vector2f position = nav[i].first.getShape().getPosition();

						if (mouseCords.x >= position.x && mouseCords.x <= position.x + size.x &&
							mouseCords.y >= position.y && mouseCords.y <= position.y + size.y) {
							Singleton::table.levelUp(this->secName, GAME_TYPE::FALLINGGAME, strike);
							return nav[i].second;
						}
					}
				}
			}

			window.clear();
			
			uptade();

			if (isSound) {
				std::cout << "PLAYING\n";
				currObj.play();
				isSound = false;
			}

			for (auto& k : nav)
				window.draw(k.first.getShape());

			window.display();
		}


		return nullptr;
	}
};