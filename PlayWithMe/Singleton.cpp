#include "Singleton.h"
#include "DragGame.h"

Singleton& Singleton::get()
{
	return obj;
}

#include "FallingFigures.h"

sf::Sound Singleton::correct;
sf::Sound Singleton::incorrect;

Image Singleton::star;
Image Singleton::unfilledStar;

#include "Window.h"
#include "Sector.h"

#include "ColorSound.h"
#include<memory>

#include "Symetric.h"

#include "DragGame.h"
#include "ObjectFinder.h"

sf::SoundBuffer Singleton::correctSound, Singleton::incorrectSound;

Resources Singleton::table;

std::vector<std::pair<sf::RectangleShape, Window*>> Singleton::digits;

Singleton::Singleton()
{
	enum class FIGURES { square, triangle, circle };

	// LOAD SAVE SYSTEM

	std::ifstream stream(Window::FILE);
	std::string input;

	if (!stream.is_open())
		std::cout << "PROBLEM OPENING THE FILE\n";

	std::getline(stream, input); // checking if the file is empty
	if (input.empty()) {
		// if empty rewrite the information
		std::ofstream streamInput(Window::FILE);
		streamInput << "Digits\nDragGame: 0\nSoundGame: 0\nFallingGame: 0\n" 
			<< "\nFigures\nDragGame: 1\nSoundGame: 0\nFallingGame: 0\n"
			<< "\nColors\nColor: 0\n"; 
		streamInput.close();
	} else {
		// if not get it
		std::ifstream streamOutput(Window::FILE);
		std::vector<std::pair<std::string, int>> info;

		std::string input, header;
		std::string output;

		bool isHeader = true;
		while (std::getline(streamOutput, input)) {
			if (input == "") {
				isHeader = true;
				continue;
			}

			if (isHeader) {
				header = input;
				isHeader = false;

				continue;
			}
			bool flag = false;

			int level = 0;
			std::string word;
			for (int i = 0; i < input.size(); i++) {

				if (input[i] == ' ')
					continue;

				if (input[i] == ':')
					flag = true;
				else if (!flag)
					word += input[i];
				else
					level = level * 10 + (input[i] - '0');
			}
			Singleton::table.getInfo()[header].push_back(level);
		
		}
		streamOutput.close();
	}
	stream.close(); 
	// =========
	musicButton.setTexture("Music.png");
	playWithMe.setTexture("playWithMe.png");

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

	// INITIALIZING FIGURES AND DIGITS




	std::string figures[] = { "square", "triangle", "circle" };
	std::string color[] = { "red", "green", "blue" };
	std::vector<Image> figuresPics(3), figuresPicsPlace(3);
	
	const size_t colorSize = sizeof(color) / sizeof(color[0]);
	const size_t figureSize = sizeof(figures) / sizeof(figures[0]);
	std::vector<std::vector<Image>> multiColorObjects(colorSize, std::vector<Image>(figureSize));

	for (size_t i = 0; i < colorSize; i++) {
		for (size_t j = 0; j < figureSize; j++) {
			multiColorObjects[i][j].setTexture(color[i] + figures[j] + ".png");
			multiColorObjects[i][j].getShape().setSize({200,200});

			// CONCATINATING SOUNDS 
			std::vector<sf::Int16> vec;

			sf::SoundBuffer colorSound, figureSound;

			colorSound.loadFromFile("Sound/" + (std::string)color[i] + ".wav");
			figureSound.loadFromFile("Sound/" + (std::string)figures[j] + ".wav");

			const sf::Int16* samplesA = colorSound.getSamples(),
				*samplesB = figureSound.getSamples();

			vec.reserve(colorSound.getSampleCount() + figureSound.getSampleCount());

			for (size_t i = 0; i < colorSound.getSampleCount(); ++i)
				vec.push_back(samplesA[i]);
			for (size_t i = 0; i < figureSound.getSampleCount(); ++i)
				vec.push_back(samplesB[i]);

		    sf::SoundBuffer combinedBuffer;
			combinedBuffer.loadFromSamples(vec.data(), vec.size(), colorSound.getChannelCount(), figureSound.getSampleRate());

			// ================
			multiColorObjects[i][j].setBuffer(combinedBuffer);
			multiColorObjects[i][j].tag = "STAR";
		}
	}

	std::cout << multiColorObjects[0][0].getBuffer().getDuration().asMicroseconds();

	std::vector<Image> digitPics, digitPicsPlace;
	digitPics.resize(9);
	digitPicsPlace.resize(9);

	for (int i = 0; i < digitPics.size(); i++) {
		const sf::Vector2f size((width + height) / 19, (width + height) / 19);

		digitPics[i].setTexture(std::to_string((i + 1)) + ".png");
		digitPics[i].getShape().setSize(size);

		digitPics[i].tag = std::to_string(i + 1);
		digitPics[i].setSound(std::to_string((i + 1)) + ".wav");

		digitPicsPlace[i].setTexture(std::to_string(i + 1) + "Place.png");
		digitPicsPlace[i].getShape().setSize(size);
	} 

	for (int i = 0; i < figuresPics.size(); i++) {
		const sf::Vector2f size((width + height) / 19, (width + height) / 19);

		figuresPicsPlace[i].setTexture(figures[i] + "Place.png");

		figuresPics[i].setTexture(figures[i] + ".png");
		figuresPics[i].setSound(figures[i] + ".wav");

		figuresPics[i].getShape().setSize(size);
		figuresPicsPlace[i].getShape().setSize(size);
	}

	// ================

	orangeSquare.setSound("Square.wav");
	orangeTriangle.setSound("Triangle.wav");
	orangeCircle.setSound("Circle.wav");

	correctSound.loadFromFile(AudioPath + "correct.wav");
	correct.setBuffer(correctSound);

	incorrectSound.loadFromFile(AudioPath + "incorrect.wav");;
	incorrect.setBuffer(incorrectSound);

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

	std::vector<std::pair<Image, Window*>> nav;

	nav.emplace_back(home, nullptr);
	nav.emplace_back(playAgain, nullptr);
	nav.emplace_back(nextArrow, nullptr);
	nav.emplace_back(backArrow, nullptr);

	DragGame* GameLevel1 = new DragGame(window, { digitPics[0], digitPics[1], digitPics[2] },
		{digitPicsPlace[0], digitPicsPlace[1], digitPicsPlace[2] }, "DigitBG.jpg", nav);

	digitImage.loadFromFile(ImagePath + "buttonDigits.png");
	button.setTexture(&digitImage);

	//digits.emplace_back(button, GameLevel1);

	DragGame* GameLevel2 = new DragGame(window, { digitPics[0], digitPics[1], digitPics[2], digitPics[3], digitPics[4] },
		{ digitPicsPlace[0], digitPicsPlace[1], digitPicsPlace[2], digitPicsPlace[3], digitPicsPlace[4] }, "DigitBG.jpg", nav);

	GameLevel1->getNav()[FrontArrow].second = GameLevel2;
	GameLevel2->getNav()[BackArrow].second = GameLevel1;

	DragGame* GameLevel3 = new DragGame(window, { digitPics[0], digitPics[1], digitPics[2], digitPics[3], digitPics[4], digitPics[5], digitPics[6], digitPics[7], digitPics[8] },
		{ digitPicsPlace[0], digitPicsPlace[1], digitPicsPlace[2], digitPicsPlace[3], digitPicsPlace[4], digitPicsPlace[5], digitPicsPlace[6], digitPicsPlace[7], digitPicsPlace[8] }, "DigitBG.jpg", nav);

	GameLevel2->getNav()[FrontArrow].second = GameLevel3;
	GameLevel3->getNav()[BackArrow].second = GameLevel2;

	FigureDrag* figuresLevel = new FigureDrag(window, figuresPics, figuresPicsPlace, "figuresBG.png", nav);

	sf::RectangleShape figuresButton(sf::Vector2f(width / 4, height / 4));
	figuresButton.setTexture(&figuresImage);

	double additionalSpace = figuresButton.getSize().y / 2;

	figuresButton.setPosition(width / 2 - figuresButton.getSize().x / 2, height / 2 - figuresButton.getSize().y / 2 + additionalSpace);
	// Click On Figure
	//std::vector<Image> digits = buttons;
	//FallingFigures* digitsFall = new FallingFigures(window, digitPics, "DigitBg.jpg", nav);

	SoundGame* digitSound = new SoundGame(window, digitPics, "DragGame.png", nav);
	SoundGame* figuresSound = new SoundGame(window, figuresPics, "figuresBG.png", nav);

	std::vector<Image> buttons;
	Image a, a1, a2;

	buttons.push_back(a);
	buttons.push_back(a1);
	buttons.push_back(a2);

	ColorSound* beta = new ColorSound(window, multiColorObjects, "DragGame.png", nav);
	FallingFigures* figuresFall = new FallingFigures(window, figuresPics, "DigitBg.jpg", nav);

	Sector* sec = new Sector(window,
		{ GameLevel1, digitSound, nullptr/*digitsFall */}, { Image(), Image(), Image() }, nav, "Digits");
	Sector* sec1 = new Sector(window, { figuresLevel, figuresSound , figuresFall }, buttons, nav, "Figures");

    ObjectFinder *omega = new ObjectFinder(window, digitPics, "none", nav);
	Sector* colors = new Sector(window, { nullptr, nullptr, nullptr }, { Image(),Image(), Image() }, nav, "Colors");

	//digitsFall->linkUp(sec->getStars()[2], sec->getName());
	figuresFall->linkUp(sec1->getStars()[2], sec1->getName());
	
	GameLevel1->linkUp(sec->getStars()[0][0], sec->getName());
	GameLevel2->linkUp(sec->getStars()[0][1], sec->getName());
	GameLevel3->linkUp(sec->getStars()[0][2], sec->getName());

	digitSound->linkUp(sec->getStars()[1], sec->getName());

	figuresLevel->linkUp(sec1->getStars()[0], sec->getName());
	figuresSound->linkUp(sec1->getStars()[1], sec->getName());

	//beta->linkUp(colors->getStars()[0], colors->getName());
	
	
	buttons.clear();

	GameLevel1->setSector(*sec);
	GameLevel2->setSector(*sec);
	GameLevel3->setSector(*sec);

	button.setPosition(100, 100);

	button.setSize(figuresButton.getSize());
	button.setPosition(width / 2 - button.getSize().x / 2, height / 2 - button.getSize().y / 2 - additionalSpace);

	digits.emplace_back(button, sec);
	digits.emplace_back(figuresButton, sec1);

	digits.emplace_back(button, digitSound);
	sf::RectangleShape foo(sf::Vector2f(width / 4, height / 4));
	foo.setPosition(0, 0);

	foo.setFillColor(sf::Color::Cyan);
	
	digits.emplace_back(foo, colors);
}
Singleton Singleton::obj;