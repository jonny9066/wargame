#include "SniperCommander.hpp"
#include "Board.hpp"

using namespace WarGame;

void SniperCommander::action(Board* board, std::pair<int,int> loc){ 
    Sniper::action(board, loc);
    board->commandSubordinates(ti, player);
}
