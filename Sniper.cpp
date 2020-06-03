#include "Sniper.hpp"
#include "Board.hpp"


void Sniper::action(WarGame::Board* board, std::pair<int,int> loc){ 
    std::pair<int,int> enemyLoc = board->getHighestHPEnemyLocation(loc, this->getOwner());
    if(enemyLoc != std::pair{-1,-1}){
        // attack enenmy and check if he was killed
        if(  ((*board)[enemyLoc]->receiveDamage(this->getDamage()))  <=0  ){
            (*board)[enemyLoc] = nullptr;
        }
    }
}
