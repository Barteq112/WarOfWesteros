#include "mainwindow.h"
#include "game.h"
#include "map.h"
#include <QApplication>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>

const int TILE_SIZE = 10; // Rozmiar jednej płytki w pikselach
void drawMap(Map* mapa)
{
    // Obliczenie rozmiarów okna na podstawie rozmiaru mapy

    int windowWidth = mapa->getMapWidth() * TILE_SIZE;
    int windowHeight = mapa->getMapHeight() * TILE_SIZE;

    // Tworzenie okna SFML
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML works!");
    // Create a view with the same size as the window
    sf::View view = window.getDefaultView();

    // Flip the y-axis by scaling it by -1 and adjusting the center
    view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
    view.setSize(view.getSize().x, -view.getSize().y);
    window.setView(view);


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
    }
}

void moveUnit(Game* game)
{
    while (true)
    {
        game->autoMoveAttack();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

int main(int argc, char *argv[])
{
    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    // return a.exec();
    Game* game = new Game();
    game->startGame();

    // testowe dodanie jednostek do armii południa i wyświetlenie ich
    game->getKingdomSouth()->buildBarracks(10, 10);
    auto barracks = std::dynamic_pointer_cast<Barracks>(game->getKingdomSouth()->getBuildings().at(1));
    barracks->RecruitUnit(1, game);
    auto unit = game->getKingdomSouth()->getArmy().getUnits().at(0);
    std::cout << unit->getHealth() << std::endl;
    auto mapa = game->getMap();




    std::thread thread1(drawMap, mapa);
    std::thread thread2(moveUnit,game);

    while (true)
    {
        //Podajesz współrzędne i zmienia się kierunek
        int x, y;
        std::cout<<"Podaj x: ";
        std::cin >> x;
        std::cout<<"\nPodaj y: ";
        std::cin>> y;
        unit->setDestination(x,y);
    }








    thread1.join();

    //prosty interfejst do sterowania unit w konsoli




}
