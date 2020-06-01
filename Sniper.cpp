#include "Sniper.hpp"
#include "Board.hpp"

using namespace WarGame;

void Sniper::action(Board* board, std::pair<int,int> loc){ 
    Soldier* enemy = board->getHighestHPEnemySoldier(loc, this->getOwner());
    if(enemy != nullptr){
        enemy->receiveDamage(this->getDamage());
    }
}
