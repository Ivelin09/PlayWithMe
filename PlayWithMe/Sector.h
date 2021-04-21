#pragma once
#include<iostream>
#include "Window.h"

#include "DragGame.h"
#include<vector>

#include "Images.h"
#include "Stars.h"

#include<fstream>
#include "Game.h"

#include<ios>

class Sector : public Window {
private:
	std::vector<Image> game;
	const std::vector<Window*> link;

	const int starSize = 3;

	std::vector<std::vector<Stars>> stars;
	int games = 0;

	std::string secName;
public:
	std::vector<Image>& getNav() {
		return this->game;
	}

	std::vector<std::vector<Stars>>& getStars() {
		return this->stars;
	}

	std::string getName() const {
		return this->secName;
	}

	Sector(sf::RenderWindow& window, const std::vector<Window*> link,
		std::vector<Image> game, std::vector<std::pair<Image, Window*>> nav, const std::string secName) : Window(window, "MiddleScreen.png", nav), game(game),
		stars(link.size(), std::vector<Stars>(starSize)), secName(secName), link(link) {

		// NAVIGATION

		this->nav[Home].first.getShape().setPosition({ 0,0 });
		this->nav.erase(this->nav.begin() + 1, this->nav.end());

		// ====

		const float widthButton = width / link.size() - width / 7;
		const float heightButton = height - height / 7;

		for (auto& k : this->game) {
			k.getShape().setSize(sf::Vector2f(widthButton, heightButton - 80));
		}

		setSymetric(this->game, 0, width, widthButton, height / 15);

		this->game[0].setTexture("game1.png");
		this->game[1].setTexture("game2.png");
		this->game[2].setTexture("game3.png");

		const float sizeX = this->game[0].getShape().getSize().x / 6;
		const float sizeY = this->game[0].getShape().getPosition().y + this->game[0].getShape().getSize().y;

		for (auto& k : this->stars)
		{
			k.resize(3);
			for (auto& q : k)
			{
				q.getShape().setSize(sf::Vector2f((width + height) / 25, (width + height) / 25));
				q.getShape().setTexture(&Singleton::get().unfilledStar.getTexture());
			}
		}
		//std::cout << this->game[0].getShape().getPosition().x << std::endl;
		int row = 0;

		for (int i = 0; i < stars.size(); i++) {
			setSymetric(stars[i], this->game[i].getShape().getPosition().x,
				this->game[i].getShape().getPosition().x + this->game[i].getShape().getSize().x,
				stars[i][0].getShape().getSize().x,
				this->game[i].getShape().getPosition().y + this->game[i].getShape().getSize().y);
		}

		bool start = false; 
		int gameLevel = 0;

	}
	Window* start() override
	{
		for (int i = 0; i < Singleton::table.getSector(this->secName).size(); i++) {
			for (int j = 0; j < Singleton::table.getSector(this->secName)[i]; j++) {
				this->stars[i][j].activate();
			}
		}

		while (window.isOpen())

		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				else if (event.type == sf::Event::MouseButtonPressed)
				{
					const sf::Vector2f mouseCords = window.mapPixelToCoords(sf::Mouse::getPosition(window));

					for (int i = 0; i < this->game.size(); i++)
					{
						sf::Vector2f size = this->game[i].getShape().getSize();
						sf::Vector2f position = this->game[i].getShape().getPosition();

						if (mouseCords.x >= position.x && mouseCords.x <= position.x + size.x &&
							mouseCords.y >= position.y && mouseCords.y <= position.y + size.y)
							return link[i];
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

			window.draw(this->background);

			for (auto& k : nav)
				window.draw(k.first.getShape());

			for (auto& k : this->game)
				window.draw(k.getShape());

			for (auto& k : this->stars)
				for (auto& q : k)
					window.draw(q.getShape());

			window.display();
		}
		return nullptr;
	}

	void levelUp() {
		return;
	}
};

