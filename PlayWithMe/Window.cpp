#include "Window.h"
#include <SFML/Graphics.hpp>

#include "DragGame.h"
#include "Singleton.h"

#include<Windows.h>

Window::Window(sf::RenderWindow& window, const std::string& image, std::vector<std::pair<Image, Window*>> nav) : 
    nav(nav), window(window)
{
    file.loadFromFile("Content/" + image);
    background.setTexture(file);

    background.setScale(width / file.getSize().x, height / file.getSize().y);
}

void Window::setNav(const std::vector<std::pair<Image, Window*>>& nav)
{
    this->nav = nav;

    if (this->nav.size() > 1)
        this->nav[PlayAgain].first.setVisibility(false);
}

Window* Window::start()
{
    return nullptr;
}