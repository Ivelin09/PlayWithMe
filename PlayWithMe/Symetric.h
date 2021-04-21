#pragma once

#include<vector>

#include<fstream>
#include "Stars.h"

#include "Window.h"

template<typename A>
void setSymetric(std::vector<A>& buttons, const int startWidth,
	const int width, const double x, const double y)
{
	double substractedWidth = width - startWidth - (x * buttons.size());
	double deltaWidth = substractedWidth / (buttons.size() * 2);

	double currPos = startWidth;

	for (auto& k : buttons)
	{
		currPos += deltaWidth;

		k.getShape().setPosition(currPos, y);
		currPos += x + deltaWidth;
	}
}

inline void setSymetric(std::vector<Image*>& buttons, const int startWidth,
	const int width, const double x, const double y)
{
	double substractedWidth = width - startWidth - (x * buttons.size());
	double deltaWidth = substractedWidth / (buttons.size() * 2);

	double currPos = startWidth;

	for (auto& k : buttons)
	{
		currPos += deltaWidth;

		k->getShape().setPosition(currPos, y);
		currPos += x + deltaWidth;
	}
}

/* void setSymetric(std::vector<sf::Vector2i>& buttons, const int startWidth,
	const int width, const double x, const double y)
{
	double substractedWidth = width - startWidth - (x * buttons.size());
	double deltaWidth = substractedWidth / (buttons.size() * 2);

	double currPos = startWidth;

	for (auto& k : buttons)
	{
		currPos += deltaWidth;

		k = { currPos, y };
		currPos += x + deltaWidth;
	}
} */

/* std::vector<Image>::iterator onObject(std::vector<Image>& dropPic, std::vector<Image>& dragPic,
	bool& hold, sf::Vector2f back, std::vector<Image>::iterator& saveIt, sf::Vector2f oldPos,
	const sf::RenderWindow& window) {
	const sf::Vector2f mouseCords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	auto it1 = dropPic.begin();

	std::vector<Image>::iterator movingObj = dragPic.end();

	for (auto it = dragPic.begin(); it != dragPic.cend(); ++it, ++it1) {
		sf::Vector2f size = it->getShape().getSize();
		sf::Vector2f position = it->getShape().getPosition();

		if (mouseCords.x >= position.x && mouseCords.x <= position.x + size.x &&
			mouseCords.y >= position.y && mouseCords.y <= position.y + size.y) {

			std::cout << "NEW SAVE\n";
			saveIt = it1;
			movingObj = it;

			back = movingObj->getShape().getPosition();
			hold = true;
		}
		oldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	}

	return movingObj;
}

void moveObj(const sf::RenderWindow& window, std::vector<Image>::iterator& movingObj, const sf::Vector2f oldPos) {
	const sf::Vector2f mouseCords = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	const double newCordsX = movingObj->getShape().getPosition().x - oldPos.x + mouseCords.x;
	const double newCordsY = movingObj->getShape().getPosition().y - oldPos.y + mouseCords.y;

	movingObj->getShape().setPosition(newCordsX, newCordsY);
} */