#pragma once
#include "SoundGame.h"

#include "Window.h"

extern const double width, height;

class ColorSound : public SoundGame 
{
private:
	std::vector<sf::Vector2i> positions;
	sf::Vector2i animationPlace;
public:
	Image* animateObj = nullptr;

	bool isOnCenter = false;
	sf::Vector2i center;

	int placeIndex = 0, objIndex = 0;
	bool flag = true;

	Image** images = nullptr;

	ColorSound(sf::RenderWindow& window, std::vector<Image> combinations, const std::string& path, std::vector<std::pair<Image, Window*>> nav) :
		SoundGame(window, combinations, path, nav) {
	
		

		const float objWidth = combinations[0].getShape().getSize().x;
		const float objHeight = combinations[0].getShape().getSize().y;

		for (auto& k : this->combinations)
			k.getShape().setPosition({ (float)(width / 2.0 - objWidth/2), (float)(-k.getShape().getSize().y )});

		// SYMETRIC MATH

		center = { (int) (width / 2 - objWidth / 2), (int)( objHeight / 4)};
		double substractedWidth = width - (objWidth * combinations.size());
		double deltaWidth = substractedWidth / (combinations.size() * 2);

		double currPos = 0;

		for (int i = 0; i < combinations.size(); i++) {
			currPos += deltaWidth;

			// !
			positions.emplace_back(currPos, height / 2 - 200);

			currPos += deltaWidth + objWidth;
		}
		// =========
		objIndex = rand() % this->combinations.size();
		animationPlace = positions[placeIndex];
	}

	Window* start() override {
		// cursor
		
		int randSize = rand() % this->combinations.size();
		buttons.resize(3);
		images = new Image*[3];


		for (int i = 0; i < 3; i++) {
			buttons[i] = &this->combinations[i];
			images[i] = &this->combinations[i];
		}
		
		while (window.isOpen()) {
			sf::Event e;
			while (window.pollEvent(e)) {
				if (e.type == sf::Event::Closed)
					window.close();
			}

			window.clear();

			uptade(buttons);

			window.display();

		}
		return nullptr;
	}

	bool moving(sf::Vector2f& pos, sf::Vector2i center, const int pixels) {
		static bool flag = false;
		if (abs((int)pos.x - center.x) > 0 && !flag){ // Moving x 

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
		else if((int)pos.x == center.x && (int)pos.y == center.y)
			return false;

		flag = !flag;

		return true;
	}

	bool animate(std::vector<Image*>& buttons) {
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

					return true;
				}
			}
		}

		if (buttons.size() > 0)
			buttons[objIndex]->getShape().setPosition(pos);
		return true;
	}

	void uptade(std::vector<Image*>& buttons) {
		window.setFramerateLimit(400);

		if (!animate(buttons)) {

		}

		for(int i = 0; i < 3; i++)
		    window.draw(images[i]->getShape());

	}

};

