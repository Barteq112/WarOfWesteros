#include "game.h"
#include "map.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>


void drawMap(Game *game)
{

    game->drawMap();
}

void moveUnit(Game* game)
{
    while (game->isGameEnded() == false)
    {
        game->autoMoveAttack();
    }
}

int main()
{

    Game* game = new Game();
    game->startGame();


    game->getKingdomSouth()->autoRun(game);
    game->getKingdomNorth()->autoRun(game);

    std::thread thread1(drawMap, game);
    std::thread thread2(moveUnit,game);

    thread1.join();

    std::cout<<"Koniec gry";





}
