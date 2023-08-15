#pragma once
#pragma once

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>



/*Class that acts as a game engine*/


class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* window;
	sf::Event evnt;
	sf::VideoMode vidMode;

	//Mouse Position
	sf::Vector2i myMousePosWindow;
	sf::Vector2f mousePosView;

	//Resources

	//Fonts
	sf::Font font;



	//Game Logic
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;


	//Game Objects
	std::string score;
	std::string life;
	sf::Sprite myBg;
	sf::Texture background;
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;
	sf::Texture fruitsSeb;
	sf::Texture fruitsTarbooz;
	sf::Texture fruitsKela;

	sf::Font myFont;
	sf::Font myFontLevel1;
	sf::Font myFontLevel2;
	sf::Font myFontLevel3;
	sf::Text myTextlife;
	sf::Text myText;
	sf::Text myTextLevel1;
	sf::Text myTextLevel2;
	sf::Text myTextLevel3;
	sf::Text lifeText;



	void initVariables();//To Initialise variables
	void initWindow(); // to initialise windows
	void initFonts(); //To introduce forms
	void initEnemies(); //to insialise Enemies
	void setTexture();//Setting Texture
	void setSprite();
	void setEnemytexture()
	{
		fruitsKela.loadFromFile("kela.png");
		fruitsSeb.loadFromFile("seb.png");
		fruitsTarbooz.loadFromFile("tarbooz.png");
	}

	


public:

	void gameover() {
		sf::RenderWindow window1(sf::VideoMode(800, 600), "Fruit Ninja", sf::Style::Close);
		sf::Clock delay;
		float time;
		sf::Time t;


		sf::RectangleShape background(sf::Vector2f(800, 600));
		sf::Texture bg;
		bg.loadFromFile("back.png");
		sf::Text gameOver;
		sf::Font myFont;
		background.setTexture(&bg);
		myFont.loadFromFile("font.otf");
		gameOver.setFont(myFont);
		gameOver.setString(" GAME OVER ");
		gameOver.setCharacterSize(100);
		gameOver.setPosition(50, 250);

		while (window1.isOpen())
		{
			sf::Event evnt;
			while (window1.pollEvent(evnt))
			{
				switch (evnt.type)
				{
				case sf::Event::Closed:
					window1.close();
				}

			}

			t = delay.getElapsedTime();
			time = t.asMilliseconds();
			std::cout <<time  << std::endl;
			if (time >= 5000)
			{
				window1.close();
			}


			window1.clear();
			window1.draw(background);
			window1.draw(gameOver);
			window1.display();
		}
	}




	//Constructor and Destructor
	Game(); //Constructor
	virtual ~Game(); //Destructor

	//Accessors
	const bool running() const;
	const bool getEndGame() const;



	//Functions
	void spawnEnemy();

	void pollEvents();

	void updateMousePositions(); //To update Mouse Position
	void updateEnemies();
	void update(); // To update the games



	void renderEnemies();
	void render(); // To render and adjust the game

};


