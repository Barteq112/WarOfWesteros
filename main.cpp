#include "mainwindow.h"
#include "game.h"
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
    game->getKingdomNorth()->getArmy().addUnitToList(std::make_shared<Infantry>());
    game->getKingdomNorth()->getArmy().addUnitToList(std::make_shared<Cavalry>());

    // Kod SFML do wyświetlania okna
    sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML Test Window");

    // Utwórz prostokąt
    sf::RectangleShape rectangle(sf::Vector2f(9.f, 9.f));
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setPosition(350.f, 275.f);

    // Pętla główna SFML
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(rectangle);
        window.display();
    }

    return 0;
}
