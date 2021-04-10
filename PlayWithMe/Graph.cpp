#include "Graph.h"
#include "Symetric.h"

#include<iostream>

int Graph::randomSeed;

Graph::Graph() {
	srand(time(NULL));
	randomSeed = rand() % 100;
}

void Graph::randomize() {
	srand(randomSeed);

	if (randomSeed == 0) {
		randomSeed = rand() % 100;
	}

	randomSeed *= 2;

	gravityY = 2.5; 
	gravityX = rand() % 3 + 1;

	power = gravityY + ((rand() % 3) + 6);
	
	std::cout << gravityX << ' ' << gravityY << ' ' << power << std::endl;

	const float positionX = rand() % (int)(width - size.x) + size.x;
	const float positionY = height;

	if (positionX < width / 2) {
		gravityX *= -1;
	}

	position = sf::Vector2f(positionX, positionY);
}

void Graph::setSize(const sf::Vector2f& size) {
	this->size = size;
}

Graph::Graph(sf::Vector2f size) : size(size) {
	randomize();

	srand(time(NULL));

	randomSeed = rand() % 100;
}

const sf::Vector2f Graph::getPos() const {
	return position;
}

void Graph::uptade(double speed) {
	position.y -= power / speed;

	gravityY *= 1 + (0.01 / speed);
	position.y += gravityY / speed;


	position.x -= gravityX / speed;
}