#pragma once
#include "Window.h"

#include "Game.h"
#include "Symetric.h"

#include "Singleton.h"

class SoundGame : public Window, Game
{
protected:
    std::vector<Image> combinations;
    std::vector<Stars>* stars;

    std::vector<Image*> buttons;
    std::vector<sf::Vector2i> positions;
private:
    const std::string gameName = "SoundGame";
    int gameStar = 0;

    bool isActivate = false;
public:
    SoundGame(sf::RenderWindow& window, std::vector<Image> combinations, const std::string& path, std::vector<std::pair<Image, Window*>> nav) :
        Window(window, "figuresBG.png", nav), combinations(combinations)
    {

        // NAVTGATION

        this->nav.erase(this->nav.begin() + 1, this->nav.end());
        this->nav[Home].first.getShape().setPosition({ 0,0 });

        // ==========
        setSymetric(this->combinations, 0, width, this->combinations[0].getShape().getSize().x, height / 2);
    }

    void linkUp(std::vector<Stars>& star) {
        this->stars = &star;
    }

    ~SoundGame()
    {

    }

    void copyElements() {
        int randSize = rand() % combinations.size() + 1;
        buttons.resize(randSize);

        if (randSize < 2)
            randSize = 2;

        std::set<int> set;

        for (int i = 0; i < randSize; i++) {
            int k = rand() % combinations.size();

            if (set.find(k) != set.end()) {
                i--;
                continue;
            }

            set.insert(k);

            buttons[i] = &combinations[k];
        }
    }

    virtual Window* start() override
    {
        size_t q = clock();
        size_t period = 5000;

        // RAND
        
        copyElements();

        setSymetric(buttons, 0.0, width, buttons[0]->getShape().getSize().x, height / 2 - combinations[0].getShape().getSize().y / 2);

        Image* obj = buttons.at(rand() % buttons.size());
        obj->play();
        while (window.isOpen()) {
            sf::Event e;
            while (window.pollEvent(e))
            {
                if (e.type == sf::Event::Closed)
                    window.close();
                else if (e.type == sf::Event::MouseButtonPressed)
                {
                    const sf::Vector2f mouseCords = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    for (int i = 0; i < buttons.size(); i++)
                    {
                        sf::Vector2f size = buttons.at(i)->getShape().getSize();
                        sf::Vector2f position = buttons.at(i)->getShape().getPosition();

                        if (mouseCords.x >= position.x && mouseCords.x <= position.x + size.x &&
                            mouseCords.y >= position.y && mouseCords.y <= position.y + size.y)
                        {
                            if (obj == buttons.at(i)) {
                                strike++;
                                if (!isActivate && strike > 3) {
                                    strike = 0;
                                    if (reloadFile(1, this->stars->size(), this->gameName, Window::FILE, *this->stars) == this->stars->size())
                                        isActivate = true;

                                }
                                return this;
                            }
                            else {
                                strike = 0;
                                Singleton::get().incorrect.play();
                            }
                        }
                    }

                    for (auto& k : this->nav)
                    {
                        sf::Vector2f size = k.first.getShape().getSize();
                        sf::Vector2f position = k.first.getShape().getPosition();

                        if (mouseCords.x >= position.x && mouseCords.x <= position.x + size.x &&
                            mouseCords.y >= position.y && mouseCords.y <= position.y + size.y)
                            return k.second;

                    }
                }
            }


            if (q + period == clock())
            {
                obj->play();
                q = clock();
            }

            window.clear();

            uptade(buttons);

            window.display();
        }
        return nullptr;
    }

    virtual void uptade(std::vector<Image*>& buttons) {
        window.draw(this->background);

        for (auto& k : buttons)
            window.draw(k->getShape());

        for (auto& k : nav)
            window.draw(k.first.getShape());
    }

};