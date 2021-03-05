#pragma once

#include <iostream>

#include "Window.h"
#include "Symetric.h"

#include "DragGame.h"
#include<cstdlib>
#include<ctime>

#include <chrono>
#include "Graph.h"

class FallingFigures : public Window
{
public:
	FallingFigures(sf::RenderWindow& window, std::vector<Image>& objects,
		const std::string& background) : Window(window, background) {

		for (int i = 0; i < objects.size(); i++)
			this->objects.emplace_back(objects[i], i);

		defaultObjects = this->objects;
		this->positions.resize(this->objects.size());

		for (int i = 0; i < this->objects.size(); i++) {
			positions[i].setSize(this->objects[i].first.getShape().getSize());
			positions[i].randomize();
		}

		//this->dropPic.push_back(Singleton::get().square);
		//this->dropPic.back().getShape().setPosition(60, 60);
	}

	Window* start() override {
		while (window.isOpen()) {
			sf::Event e;
			while (window.pollEvent(e)) {
				if (e.type == sf::Event::Closed) {
					window.close();
				}
				else if (e.type == sf::Event::MouseButtonPressed) {
					const sf::Vector2f mouseCords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
					for (int i = 0; i < objects.size(); i++) {
						sf::Vector2f size = objects[i].first.getShape().getSize();
						sf::Vector2f position = objects[i].first.getShape().getPosition();

						if (mouseCords.x >= position.x && mouseCords.x <= position.x + size.x &&
							mouseCords.y >= position.y && mouseCords.y <= position.y + size.y) {
							if (currObj.second == this->objects[i].second) {
								if (++correct == generated) {
									Start = true;
								}
								objects[i].first.getShape().setSize(sf::Vector2f(0, 0));
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
							return nav[i].second;
						}
					}
				}
			}

			window.clear();
			uptade();

			if (isSound) {
				std::cout << "PLAYING\n";
				currObj.first.play();
				isSound = false;
			}
			
			for (auto& k : nav)
				window.draw(k.first.getShape());

			window.display();
		}
		return nullptr;
	}

private:
	bool Start = true;

	std::vector<Graph> positions;
	std::vector<std::pair<Image, int>> objects;

	std::vector<std::pair<Image, int>> defaultObjects;

	std::pair<Image, int> currObj;

	int correct = 0, generated = 0;

	sf::RectangleShape box;
	bool isSound = false;

	sf::Text text;
	sf::Font font;
	void uptade() {
		using namespace std::chrono_literals;
		generated = 0;

		window.draw(background);

		int sum = 0;
		int time = 2;

		for (int i = 0; i < positions.size(); i++) {
			const sf::Vector2f pos = this->objects.at(i).first.getShape().getPosition();
			const sf::Vector2f size = this->objects.at(i).first.getShape().getSize();

			for (int j = 0; j < positions.size(); j++) {
				const sf::Vector2f pos = positions[i].getPos();
				const sf::Vector2f pos1 = positions[j].getPos();
				
			}

			if (pos.y >= height) {
				sum++;
			}

			positions.at(i).uptade();
			this->objects.at(i).first.getShape().setPosition(positions.at(i).getPos());

			window.draw(objects.at(i).first.getShape());
		}

		if (Start || sum == positions.size()) {
			const int totalObjects = 3;
			Start = false;

			objects.clear();
			positions.clear();

			objects.resize(totalObjects);
			positions.resize(totalObjects);

			int randObject = rand() % objects.size();

			for (int i = 0; i < totalObjects; i++) {
				int index = rand() % defaultObjects.size();
				if (index == randObject)
					generated++;

				objects[i] = defaultObjects[index];
			}

			currObj = objects[randObject];
			isSound = true;

			for (int i = 0; i < this->objects.size(); i++) {
				positions[i].setSize(this->objects[i].first.getShape().getSize());
				positions[i].randomize();
			}

			for (auto& k : positions) {
				k.randomize();
			}

		}

	}
};
