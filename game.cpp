#include "game.h"
#include <algorithm>
#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>

Game::Game() {
    //inicjalizacja królestw
    KingdomNorth = new Kingdom();
    KingdomSouth = new Kingdom();
    KingdomBeyondTheWall = new Kingdom();
    //inicjalizacja mapy
    map = new Map(100,50);
    KingdomSouth->setOwner(0);
    KingdomNorth->setOwner(1);
    KingdomBeyondTheWall->setOwner(2);
    KingdomSouth->setMap(this->map);
    KingdomNorth->setMap(this->map);
    KingdomBeyondTheWall->setMap(this->map);
}

void Game::endGame() {
    delete KingdomNorth;
    delete KingdomSouth;
    delete KingdomBeyondTheWall;
}

bool Game::isGameEnded()
{
    int c=0;
    if(KingdomBeyondTheWall == nullptr)
        c++;
    if(KingdomNorth == nullptr)
        c++;
    if(KingdomSouth == nullptr)
        c++;
    if(c>=2)
        return true;
    return false;
}


// 0 - South, 1 - North, 2 - BeyondTheWall
void Game::startGame() {
    //Podział mapy
    for(int i=0; i<map->getMapWidth(); i++) {
        for(int j=0; j<map->getMapHeight(); j++) {
            if(j<map->getMapHeight()/3) {
                map->getTile(i,j)->setOwner(0);
            } else if(j<2*map->getMapHeight()/3) {
                map->getTile(i,j)->setOwner(1);
            } else {
                map->getTile(i,j)->setOwner(2);
            }
        }
    }

    //Postawienie zamku głównego dla każdego królestwa
    KingdomSouth->buildMainCastle(1,1);
    KingdomNorth->buildMainCastle(map->getMapWidth()-4,map->getMapHeight()/2);
    KingdomBeyondTheWall->buildMainCastle(1,map->getMapHeight()-5);



}


void Game::autoMoveAttack()
{

    std::vector<std::shared_ptr<Unit>> allUnits;

    // Sprawdzenie, czy królestwa mają jednostki, zanim je dodamy do allUnits
    if(this->KingdomSouth != nullptr)
    {
        auto southUnits = getKingdomSouth()->getArmy().getUnits();
        if (!southUnits.empty()) {
            allUnits.insert(allUnits.end(), southUnits.begin(), southUnits.end());
        }
    }

    if(this->KingdomBeyondTheWall != nullptr)
    {
        auto beyondTheWallUnits = getKingdomBeyondTheWall()->getArmy().getUnits();
        if (!beyondTheWallUnits.empty()) {
            allUnits.insert(allUnits.end(), beyondTheWallUnits.begin(), beyondTheWallUnits.end());
        }
    }
    if(this->KingdomNorth != nullptr)
    {
        auto northUnits = getKingdomNorth()->getArmy().getUnits();
        if (!northUnits.empty()) {
            allUnits.insert(allUnits.end(), northUnits.begin(), northUnits.end());
        }
    }

    // Pobierz czas początkowy
    auto currentTime = std::chrono::system_clock::now();

    // Przemieszaj jednostki
    if(allUnits.size() > 1)
        std::random_shuffle(allUnits.begin(), allUnits.end());
    // Przejdź po liście i wykonaj ruch każdej jednostki
    for (auto unit : allUnits)
    {
        //Sprawdzenie czy jednostka jest w danym miejscu na mapie
        if (this->getMap()->getTile(unit->getX(),unit->getY())->getUnit() != unit)
        {
            continue;
        }


        if (unit->inMotion() && std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - unit->getLastMoveTime()).count() >3000/unit->getSpeed())
        {
            unit->move(this->getMap());
            unit->setLastMoveTime();
        }

        if(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - unit->getLastAttackTime()).count() >2000/unit->getAttackSpeed())
        {
            unit->attack(this);
            unit->setLastAttackTime();
        }

    }
}



const int TILE_SIZE = 20;

void Game::drawMap()
{
    auto mapa = getMap();
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

        // Czyszczenie okna przed rysowaniem i ustawienie tła na białe
        window.clear(sf::Color::White);

        // Pobranie wszystkich jednostek i budynków
        std::vector<std::shared_ptr<Unit>> allUnits;

        if (this->KingdomSouth != nullptr)
        {
            auto southUnits = getKingdomSouth()->getArmy().getUnits();
            if (!southUnits.empty())
            {
                allUnits.insert(allUnits.end(), southUnits.begin(), southUnits.end());
            }
        }

        if (this->KingdomBeyondTheWall != nullptr)
        {
            auto beyondTheWallUnits = getKingdomBeyondTheWall()->getArmy().getUnits();
            if (!beyondTheWallUnits.empty())
            {
                allUnits.insert(allUnits.end(), beyondTheWallUnits.begin(), beyondTheWallUnits.end());
            }
        }

        if (this->KingdomNorth != nullptr)
        {
            auto northUnits = getKingdomNorth()->getArmy().getUnits();
            if (!northUnits.empty())
            {
                allUnits.insert(allUnits.end(), northUnits.begin(), northUnits.end());
            }
        }

        std::vector<std::shared_ptr<Building>> allBuildings;

        if (this->KingdomSouth != nullptr)
        {
            auto southBuildings = getKingdomSouth()->getBuildings();
            if (!southBuildings.empty())
            {
                allBuildings.insert(allBuildings.end(), southBuildings.begin(), southBuildings.end());
            }
        }

        if (this->KingdomBeyondTheWall != nullptr)
        {
            auto beyondTheWallBuildings = getKingdomBeyondTheWall()->getBuildings();
            if (!beyondTheWallBuildings.empty())
            {
                allBuildings.insert(allBuildings.end(), beyondTheWallBuildings.begin(), beyondTheWallBuildings.end());
            }
        }

        if (this->KingdomNorth != nullptr)
        {
            auto northBuildings = getKingdomNorth()->getBuildings();
            if (!northBuildings.empty())
            {
                allBuildings.insert(allBuildings.end(), northBuildings.begin(), northBuildings.end());
            }
        }

        // Mapowanie typów jednostek i budynków na nazwy plików
        std::map<int, std::string> unitTypeMap = {
            {0, "giant"},
            {1, "infantry"},
            {2, "archer"},
            {3, "cavalry"},
            {4, "magician"},
            {5, "wolf"},
            {6, "heavyknight"}
        };

        std::map<int, std::string> buildingTypeMap = {
            {0, "castle"},
            {1, "barracks"},
            {2, "house"}
        };

        // Rysowanie wszystkich jednostek
        for (const auto& unit : allUnits)
        {
            sf::Texture unitTexture;
            std::string path;

            // Ustalanie ścieżki na podstawie królestwa
            if (unit->getOwner() == 0)
            {
                path = "sprites/south/";
            }
            else if (unit->getOwner() == 1)
            {
                path = "sprites/north/";
            }
            else if (unit->getOwner() == 2)
            {
                path = "sprites/beyondthewall/";
            }

            // Dodanie nazwy pliku na podstawie typu jednostki
            path += unitTypeMap[unit->getType()] + ".png";

            if (!unitTexture.loadFromFile(path))
            {
                // Error handling
                continue;
            }

            sf::Sprite sprite;
            sprite.setTexture(unitTexture);
            // Ustawienie pozycji z uwzględnieniem przesunięcia od dolnego lewego rogu
            sprite.setPosition(unit->getX() * TILE_SIZE, unit->getY() * TILE_SIZE);
            sprite.setScale(TILE_SIZE / (float)unitTexture.getSize().x, TILE_SIZE / (float)unitTexture.getSize().y);

            //sprite.setRotation(180); // Obrót o 180 stopni
            window.draw(sprite);
        }

        // Rysowanie wszystkich budynków
        for (const auto& building : allBuildings)
        {
            sf::Texture buildingTexture;
            std::string path;

            // Ustalanie ścieżki na podstawie królestwa
            if (building->getOwner() == 0)
            {
                path = "sprites/south/";
            }
            else if (building->getOwner() == 1)
            {
                path = "sprites/north/";
            }
            else if (building->getOwner() == 2)
            {
                path = "sprites/beyondthewall/";
            }

            // Dodanie nazwy pliku na podstawie typu budynku
            path += buildingTypeMap[building->getType()] + ".png";

            if (!buildingTexture.loadFromFile(path))
            {
                // Error handling
                continue;
            }

            sf::Sprite sprite;
            sprite.setTexture(buildingTexture);
            sprite.setScale((building->getSizex() * TILE_SIZE) / (float)buildingTexture.getSize().x, (building->getSizey() * TILE_SIZE) / (float)buildingTexture.getSize().y);

            // Ustawienie pozycji z uwzględnieniem przesunięcia od dolnego lewego rogu i wysokości budynku
            sprite.setPosition(building->getX() * TILE_SIZE, building->getY() * TILE_SIZE);

            window.draw(sprite);
        }

        window.display();
    }
}






