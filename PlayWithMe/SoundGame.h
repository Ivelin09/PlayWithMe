#pragma once
#include "Window.h"

#include "Game.h"
#include "Symetric.h"

#include "Singleton.h"

class SoundGame : public Window, virtual public Game
{
protected:
    std::vector<Image> combinations;
    std::vector<Stars>* stars;

    std::vector<Image*> buttons;

    std::vector<sf::Vector2i> positions;
    //std::list<sf::Sound*> manageSound;
private:
    const std::string gameName = "SoundGame";
    int gameStar = 0;

    Image* obj;
    bool isActivate = false;

    std::string secName;
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


    SoundGame(sf::RenderWindow& window, std::vector<std::vector<Image>> combinations, const std::string& path, std::vector<std::pair<Image, Window*>> nav) :
        Window(window, "figuresBG.png", nav)
    {
        // NAVTGATION

        this->nav.erase(this->nav.begin() + 1, this->nav.end());
        this->nav[Home].first.getShape().setPosition({ 0,0 });

        // ==========

        this->combinations.resize(combinations.size() * combinations[0].size());

        for (int i = 0; i < combinations.size(); i++)
            for (int j = 0; j < combinations[i].size(); j++)
                this->combinations[i] = combinations[i][j];

        setSymetric(this->combinations, 0, width, this->combinations[0].getShape().getSize().x, height / 2);
    }

    void linkUp(std::vector<Stars>& star, std::string secName) {
        this->stars = &star;
        this->secName = secName;
    }

    ~SoundGame()
    {

    }

    virtual void copyElements() {
        int randSize = rand() % combinations.size() + 1;

        if (randSize < 2)
            randSize = 2;

        buttons.resize(randSize);

        std::set<int> set;

        for (int i = 0; i < randSize; i++) {
            int k = rand() % combinations.size(); // randSize

            if (set.find(k) != set.end()) {
                i--;
                continue;
            }

            set.insert(k);

            buttons[i] = &combinations[k];
        }
    }

    virtual void intro() {
        copyElements();

        setSymetric(buttons, 0.0, width, buttons[0]->getShape().getSize().x, height / 2 - combinations[0].getShape().getSize().y / 2);
    }

    virtual void correctAnswer() {
        strike++;
        if (!isActivate && strike > 3) {
            strike = 0;
            Singleton::table.levelUp(this->secName, GAME_TYPE::SOUNDGAME);
            isActivate = true;

        }
    }

    virtual sf::Sound& incorrectAnswer() {
        strike = 0;
        return Singleton::get().incorrect;
    }

    virtual Image* random() {
        return buttons.at(rand() % buttons.size());
    }


    void runSound(Image& obj) {
        obj.play();
        while (window.isOpen() && obj.getPlayer().getStatus() != sf::Sound::Status::Stopped) {
            sf::Event e;
            while (window.pollEvent(e)) {

            }
        }
        return;
    }

    virtual Window* start() override
    {
        int period = 5000, q = -period;
        // RAND
        
        intro();

        obj = random();
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
                                correctAnswer();
                                return this;
                            }
                            else {
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


            if (q + period <= clock())
            {
                // passing the current sound of the object
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