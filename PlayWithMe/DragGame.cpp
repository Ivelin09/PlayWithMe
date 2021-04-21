#include "DragGame.h"

#include "Sector.h"

#include<SFML/Graphics.hpp>

#include "Game.h"

#include "Symetric.h"
DragGame::DragGame(sf::RenderWindow& window, std::vector<Image> dragPic,
    std::vector<Image> dropPic, const std::string& background, std::vector<std::pair<Image, Window*>> nav) : Window(window, background, nav),
    dropPic(dropPic), dragPic(dragPic)
{
    // NAVIGATION 
    this->nav[PlayAgain].first.setVisibility(false);
    this->nav[PlayAgain].second = this;

    // ================

    double substractedWidth = width - (dragPic.begin()->getShape().getSize().x * dragPic.size());

    double deltaWidth = substractedWidth / (dragPic.size() * 2);

    const double additionalSpace = height / 6;

    const double additionalSpaceUp = height / 8;
    const double additionalSpaceDown = height / 6;

    double currPos = 0;

    dragY = height / 2 - (dragPic[0].getShape().getSize().y / 2) - additionalSpaceUp;
    dropY = height / 2 - (dragPic[0].getShape().getSize().y / 2) + additionalSpace;

    setSymetric(this->dragPic, 0, width, dragPic[0].getShape().getSize().x, dragY);
    setSymetric(this->dropPic, 0, width, dragPic[0].getShape().getSize().x, dropY);
}

void DragGame::nextLevel() {
    this->level++;
}

void DragGame::uptade() {
    window.draw(this->background);

    for (auto& k : nav)
        window.draw(k.first.getShape());

    for (auto& it : dropPic)
        window.draw(it.getShape());

    for (auto& it : dragPic)
        window.draw(it.getShape());
}

int DragGame::index = 0;

void DragGame::randomize()
{
    srand(time(0));

    for (int i = 0; i < dragPic.size(); i++)
    {
        int q = rand() % dragPic.size();

        sf::Vector2f location = dragPic[q].getShape().getPosition();

        dragPic[q].getShape().setPosition(dragPic[i].getShape().getPosition().x, dragY);
        dragPic[i].getShape().setPosition(location.x, dragY);
    }

    for (int i = 0; i < dragPic.size(); i++)
    {
        int q = rand() % dragPic.size();

        sf::Vector2f location = dropPic[q].getShape().getPosition();

        dropPic[q].getShape().setPosition(dropPic[i].getShape().getPosition().x, dropY);
        dropPic[i].getShape().setPosition(location.x, dropY);
    }

}

Window* DragGame::start()
{
    const auto arr = Singleton::get().digits;
    this->movingObj = dragPic.end();

    sf::Vector2f back;
    bool hold = false;

    sf::Vector2f oldPos;
    bool nextGame = false;
    const size_t generated = dragPic.size();

    bool correctSound = false;
    double correctTime = 0;

    bool mistake = false;
    Image save;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {

                const sf::Vector2f mouseCords = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                // ARROW NAVIGATION

                for (int i = 0; i < nav.size(); i++)
                {
                    sf::Vector2f size = nav[i].first.getShape().getSize();
                    sf::Vector2f position = nav[i].first.getShape().getPosition();

                    if (mouseCords.x >= position.x && mouseCords.x <= position.x + size.x &&
                        mouseCords.y >= position.y && mouseCords.y <= position.y + size.y) {
                        if (i == PlayAgain) {
                            correct = 0;

                            // checking if are all correct with no mistakes
                            if(!mistake)
                                strike++;

                            if (!isActivate) {
                                isActivate = true; 
                                Singleton::table.levelUp(this->secName, GAME_TYPE::DRAGGAME);
                            }

                            this->nav[PlayAgain].first.setVisibility(false);
                            randomize();
                        }
                        else if (i == FrontArrow) {
                            index++;
                        }
                        else if (i == BackArrow) {
                            index--;
                        }
                        return nav[i].second;
                    }
                }

                // DRAG & DROP

                auto it1 = dropPic.begin();
                for (auto it = dragPic.begin(); it != dragPic.cend(); ++it) {
                    sf::Vector2f size = it->getShape().getSize();
                    sf::Vector2f position = it->getShape().getPosition();

                    if (mouseCords.x >= position.x && mouseCords.x <= position.x + size.x &&
                        mouseCords.y >= position.y && mouseCords.y <= position.y + size.y) {

                        std::cout << "NEW SAVE\n";
                        this->saveIt = it1;
                        movingObj = it;

                        back = movingObj->getShape().getPosition();
                        hold = true;
                    }
                    oldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    if (it1 != dropPic.end())
                        ++it1;
                }
            }
            else if (hold && event.type == sf::Event::MouseMoved) {
                const sf::Vector2f mouseCords = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                const double newCordsX = movingObj->getShape().getPosition().x - oldPos.x + mouseCords.x;
                const double newCordsY = movingObj->getShape().getPosition().y - oldPos.y + mouseCords.y;

                if (newCordsX >= 0 && newCordsX + movingObj->getShape().getSize().x <= width
                    && newCordsY >= 0 && newCordsY + movingObj->getShape().getSize().y <= height) {
                    sf::Vector2f cornerX = movingObj->getShape().getPosition();
                    sf::Vector2f cornerY = sf::Vector2f(movingObj->getShape().getPosition().x + movingObj->getShape().getSize().x,
                        movingObj->getShape().getPosition().y + movingObj->getShape().getSize().y);

                    movingObj->getShape().setPosition(newCordsX, newCordsY);

                    auto pos1 = dropPic.begin();
                    for (auto it = dragPic.begin(); pos1 != dropPic.end() && it != dragPic.end(); ++it, ++pos1)
                    {
                        sf::Vector2u size1(movingObj->getShape().getSize().x, movingObj->getShape().getSize().y);
                        sf::Vector2f position1 = pos1->getShape().getPosition();

                        if ((cornerX.x >= position1.x &&
                            cornerX.x <= position1.x + size1.x && cornerX.y >= position1.y && cornerX.y <= position1.y + size1.y) ||
                            (cornerY.x >= position1.x && cornerY.x <= position1.x + size1.x && cornerY.y >= position1.y && cornerY.y <= position1.y + size1.y) ||
                            (cornerX.x >= position1.x && cornerX.x <= position1.x + size1.x && cornerY.y >= position1.y && cornerY.y <= position1.y + size1.y) ||
                            (cornerY.x >= position1.x && cornerY.x <= position1.x + size1.x && cornerX.y >= position1.y && cornerX.y <= position1.y + size1.y))
                        {
                            hold = false;
                            if (this->saveIt == pos1) {
                                save = *movingObj;
                                movingObj->getShape().setPosition(pos1->getShape().getPosition());

                                it->play();
                                if (++correct == generated)
                                {
                                    correctTime = clock() + 1500;
                                    correctSound = true;
                                    this->nextLevel(); // tracing the completed levels

                                    //sector->getStars()[(int)WINDOW_TYPES::DragGame][index].activate();
                                    this->nav[PlayAgain].first.setVisibility(true);
                                }

                                //std::cout << position1.x << ' ' << position1.y << " | " << mouseCords.x << ' ' << mouseCords.y << std::endl;
                            }
                            else {
                                Singleton::get().incorrect.play();

                                mistake = true;
                                movingObj->getShape().setPosition(back);
                            }
                            break;
                        }
                    }
                    oldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                }
                else
                {
                    sf::Vector2f cornerX = movingObj->getShape().getPosition();
                    sf::Vector2f cornerY = sf::Vector2f(movingObj->getShape().getPosition().x + movingObj->getShape().getSize().x,
                        movingObj->getShape().getPosition().y + movingObj->getShape().getSize().y);

                    auto pos1 = dropPic.begin();
                    for (auto it = dragPic.begin(); it != dragPic.end(); ++it, ++pos1)
                    {
                        sf::Vector2u size1(movingObj->getShape().getSize().x, movingObj->getShape().getSize().y);
                        sf::Vector2f position1 = pos1->getShape().getPosition();

                        if ((cornerX.x >= position1.x &&
                            cornerX.x <= position1.x + size1.x && cornerX.y >= position1.y && cornerX.y <= position1.y + size1.y) ||
                            (cornerY.x >= position1.x && cornerY.x <= position1.x + size1.x && cornerY.y >= position1.y && cornerY.y <= position1.y + size1.y) ||
                            (cornerX.x >= position1.x && cornerX.x <= position1.x + size1.x && cornerY.y >= position1.y && cornerY.y <= position1.y + size1.y) ||
                            (cornerY.x >= position1.x && cornerY.x <= position1.x + size1.x && cornerX.y >= position1.y && cornerX.y <= position1.y + size1.y))
                            movingObj->getShape().setPosition(back);
                    }
                    hold = false;
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                hold = false;
                movingObj = dragPic.begin();
            }
        }

        if (correctSound && clock() >= correctTime) {
            std::cout << "PLAY\n";
            Singleton::get().correct.play();

            correctSound = false;
        }

        window.clear();

        uptade();

        window.display();
    }
    return nullptr;
}