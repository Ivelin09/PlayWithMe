#pragma once
#include<Candle/Candle.hpp>

#include "Window.h"
#include<unordered_set>

extern const double width, height;

class ObjectFinder : public Window
{
private:
    std::vector<Image> images;
    std::vector<Image> displayImages;
public:

    ObjectFinder(sf::RenderWindow& window, const std::vector<Image> images, const std::string& background, std::vector<std::pair<Image, Window*>> nav) :
        Window(window, background, nav), images(images) { }

    void randImages() {
        srand(time(0));
        size_t randSize = rand() % images.size();

        this->displayImages.resize(randSize);
        std::unordered_set<int> index;
        for (int i = 0; i < randSize; i++) {

            size_t randIndex = rand() % images.size();
            if (index.find(randIndex) != index.end()) {
                i--;
                continue;
            }

            displayImages[i] = images[randIndex];

            index.insert(randIndex);
        }
    }

	Window* start() override {
        candle::RadialLight light;

        light.setRange(100);
        light.setFade(true);
        // load the image
        sf::Texture img1;
        if (!img1.loadFromFile("Content/newBG.jpg")) {
            exit(1);
        }

        sf::Sprite background(img1);
        background.setScale(width / img1.getSize().x, height / img1.getSize().y);
        // create the lighting area
        candle::LightingArea fog(candle::LightingArea::FOG,
            sf::Vector2f(0.f, 0.f),
            sf::Vector2f(width, height));
        fog.setAreaColor(sf::Color::Black);

        // main loop
        while (window.isOpen()) {
            sf::Event e;
            while (window.pollEvent(e)) {
                if (e.type == sf::Event::Closed) {
                    window.close();
                }
                else if (e.type == sf::Event::MouseMoved) {
                    sf::Vector2f mp(sf::Mouse::getPosition(window));
                    light.setPosition(mp);
                }
            }

            fog.clear();
            fog.draw(light);
            fog.display();

            window.clear();

            for (auto& k : this->displayImages)
                window.draw(k.getShape());

            window.draw(background);
            window.draw(fog);

            window.display();
        }
        return 0;
	}
};

