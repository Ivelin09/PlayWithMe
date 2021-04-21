#pragma once
#include "SoundGame.h"

#include "Window.h"
#include<Candle/RadialLight.hpp>

#include "Game.h"
#include<functional>

#include "Symetric.h"
#include<unordered_set>

#include<SFML/Audio.hpp>

extern const double width, height;

class ColorSound : public SoundGame
{
private:
	std::vector<sf::Vector2i> positions;
	sf::Vector2i animationPlace;

	std::vector<std::vector<Image>> objects;
	std::function<void(void)> randElements = nullptr;

	std::string gameName = "Color";
public:
	Image* animateObj = nullptr;

	bool isOnCenter = false;
	sf::Vector2i center;

	int placeIndex = 0, objIndex = 0;
	bool flag = true;

	Image** images = nullptr;
	size_t randSize, currLevel = 0;

	bool showAnimation = true;

	// if level up progress = true
	bool progress = false;

	int nextLevel[4] = { 1,8,10 };

	ColorSound(sf::RenderWindow& window, std::vector<std::vector<Image>> combinations, const std::string& path, std::vector<std::pair<Image, Window*>> nav) :
		SoundGame(window, combinations, path, nav), objects(combinations), currLevel(Singleton::table.getInfo()["Colors"][0]) {

		// CHANGING LEVELS

		if (currLevel == 0) {
			randElements = std::bind(&ColorSound::randElementsLevel2, this);
		}

		// ===========

		Image& obj = combinations[0][0];

		const float objWidth = obj.getShape().getSize().x;
		const float objHeight = obj.getShape().getSize().y;

		center = { (int)(width / 2 - objWidth / 2), (int)(objHeight / 4) };

		for (auto& a : this->objects)
			for (auto& k : a)
				k.getShape().setPosition({ (float)center.x, (float)(-k.getShape().getSize().y) });

		// SYMETRIC MATH

		double substractedWidth = width - (objWidth * combinations.size());
		double deltaWidth = substractedWidth / (combinations.size() * 2);

		double currPos = 0;

		for (int i = 0; i < this->objects[0].size(); i++) {
			currPos += deltaWidth;

			// !
			positions.emplace_back(currPos, height / 2 - objHeight / 2);

			currPos += deltaWidth + objWidth;
		}
		// =========

		// RAND OBJECT
		objIndex = rand() % this->objects.size();
		animationPlace = positions[0];
	}

	void intro() override {
		return;
	}

	void correctAnswer() override {

		if (nextLevel[this->currLevel] == ++this->strike);
		return;
	}

	Window* start() override {

		this->copyElements();
		if (showAnimation) {
			animate(buttons);

			buttons.resize(randSize);

			for (int i = 0; i < randSize; i++) {
				buttons[i] = images[i];
			}
		}
		else {
			setSymetric(buttons, 0.0, width, buttons[0]->getShape().getSize().x,
				height / 2 - combinations[0].getShape().getSize().y / 2);
		}
		Window* STATE = SoundGame::start();
		if (STATE == nullptr) {
			showAnimation = true;
		}

		return STATE;
	}

	void copyElements() override {
		this->randElements();
		randSize = buttons.size();

		if (images)
			delete[] images;
		images = new Image * [buttons.size()];

		for (int i = 0; i < buttons.size(); i++) {
			images[i] = buttons[i];
		}

	}

	sf::Sound& incorrectAnswer() {

		this->strike = 0;

		int i = 0;
		sf::Vector2f defSize = images[0]->getShape().getSize();

		bool shrinkDown = false;
		long double currTime = 0;
		long double soundTime = 1;
		while (i != 3 && window.isOpen()) {
			sf::Event e;
			while (window.pollEvent(e)) {
				if (e.type == sf::Event::Closed) {
					window.close();
				}
			}

			if (!shrinkDown) {
				sf::Vector2f oldSize = images[i]->getShape().getSize();
				images[i]->getShape().setSize({ (float)(oldSize.x * 1.005),(float)(oldSize.y * 1.0 * 1.005) });

				sf::Vector2f newSize = images[i]->getShape().getSize();

				sf::Vector2f diffLoc = { newSize.x - oldSize.x, newSize.y - oldSize.y };
				sf::Vector2f currLoc = images[i]->getShape().getPosition();

				images[i]->getShape().setPosition(currLoc - sf::Vector2f(diffLoc.x / 2.0, diffLoc.y / 2.0));
				currTime = clock();
				soundTime = images[i]->getBuffer().getDuration().asMilliseconds() + currTime;

				images[i]->play();
			}

			if (defSize.x * 2 <= images[i]->getShape().getSize().x) {
				shrinkDown = true;
			}
			if (shrinkDown && clock() >= soundTime) {
				sf::Vector2f oldSize = images[i]->getShape().getSize();
				images[i]->getShape().setSize({ (float)(oldSize.x * 0.995), (float)(oldSize.y * 0.995) });

				sf::Vector2f newSize = images[i]->getShape().getSize();

				sf::Vector2f diffLoc = { newSize.x - oldSize.x, newSize.y - oldSize.y };
				sf::Vector2f currLoc = images[i]->getShape().getPosition();

				images[i]->getShape().setPosition(currLoc - sf::Vector2f(diffLoc.x / 2.0, diffLoc.y / 2.0));
			}

			if ((int)defSize.x == (int)images[i]->getShape().getSize().x) {
				i++;
				shrinkDown = false;
			}
			window.clear();
			uptade(this->buttons);

			window.display();

		}

		return buttons[objIndex]->getPlayer();
	}


	void randElementsLevel1() {
		const size_t size = 3;
		this->buttons.resize(size);
		// on currLevel == 0 we have different objects with the same color

		int randRow = rand() % objects.size(),
			secondRandRow = -1;

		// shitty rand system
		do {
			secondRandRow = rand() % objects.size();
		} while (secondRandRow != randRow);

		// ===

		std::unordered_set<int> set;

		// get random element and change just change its color
		int randIndex = this->objects[randRow].size() - 1;

		size_t saveIndex = 0, saveColor = 0;
		// it won't work if objects[randRow] <= 1
		for (int i = 0; i < objects[randRow].size(); i++) {
			int k = rand() % objects[randRow].size();

			if (set.find(k) != set.end()) {
				i--;
				continue;
			}

			if (randIndex == i) {
				int randColor = -1;

				do {
					randColor = rand() % objects.size();
				} while (randColor == saveColor);

				this->buttons[i] = &objects[randColor][saveIndex];
				continue;
			}

			set.insert(k);
			buttons[i] = &objects[randRow][k];

			if (randIndex == i + 1) {
				saveColor = randRow;
				saveIndex = k;
			}
		}

		// change a random index from buttons with the same shape, but with different color
	}

	void randElementsLevel2() {
		size_t randFigure = rand() % objects.size();

		const size_t size = objects[0].size();

		this->buttons.resize(size);

		std::unordered_set<int> q;
		for (size_t i = 0; i < size; i++) {

			int randColor = rand() % size;
			while (q.find(randColor) != q.end())
				randColor = rand() % size;

			this->buttons[i] = &objects[randColor][randFigure];

			q.insert(randColor);
		}
	}

	bool moving(sf::Vector2f& pos, sf::Vector2i center, const int pixels) {
		static bool flag = false;
		if (abs((int)pos.x - center.x) > 0 && !flag) { // Moving x 

			if (pos.x > center.x)
				pos.x -= pixels;
			else
				pos.x += pixels;

		}
		else if (abs((int)pos.y - center.y) > 0) { // Moving y

			if (pos.y > center.y)
				pos.y -= pixels;
			else
				pos.y += pixels;
		}
		else if ((int)pos.x == center.x && (int)pos.y == center.y)
			return false;

		flag = !flag;

		return true;
	}

	bool animate(std::vector<Image*>& buttons) {
		while (window.isOpen()) {
			sf::Event e;
			while (window.pollEvent(e)) {
				if (e.type == sf::Event::Closed)
					window.close();
			}

			// CALCULATIONS
			if (buttons.size() == 0)
				return false;
			const int pixels = 1;
			sf::Vector2f pos = buttons[objIndex]->getShape().getPosition();

			if (!isOnCenter) {
				std::cout << pos.x << ' ' << pos.y << std::endl;

				if (!moving(pos, center, pixels))
					isOnCenter = true;
			}
			else if (buttons.size() > 0) {

				if (!moving(pos, animationPlace, pixels)) {

					buttons.erase(buttons.begin() + objIndex);

					if (buttons.size() == 0) {

					}
					else {
						objIndex = rand() % buttons.size();

						if (!flag) {
							animationPlace = positions[placeIndex];
						}
						else {
							animationPlace = positions[positions.size() - placeIndex - 1];
							placeIndex++;
						}

						isOnCenter = false;
						flag = !flag;

						continue;
					}
				}
			}
			// CALCULATIONS 
			if (buttons.size() > 0)
				buttons[objIndex]->getShape().setPosition(pos);
			else
				this->showAnimation = false;

			window.clear();

			uptade(buttons);

			window.display();
		}
	}

	void uptade(std::vector<Image*>& buttons) override {
		candle::RadialLight light;
		light.setRange(80);
		light.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
		window.draw(light);


		window.setFramerateLimit(600);
		for (int i = 0; i < randSize; i++)
			window.draw(images[i]->getShape());
	}

};

