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
//kkkkkkkkkkkkkkkka
#include<ctime>
#include<cstdlib>

#include "Window.h"
class Sector;

#include "Symetric.h"
#include "Game.h"


class DragGame : public Window, Game
{
protected:
    static int index;

    Stars* star;
    bool isActivate = false;

    std::vector<Image>::iterator saveIt;
    std::vector<Image> dropPic, dragPic;

    sf::Vector2f playAgain;
    const std::string gameName = "DragGame";
    double dragY, dropY;
    int correct = 0;

    int level = 0;
    std::string secName;
public:
    DragGame(sf::RenderWindow& window, std::vector<Image> dragPic, std::vector<Image> dropPic,
        const std::string& background, std::vector<std::pair<Image, Window*>> nav);

    std::vector<Image>::iterator movingObj;

    virtual void randomize();
    Window* start() override;

    virtual void uptade();
    virtual void nextLevel();

    std::vector<std::pair<Image, Window*>>& getNav()  {
        return this->nav;
    }

    void linkUp(Stars& star, std::string secName) {
        this->star = &star;
        this->secName = secName;
    }

    ~DragGame() = default;
};

class ColorDrag : public DragGame {
    ColorDrag(sf::RenderWindow& window, std::vector<Image>& dragPic, std::vector<Image>& dropPic,
        const std::string& background, std::vector<std::pair<Image, Window*>> nav) : DragGame(window, dragPic, dropPic, background, nav) {}
};

class FigureDrag : public DragGame {
public:
    std::vector<Stars>* stars;
    FigureDrag(sf::RenderWindow& window, std::vector<Image>& dragPic, std::vector<Image>& dropPic,
        const std::string& background, std::vector<std::pair<Image, Window*>> nav) : DragGame(window, dragPic, dropPic, background, nav) {}

    void linkUp(std::vector<Stars>& stars, std::string sectorName) {
        this->stars = &stars;

        return;
    }
private:
    void nextLevel() override {
        DragGame::nextLevel();

        if (this->level == 1) {
            std::cout << "CHANIGING LEVELS\n";

            flag = true;
        }
    }

    void randomize() override {
        // IN PROCESS

        DragGame::randomize();
        // Randomize is being called when the Play Again buttons is pressed 
    }

private:
    bool flag = false;
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