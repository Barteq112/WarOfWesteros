#ifndef GAME_H
#define GAME_H
#include "kingdom.h"
#include "map.h"

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
    Map* getMap() {return map;}
};

#endif // GAME_H
