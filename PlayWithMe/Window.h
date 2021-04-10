#pragma once

#include<string>
#include<vector>

#include<SFML/Graphics.hpp>
#include "Images.h"

#include "Stars.h"

enum NAVIGATION { Home = 0, PlayAgain, FrontArrow, BackArrow };
enum GAME_TYPE {Figures, Digits};

class Sector;

class Window
{
public:
    Sector* sector = nullptr;
    static const std::string FILE;

    Window(sf::RenderWindow& window, const std::string& image, std::vector<std::pair<Image, Window*>> nav);
    void setNav(const std::vector<std::pair<Image, Window*>>& nav);

    virtual Window* start() = 0;
    ~Window() = default;

    void setSector(Sector& q) {
        this->sector = &q;
    }
protected:
    std::vector<std::pair<Image, Window*>> nav;
    sf::RenderWindow& window;

    sf::Texture file;
    sf::Sprite background;
};