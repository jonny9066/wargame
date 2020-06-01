#include "FootSoldier.hpp"
#include "Board.hpp"

using namespace WarGame;

void FootSoldier::action(Board* board, std::pair<int,int> loc){ 
    Soldier* closestEnemy = board->getClosestEnemySoldier(loc, this->getOwner());
    if(closestEnemy != nullptr){
        closestEnemy->receiveDamage(this->getDamage());
    }
}
