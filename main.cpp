#include "mainwindow.h"
#include "game.h"
#include "map.h"
#include <QApplication>
#include <iostream>
#include <SFML/Graphics.hpp>

const int TILE_SIZE = 10; // Rozmiar jednej płytki w pikselach

int main(int argc, char *argv[])
{
    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    // return a.exec();
    Game* game = new Game();
    game->startGame();

    // testowe dodanie jednostek do armii południa i wyświetlenie ich
    game->getKingdomSouth()->buildBarracks(0, 0);
    game->getKingdomNorth()->buildHouse(45,44);
    auto barracks = std::dynamic_pointer_cast<Barracks>(game->getKingdomSouth()->getBuildings().at(0));
    barracks->RecruitUnit(1, game);
    auto unit = game->getKingdomSouth()->getArmy().getUnits().at(0);
    std::cout << unit->getHealth() << std::endl;


    // Obliczenie rozmiarów okna na podstawie rozmiaru mapy
    auto mapa = game->getMap();
    int windowWidth = mapa->getMapWidth() * TILE_SIZE;
    int windowHeight = mapa->getMapHeight() * TILE_SIZE;

    // Tworzenie okna SFML
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML works!");

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

        for (int i = 0; i < mapa->getMapWidth(); i++)
        {
            for (int j = 0; j < mapa->getMapHeight(); j++)
            {
                if (mapa->getTile(i, j)->getBuilding() != nullptr)
                {
                    sf::RectangleShape rectangle(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                    rectangle.setPosition(i * TILE_SIZE, j * TILE_SIZE);
                    rectangle.setFillColor(sf::Color::Green);
                    window.draw(rectangle);
                }
                if (mapa->getTile(i, j)->getUnit() != nullptr)
                {
                    sf::RectangleShape rectangle(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                    rectangle.setPosition(i * TILE_SIZE, j * TILE_SIZE);
                    rectangle.setFillColor(sf::Color::Red);
                    window.draw(rectangle);
                }
            }
        }
        window.display();
        //opóźnienie 1s
        sf::sleep(sf::seconds(0.2));
        unit->move(game->getMap(), 50, 50);
    }
}
