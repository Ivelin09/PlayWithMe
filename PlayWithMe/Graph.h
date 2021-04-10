#pragma once

#include<SFML/Graphics.hpp>

extern const double width;
extern const double height;

struct Graph {
	float gravityY = 0, gravityX = 0, power = 0;
	static int randomSeed;

	sf::Vector2f velocity;

	sf::Vector2f position;
	sf::Vector2f size;

	Graph();

	Graph(sf::Vector2f size);

	const sf::Vector2f getPos() const;

	void uptade(double speed);

	void setSize(const sf::Vector2f& size);

	void randomize();
};