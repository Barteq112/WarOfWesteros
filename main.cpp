#include "mainwindow.h"
#include "game.h"
#include "map.h"
#include <QApplication>
#include <iostream>
#include <SFML/Graphics.hpp>




int main(int argc, char *argv[])
{
    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    // return a.exec();







    Game* game = new Game();
    game->startGame();

    // testowe dodanie jednostek do armii północy i wyświetlenie ich
    game->getKingdomSouth()->buildBarracks(100,100);
    auto barracks = std::dynamic_pointer_cast<Barracks>(game->getKingdomSouth()->getBuildings().at(0));
    barracks->RecruitUnit(1,game);


    //Proste rysowanie mapy sfml do testowania budynek jeden kolor, jednostki drugi
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    auto mapa = game->getMap();

    while (window.isOpen())
    {
        // Obsługa zdarzeń
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Czyszczenie okna przed rysowaniem
        window.clear();


    for(int i=0;i<mapa->getMapWidth();i++)
    {
        for(int j=0;j<mapa->getMapHeight();j++)
        {
            if(mapa->getTile(i,j)->getBuilding()!=nullptr)
            {
                sf::RectangleShape rectangle(sf::Vector2f(1, 1));
                rectangle.setPosition(i,j);
                rectangle.setFillColor(sf::Color::Green);
                window.draw(rectangle);
            }
            if(mapa->getTile(i,j)->getUnit()!=nullptr)
            {
                sf::RectangleShape rectangle(sf::Vector2f(1, 1));
                rectangle.setPosition(i,j);
                rectangle.setFillColor(sf::Color::Red);
                window.draw(rectangle);
            }
        }
    }
    barracks->RecruitUnit(1,game);
    window.display();


    }
}

