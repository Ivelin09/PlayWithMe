#pragma once

#include<string>
#include<vector>

#include<SFML/Graphics.hpp>
#include "Images.h"

class Sector;

enum class WINDOW_TYPES { DragGame, SoundGame };

class Window
{
public:
    Sector* sector = nullptr;

    Window(sf::RenderWindow& window, const std::string& image);
    void setNav(const std::vector<std::pair<Image, Window*>>& nav);

    virtual Window* start() = 0;
    ~Window() = default;

    void setSector(Sector& q) {
        this->sector = &q;
    }

    WINDOW_TYPES currWindow;
protected:
    std::vector<std::pair<Image, Window*>> nav;
    sf::RenderWindow& window;

    sf::Texture file;
    sf::Sprite background;
};
