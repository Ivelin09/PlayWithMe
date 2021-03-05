#pragma once

#include "Window.h"
#include "Images.h"
#include<vector>

#include<list>
#include <thread>

#include<algorithm>

#include<iostream>
#include "Singleton.h"

extern const double width;
extern const double height;
#include<stack>

#include<ctime>
#include<cstdlib>

#include "Window.h"
class Sector;

enum NAVIGATION { Menu = 0, PlayAgain, FrontArrow, BackArrow };
#include "Symetric.h"


class DragGame : public Window
{
protected:
    static int index;

    std::vector<Image>::iterator saveIt;
    std::vector<Image> dropPic, dragPic;

    sf::Vector2f playAgain;

    double dragY, dropY;
    int correct = 0;

    int level = 0;
public:
    DragGame(sf::RenderWindow& window, std::vector<Image>& dragPic, std::vector<Image>& dropPic,
        const std::string& background);

    std::vector<Image>::iterator movingObj;

    virtual void randomize();
    Window* start() override;

    virtual void uptade();
    virtual void nextLevel();

    ~DragGame() = default;
};

class FigureDrag : public DragGame {
public:
    FigureDrag(sf::RenderWindow& window, std::vector<Image>& dragPic, std::vector<Image>& dropPic,
        const std::string& background) : DragGame(window, dragPic, dropPic, background) {}
private:
    void nextLevel() override {
        DragGame::nextLevel();

        if (this->level == 1) {
            std::cout << "CHANIGING LEVELS\n";

            flag = true;
        }
    }

    void randomize() override {
        if (flag) {
            this->dragPic = Singleton::get().figures;
            this->dropPic = Singleton::get().figuresPlace;

            flag = false;
        }

        DragGame::randomize();
        // Randomize is being called when the Play Again buttons is pressed 
    }

private:
    bool flag = false;
    const int unlockLevel = 3;
};

class SoundGame : public Window
{
private:
    std::vector<Image> combinations;
public:
    SoundGame(sf::RenderWindow& window, std::vector<Image> combinations, const std::string& path) : Window(window, "figuresBG.png"), combinations(combinations)
    {
        this->currWindow = WINDOW_TYPES::DragGame;
        setSymetric(this->combinations, 0, width, this->combinations[0].getShape().getSize().x, height / 2);

        this->nav[Menu].first.getShape().setPosition(0, 0);
    }

    ~SoundGame()
    {

    }

    Window* start() override
    {
        size_t q = clock();
        size_t period = 5000;

        // RAND

        int randSize = rand() % combinations.size();
        std::vector<Image> buttons(combinations.begin() + randSize, combinations.end());

        std::random_shuffle(buttons.begin(), buttons.end());

        // ==============
        setSymetric(buttons, 0, width, buttons[0].getShape().getSize().x, height / 2 - combinations[0].getShape().getSize().y / 2);

        Image* obj = &buttons[rand() % buttons.size()];
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
                        sf::Vector2f size = buttons[i].getShape().getSize();
                        sf::Vector2f position = buttons[i].getShape().getPosition();

                        if (mouseCords.x >= position.x && mouseCords.x <= position.x + size.x &&
                            mouseCords.y >= position.y && mouseCords.y <= position.y + size.y)
                        {
                            if (obj == &buttons[i])
                                return this;
                            else
                                Singleton::get().incorrect.play();
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

            std::cout << q + period << ' ' << clock() << std::endl;

            if (q + period == clock())
            {
                obj->play();
                q = clock();
            }

            window.clear();

            window.draw(this->background);

            for (auto& k : buttons)
                window.draw(k.getShape());

            for (auto& k : nav)
                window.draw(k.first.getShape());

            window.display();
        }
    }
};

/* class Navigation
{
private:
    DragGame* link;
public:
    void start()
    {

    }
}; */
