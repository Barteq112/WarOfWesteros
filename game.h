#ifndef GAME_H
#define GAME_H
#include "kingdom.h"
#include "map.h"

//Indeksy dla poszczególnych królestw 0 - South, 1 - North, 2 - BeyondTheWall
//Indeksy poszczególnych budnynków 0 - MainCastle, 1 - Barracks, 2 - House
//Inedksy poszczególnych jednostek 0 - Giant, 1 - Infantry, 2 - Archer, 3 - Cavalry, 4 - Magician, 5 - Wolf, 6 - HeavyKnight


class Game
{
private:
    Kingdom* KingdomNorth;
    Kingdom* KingdomSouth;
    Kingdom* KingdomBeyondTheWall;
    Map* map;
public:
    Game();
    void startGame();
    void endGame();
    bool isGameEnded();
    void autoMoveAttack();
    void setKingdomNorth(Kingdom* kingdom) {KingdomNorth = kingdom;}
    void setKingdomSouth(Kingdom* kingdom) {KingdomSouth = kingdom;}
    void setKingdomBeyondTheWall(Kingdom* kingdom) {KingdomBeyondTheWall = kingdom;}
    Map* getMap() {return map;}
    Kingdom* getKingdomNorth() {return KingdomNorth;}
    Kingdom* getKingdomSouth() {return KingdomSouth;}
    Kingdom* getKingdomBeyondTheWall() {return KingdomBeyondTheWall;}
};

#endif // GAME_H
