#ifndef SINGLETON_H
#define SINGLETON_H

#include "Images.h"
#include<vector>

#include<list>
#include "Window.h"

class DragGame;

extern sf::RenderWindow window;

class Singleton
{
public:
	static Singleton& get();

	Singleton();
	~Singleton() = default;

	Singleton(const Singleton&) = delete;
	void operator=(const Singleton&) = delete;

	static sf::SoundBuffer correctSound, incorrectSound;
	static sf::Sound correct, incorrect;

	Image one, two, three, four, five, six, seven, eight, nine;
	Image orangeSquare, orangeTriangle, orangeCircle, square, triangle, circle;

	std::vector<Image*> orangeFigures{ &orangeSquare, &orangeTriangle, &orangeCircle };

	Image onePlace, twoPlace, threePlace, fourPlace, fivePlace,
		sixPlace, sevenPlace, eightPlace, ninePlace;
	Image orangeSquarePlace, orangeTrianglePlace, orangeCirclePlace,
		squarePlace, trianglePlace, circlePlace;

    Image game, game1, game2;

	std::vector<Image> figures, figuresPlace;

	Image playWithMe;
	Image dragGameIcon, soundGameIcon;

	Image home;
	static Image star, unfilledStar;

	Image musicButton;
	sf::Music gameAudio;

	Image backArrow, nextArrow, playAgain;

	sf::Texture figuresImage, digitImage;

	std::vector<Image> dragPic, dropPic;
	static std::vector<std::pair<sf::RectangleShape, Window*>> digits;
private:

	static Singleton obj;
};

#endif