#include "Paramedic.hpp"
#include "Board.hpp"
#include <iostream>

using namespace WarGame;

void Paramedic::action(WarGame::Board* board, std::pair<int,int> loc){ 
    std::vector<Soldier*> closefrnds = board->getAdjacentFriendlys(loc, player);
    for(std::vector<Soldier*>::iterator it = closefrnds.begin(); it != closefrnds.end(); it++){
        (*it)->restoreHealth();
    }
}

