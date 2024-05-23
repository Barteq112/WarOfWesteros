#ifndef RESOURCES_H
#define RESOURCES_H

class Resources
{
private:
    int gold;
    int population;
public:
    Resources(int initGold, int initPopulation);
    int getGold() {return gold;}
    int getPopulation() {return population;}
    void increaseGold(int gold) {this->gold += gold;}
    void increasePopulation(int population) {this->population += population;}
    void decreaseGold(int gold) {this->gold -= gold;}
    void decreasePopulation(int population) {this->population -= population;}
};

#endif // RESOURCES_H
