#include "FootCommander.hpp"
#include "Board.hpp"

using namespace WarGame;

void FootCommander::action(WarGame::Board* board, std::pair<int,int> loc){ 
    // foot commander shoots like regular soldier
    FootSoldier::action(board, loc);
    board->commandSubordinates(ti, player);
    //command(board, this->getOwner());
}
