#include "ParamedicCommander.hpp"
#include "Board.hpp"

using namespace WarGame;

void ParamedicCommander::action(WarGame::Board* board, std::pair<int,int> loc){ 
    Paramedic::action(board,loc);
    board->commandSubordinates(ti,player);
}
