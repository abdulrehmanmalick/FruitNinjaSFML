#include <iostream>
#include "Game.h"

using namespace std;


int main()
{
    //Init srand
    std::srand((time(NULL)));

    sf::Music music;
    music.openFromFile("music.ogg");
    music.play();

    //Game Engine
    Game game;

    //GameLoop
   


    while (game.running() && !game.getEndGame())
    {

        //update
        game.update();
        //render
        game.render();

      

      
    }
    //Application Ended

    return 0;
}