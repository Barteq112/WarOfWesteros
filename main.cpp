#include "mainwindow.h"
#include "map.h"
#include "game.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    // return a.exec();

    Game* game = new Game();
    game->startGame();
    // testowe dodanie jedneostek do armii północy i wyświetlenie ich
    // testowe dodanie jednostek do armii północy i wyświetlenie ich
    game->getKingdomNorth()->getArmy().addUnitToList(std::make_shared<Infantry>(1));
    game->getKingdomNorth()->getArmy().addUnitToList(std::make_shared<Cavalry>(2));

    // Wyświetlenie jednostek armii północy
    for (auto unit : game->getKingdomNorth()->getArmy().getUnits())
    {
        std::cout << "Jednostka: " << unit->getID() << std::endl;

        // Sprawdzenie, czy jednostka jest typu Infantry
        if (auto infantryPtr = std::dynamic_pointer_cast<Infantry>(unit))
        {
            // Jeśli jednostka jest typu Infantry, możemy wykonać odpowiednie działania dla tego typu jednostki
            std::cout << "To jest jednostka typu Infantry" << std::endl;
            // Tutaj możesz dodać dodatkowe operacje dla jednostek typu Infantry
        }
    }
    game->endGame();



}
