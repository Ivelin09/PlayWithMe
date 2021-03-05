#include "Singleton.h"

#include "DragGame.h"

Singleton& Singleton::get()
{
	return obj;
}

#include "FallingFigures.h"
#include "SimonGame.h"

sf::Sound Singleton::correct;
sf::Sound Singleton::incorrect;

Image Singleton::star;
Image Singleton::unfilledStar;


#include "Window.h"
#include "Sector.h"

sf::SoundBuffer Singleton::correctSound, Singleton::incorrectSound;
std::vector<std::pair<sf::RectangleShape, Window*>> Singleton::digits;

Singleton::Singleton()
{

	// SETTING TEXTURES
	one.setTexture("one.png");
	onePlace.setTexture("onePlace.png");

	one.setSound("one.wav");

	two.setTexture("two.png");
	twoPlace.setTexture("twoPlace.png");

	three.setTexture("three.png");
	threePlace.setTexture("threePlace.png");

	four.setTexture("four.png");
	fourPlace.setTexture("fourPlace.png");

	five.setTexture("five.png");
	fivePlace.setTexture("fivePlace.png");

	six.setTexture("six.png");
	sixPlace.setTexture("sixPlace.png");

	seven.setTexture("seven.png");
	sevenPlace.setTexture("sevenPlace.png");

	eight.setTexture("eight.png");
	eightPlace.setTexture("eightPlace.png");

	nine.setTexture("nine.png");
	ninePlace.setTexture("ninePlace.png");

	musicButton.setTexture("Music.png");
	playWithMe.setTexture("playWithMe.png");

	square.setTexture("square.png");
	triangle.setTexture("triangle.png");
	circle.setTexture("circle.png");

	squarePlace.setTexture("squarePlace.png");
	trianglePlace.setTexture("trianglePlace.png");
	circlePlace.setTexture("circlePlace.png");

	orangeSquare.setTexture("orangeSquare.png");
	orangeTriangle.setTexture("orangeTriangle.png");
	orangeCircle.setTexture("orangeCircle.png");

	orangeSquarePlace.setTexture("orangeSquarePlace.png");
	orangeTrianglePlace.setTexture("orangeTrianglePlace.png");
	orangeCirclePlace.setTexture("orangeCirclePlace.png");

	dragGameIcon.setTexture("DragGameIcon.png");
	soundGameIcon.setTexture("SoundGameIcon.png");

	game.setTexture("game1.png");
	game1.setTexture("game2.png");
	game2.setTexture("game3.png");

	home.setTexture("home.png");
	unfilledStar.setTexture("unfilledStar.png");

	star.setTexture("star.png");
	figuresImage.loadFromFile(ImagePath + "buttonFigures.png");


	// SETTING SIZES
	home.getShape().setSize(sf::Vector2f((width + height) / 17, (width + height) / 17));
	unfilledStar.getShape().setSize(sf::Vector2f((width + height) / 25, (width + height) / 25));
	star.getShape().setSize(sf::Vector2f((width + height) / 25, (width + height) / 25));

	// SETTING UP AUDIO 

	square.setSound("Square.wav");
	circle.setSound("circle.wav");
	triangle.setSound("Triangle.wav");

	orangeSquare.setSound("Square.wav");
	orangeTriangle.setSound("Triangle.wav");
	orangeCircle.setSound("Circle.wav");

	one.setSound("one.wav");
	two.setSound("two.wav");
	three.setSound("three.wav");
	four.setSound("four.wav");
	five.setSound("five.wav");
	six.setSound("six.wav");
	seven.setSound("seven.wav");
	eight.setSound("eight.wav");
	nine.setSound("nine.wav");

	correctSound.loadFromFile(AudioPath + "correct.wav");
	correct.setBuffer(correctSound);

	incorrectSound.loadFromFile(AudioPath + "incorrect.wav");;
	incorrect.setBuffer(incorrectSound);

	// PUSHING FIGURES 
	figures.push_back(square);
	figures.push_back(triangle);
	figures.push_back(circle);

	figuresPlace.push_back(squarePlace);
	figuresPlace.push_back(trianglePlace);
	figuresPlace.push_back(circlePlace);

	//BUTTONS

	std::cout << window.getSize().x << ' ' << window.getSize().y << std::endl;

	sf::RectangleShape button(sf::Vector2f(width / 6, height / 6));
	button.setPosition(sf::Vector2f(window.getSize().x / 2 - button.getSize().x / 2,
		window.getSize().y / 2 - button.getSize().y / 2 + 100));

	backArrow.setTexture("backArrow.png");
	nextArrow.setTexture("nextArrow.png");

	playAgain.setTexture("button_next.png");

	backArrow.getShape().setSize(sf::Vector2f(width / 10, height / 10));
	nextArrow.getShape().setSize(sf::Vector2f(width / 10, height / 10));
	playAgain.getShape().setSize(sf::Vector2f(width / 5, height / 8));
	playWithMe.getShape().setSize(sf::Vector2f(width / 4, height / 11));

	playWithMe.getShape().setPosition(width / 2 - playWithMe.getShape().getSize().x / 2, 50);
	backArrow.getShape().setPosition(25, 25);
	nextArrow.getShape().setPosition(width - nextArrow.getShape().getSize().x - 25, 25);
	playAgain.getShape().setPosition(width / 2 - playAgain.getShape().getSize().x / 2, height - playAgain.getShape().getSize().y - (height / 14));
	home.getShape().setPosition(25,
		backArrow.getShape().getPosition().y + backArrow.getShape().getSize().y);

	gameAudio.openFromFile(AudioPath + "gameAudio.wav");
	gameAudio.setPitch(1);

	gameAudio.setVolume(50);
	gameAudio.setLoop(true);

	musicButton.getShape().setSize(sf::Vector2f(width / 10, height / 10));
	musicButton.getShape().setOutlineThickness(2);

	// Digit Game Level 1
	dragPic.push_back(one);
	dragPic.push_back(two);
	dragPic.push_back(three);

	dropPic.push_back(onePlace);
	dropPic.push_back(twoPlace);
	dropPic.push_back(threePlace);

	std::vector<std::pair<Image, Window*>> nav;

	DragGame* GameLevel1 = new DragGame(window, dragPic, dropPic, "DigitBG.jpg");

	digitImage.loadFromFile(ImagePath + "buttonDigits.png");
	button.setTexture(&digitImage);

	//digits.emplace_back(button, GameLevel1);

	// Digit Game 0-5

	dragPic.push_back(four);
	dragPic.push_back(five);

	dropPic.push_back(fourPlace);
	dropPic.push_back(fivePlace);
	DragGame* GameLevel2 = new DragGame(window, dragPic, dropPic, "DigitBG.jpg");

	nav.clear();

	nav.emplace_back(home, nullptr);
	nav.emplace_back(playAgain, GameLevel1);
	nav.emplace_back(nextArrow, GameLevel2);
	nav.emplace_back(backArrow, nullptr);

	GameLevel1->setNav(nav);

	dragPic.push_back(six);
	dropPic.push_back(sixPlace);

	dragPic.push_back(seven);
	dropPic.push_back(sevenPlace);

	dragPic.push_back(eight);
	dropPic.push_back(eightPlace);

	dragPic.push_back(nine);
	dropPic.push_back(ninePlace);

	nav.clear();

	DragGame* GameLevel3 = new DragGame(window, dragPic, dropPic, "DigitBG.jpg");

	nav.emplace_back(home, nullptr);
	nav.emplace_back(playAgain, GameLevel2);
	nav.emplace_back(nextArrow, GameLevel3);
	nav.emplace_back(backArrow, GameLevel1);

	GameLevel2->setNav(nav);

	nav.clear();

	nav.emplace_back(home, nullptr);
	nav.emplace_back(playAgain, GameLevel3);
	nav.emplace_back(nextArrow, nullptr);
	nav.emplace_back(backArrow, GameLevel2);

	GameLevel3->setNav(nav);

	// FIGURES DRAGROP

	dropPic.clear();
	dragPic.clear();
	nav.clear();

	dragPic.push_back(orangeSquare);
	dragPic.push_back(orangeTriangle);
	dragPic.push_back(orangeCircle);

	dropPic.push_back(orangeSquarePlace);
	dropPic.push_back(orangeTrianglePlace);
	dropPic.push_back(orangeCirclePlace);

	FigureDrag* figuresLevel = new FigureDrag(window, dragPic, dropPic, "figuresBG.png");

	// FIGURES NAV

	nav.emplace_back(home, nullptr);
	nav.emplace_back(playAgain, figuresLevel);

	nav.emplace_back(nextArrow, nullptr);
	nav.emplace_back(backArrow, nullptr);

	sf::RectangleShape figuresButton(sf::Vector2f(width / 4, height / 4));
	figuresButton.setTexture(&figuresImage);

	double additionalSpace = figuresButton.getSize().y / 2;

	figuresButton.setPosition(width / 2 - figuresButton.getSize().x / 2, height / 2 - figuresButton.getSize().y / 2 + additionalSpace);
	figuresLevel->setNav(nav);

	nav.clear();

	dragPic.clear();
	dropPic.clear();
	// Click On Figure

	std::vector<Image> buttons;
	sf::RectangleShape q(sf::Vector2f(200, 200));

	buttons.emplace_back(one);
	buttons.emplace_back(two);
	buttons.emplace_back(three);
	buttons.emplace_back(four);
	buttons.emplace_back(five);
	buttons.emplace_back(six);
	buttons.emplace_back(seven);
	buttons.emplace_back(eight);
	buttons.emplace_back(nine);

	//std::vector<Image> digits = buttons;
	FallingFigures* digitsFall = new FallingFigures(window, buttons, "DigitBg.jpg");

	SoundGame* digitSound = new SoundGame(window, buttons, "DragGame.png");

	buttons.clear();

	buttons.emplace_back(square);
	buttons.emplace_back(triangle);
	buttons.emplace_back(circle);

	SoundGame* figuresSound = new SoundGame(window, buttons, "figuresBG.png");

	button.setPosition(100, 100);

	home.getShape().setPosition(0, 0);

	nav.emplace_back(home, nullptr);
	nav.emplace_back(playAgain, figuresLevel);

	digitSound->setNav(nav);


	buttons.clear();
	Image a, a1, a2;;

	buttons.emplace_back(a);
	buttons.emplace_back(a1);
	buttons.emplace_back(a2);

	FallingFigures* figuresFall = new FallingFigures(window, figures, "DigitBg.jpg");

	Sector* sec = new Sector(window,
		{ GameLevel1, digitSound, digitsFall },
		buttons);
	Sector* sec1 = new Sector(window, { figuresLevel, figuresSound , figuresFall }, buttons);
	buttons.clear();

	nav.pop_back();

	nav[0].first.getShape().setScale(sf::Vector2f(0.9, 0.9));

	sec->setNav(nav);
	sec1->setNav(nav);

	nav.clear();
	nav.emplace_back( home, nullptr );

	figuresFall->setNav(nav);
	digitsFall->setNav(nav);

	GameLevel1->setSector(*sec);
	GameLevel2->setSector(*sec);
	GameLevel3->setSector(*sec);

	button.setSize(figuresButton.getSize());
	button.setPosition(width / 2 - button.getSize().x / 2, height / 2 - button.getSize().y / 2 - additionalSpace);

	digits.emplace_back(button, sec);
	digits.emplace_back(figuresButton, sec1);

	digits.emplace_back(button, digitSound);
}
Singleton Singleton::obj;
