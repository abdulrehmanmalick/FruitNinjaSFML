#include "Game.h"
#include <string>

//Private
void Game::setTexture()
{
    this->background.loadFromFile("back.png"); //Loads the Background image
}

void Game::setSprite()
{
    this->myBg.setTexture(this->background);
}

void Game::initVariables()
{
    this->window = nullptr;

    //Game Logic
    this->endGame = false;
    this->points = 0;
    this->health = 10;
    //this->enemySpawnTimer = 0.f;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax; //To Spawn enemies directly. Timer will start from max and go to 0
    this->maxEnemies = 10;
    this->mouseHeld = false;

}

void Game::initWindow()
{
    this->vidMode.width = 800;
    this->vidMode.height = 600;
    this->window = new sf::RenderWindow(this->vidMode, "Fruit Ninja 2.0", sf::Style::Default); //Default has everything like border(TitleBar),resize.
    this->myText.setPosition(100, 500);
    this->myFont.loadFromFile("font.otf");
    this->myFontLevel1.loadFromFile("font.otf");
    this->myFontLevel2.loadFromFile("font.otf");
    this->myFontLevel3.loadFromFile("font.otf");
    this->myText.setFont(this->myFont);
    this->myTextLevel1.setFont(this->myFont);
    this->myTextLevel2.setFont(this->myFont);
    this->myTextLevel3.setFont(this->myFont);
    this->lifeText.setFont(this->myFont);

    

    this->window->setFramerateLimit(60); //Sets the Frame Rate. One should set it according to the Screen he/she is using.
}

void Game::initEnemies()
{
    this->enemy.setPosition(0.f, 0.f);
    this->enemy.setSize(sf::Vector2f(50.f, 50.f)); //.f signifies Float value. Vector2f is taken as a parameter here.
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f)); // To reduce or Increase the size without editing the size.
     //Fills Color inside the Shape.
    //this->enemy.setOutlineColor(sf::Color::Yellow); //Outline Color.
    //this->enemy.setOutlineThickness(1.f); //Gives outline thickness so that we can see it.


}


//Constructor & Destructor
Game::Game()

{
    this->setEnemytexture();
    this->initVariables();
    this->initWindow();
    this->initEnemies();
   

}

Game::~Game()
{
    delete this->window; //To Prevent Memory Leakage
 

        this->gameover();
       
  
}

const bool Game::running() const
{
    return this->window->isOpen();
}

const bool Game::getEndGame() const
{
    return this->endGame;
}

//Functions
void Game::spawnEnemy()
{
    /*
     returns void

     Spawns Enemies and sets their colors and positions.
     Sets a random position.
     Sets a random color.
     Adds enemy to the vector.

    */
    /*
    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y))

    );
    */

    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        0.f);


    int random = rand() % 3 + 1;
    std::cout << random;

    switch (random)
    {
    case 1:
        this->enemy.setTexture(&fruitsKela);
        break;

    case 2:
        this->enemy.setTexture(&fruitsSeb);
        break;

    case 3:
        this->enemy.setTexture(&fruitsTarbooz);
        break;
    }
    random = 0;

    //Spawn The Enemy
    this->enemies.push_back(this->enemy);


}

void Game::pollEvents()
{

    while (this->window->pollEvent(this->evnt))
    {
        switch (this->evnt.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;

        case sf::Event::KeyPressed:
            if (this->evnt.key.code == sf::Keyboard::Escape ) //Will End the Program.
            {
                this->window->close();
                break;
            }
        }
    }
}

void Game::updateMousePositions()
{
    //return void. Updates the mouse positions.
    //Update Relative to window (vector2i)

    this->myMousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->myMousePosWindow);

}


void Game::updateEnemies()
/*
    returns void

    Updates the Enemy Spawn Timer
    Spawn Enemies when the total amount of enemies is smaller than the maximum.
    Moves the enemy downwards
    Removes the Enemy at the edge of the screen

*/
{
    //Updating the timer for enemy spawning
    if (this->enemies.size() < this->maxEnemies)
    {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            //Spawn the Enemy and reset the timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else
        {
            this->enemySpawnTimer += 1.f;
        }
    }

    //Move and updating the Enemies
    for (int i = 0; i < this->enemies.size(); i++)
    {
        bool deleted = false;

        this->enemies[i].move(0.f, 0.5f); //U can increase or decrease the speed      

        if ((this->enemies[i].getPosition().y) > (this->window->getSize().y))
        {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
            std::cout << "Health: " << this->health << "\n";


        }


        if (this->points >= 10)
        {
            this->maxEnemies = 20;
            this->enemies[i].move(0.f, 0.8f);
        }

        if (this->points >= 40)
        {
            this->maxEnemies = 20;
            this->enemies[i].move(0.f, 1.f);
        }


    }

    //Check if clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (this->mouseHeld == false)
        {
            this->mouseHeld = true;
            bool deleted = false;

            for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
            {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
                {
                    //Delete the enemy
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);

                    //Gain Points
                    this->points += 1;

                    std::cout << "Points: " << this->points << "\n";
                }
            }
        }
        else
        {
            this->mouseHeld = false;
        }
    }
}


void Game::update()
{
    //EventPolling
    this->pollEvents();

    //EndGame
    if (this->endGame == false)
    {
        //Updating Mouse Position
        this->updateMousePositions();
        //Updating Enemies
        this->updateEnemies();
    }

    //Condition for End Game
    if (this->health <= 0)
    {
        this->endGame = true;
       
       
        
    }
}




void Game::initFonts()
{
    //std::cout << "Health: " << this->health << "\n";
    this->life = std::to_string(this->health);
    this->myText.setString("Score : " + this->score);



    //std::cout << "Points: " << this->points << "\n";
    this->score = std::to_string(this->points);
    this->myText.setString("Score : " + this->score);


    this->lifeText.setString("Health : " + this->life);
    this->lifeText.setPosition(100, 550);
    this->lifeText.setCharacterSize(30);
    this->life = health;

    if (this->points < 10)
    {
        this->myTextLevel2.setPosition(0, 0);
        this->myTextLevel2.setString("Level 1");
    }

    if (this->points >= 10)
    {

        this->myTextLevel2.setPosition(0, 0);
        this->myTextLevel2.setString("Level 2");

        //this->myText.setPosition(100, 500);
        //his->myText.setString("Score : " + this->score);  
    }

    if (this->points >= 40)
    {
        this->myTextLevel2.setPosition(0, 0);
        this->myTextLevel2.setString("Level 3");

        this->myText.setPosition(100, 500);
        //this->myText.setString("Score : " + this->score);
    }

}


void Game::renderEnemies()
{
    //Rendering all the enemies
    for (auto& e : this->enemies)
    {
        this->window->draw(e);
    }
}

void Game::render()
{
    /*
            returns nothing.
       -clear old frame
       -render objects
       -display frame in window

     Renders the Game Objects.
    */
    this->window->clear(sf::Color::Black);

    //Draw Game Objects
    this->window->draw(myBg);
    this->renderEnemies();
    this->setTexture();
    this->initFonts();
    this->setSprite();
    this->window->draw(myText);
    this->window->draw(myTextLevel1);
    this->window->draw(myTextLevel2);
    this->window->draw(myTextLevel3);
    this->window->draw(lifeText);


    this->window->display();
}
