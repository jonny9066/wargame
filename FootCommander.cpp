#include "FootCommander.hpp"
#include "Board.hpp"

using namespace WarGame;

void FootCommander::action(Board board){ 
    Soldier* closestEnemy = board.getClosestEnemySoldier({1,2}, this->getOwner());
    closestEnemy->receiveDamage(this->getDamage());
}
