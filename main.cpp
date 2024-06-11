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

    // testowe dodanie jednostek do armii południa i wyświetlenie ich
    // game->getKingdomSouth()->buildBarracks(10, 10);
    // auto barracks = std::dynamic_pointer_cast<Barracks>(game->getKingdomSouth()->getBuildings().at(1));
    // barracks->RecruitUnit(3, game);
    // auto unit = game->getKingdomSouth()->getArmy().getUnits().at(0);
    game->getKingdomSouth()->autoRun(game);
    game->getKingdomNorth()->autoRun(game);
    game->getKingdomBeyondTheWall()->autoRun(game);





    std::thread thread1(drawMap, game);
    std::thread thread2(moveUnit,game);

    // while (game->isGameEnded() == false)

    // {
    //     //Podajesz współrzędne i zmienia się kierunek
    //     int x, y;
    //     std::cout<<"Podaj x: ";
    //     std::cin >> x;
    //     std::cout<<"Podaj y: ";
    //     std::cin>> y;
    //     unit->setDestination(x,y);
    // }








    thread1.join();

    //prosty interfejst do sterowania unit w konsoli




}
