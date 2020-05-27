#include "Board.hpp"
using namespace WarGame;


bool Board::insideBoard(std::pair<int,int> location) const{
    // check negativity
    if(location.first<0 || location.second<0){
        return false;
    }
    // check if outside
    std::pair<int,int> size = getBoardSize();
    if(location.first >= size.first || location.second >= size.second){
        return false;
    }
    else{
        return true;
    }

}

Soldier*& Board::operator[](std::pair<int,int> location){
    if(!insideBoard(location)){
        throw std::invalid_argument("bad coordinates!");
    }
    
    Soldier** sldr = &(board.at(location.first).at(location.second));
    /* //impossible to delete this way
    if(*sldr != nullptr){
        throw std::invalid_argument("An occupied square cannot be modified!");
    }
    */
    return *sldr;
}  
Soldier* Board::operator[](std::pair<int,int> location) const{
    if(!insideBoard(location)){
        throw std::invalid_argument("bad coordinates!");
    }
    return board.at(location.first).at(location.second);
}

Soldier* Board::getClosestEnemySoldier(std::pair<int,int> location, int player) const{
    std::pair<int,int> size = getBoardSize();
    //i is radius from location -1, radius is length of board (inefficient)
    for(int i = 0; i< size.first; i++){
        // top left, top right, bottom right, bottom left
        std::pair<int,int> diags[] = {{location.first-i-1, location.second+i+1},
        {location.first+i+1, location.second+i+1},{location.first+i+1, location.second-i-1},
        {location.first-i-1, location.second-i-1}};
        // right, down, left, up
        std::pair<int,int> steps[] = {{1,0},{0,-1}, {-1,0}, {0,1}};
        
        
        // go over each edge of the square in radius i
        for(int i=0; i<4; i++){
            std::pair<int,int> csquare = diags[i];
            // go over edge until reaching next diagonal
            while(csquare != diags[(i+1)%4]){
                if(insideBoard(csquare)){
                    Soldier* csoldier = (*this)[csquare];
                    // check if square is occupied by enemy
                    if(csoldier != nullptr && csoldier->getOwner() != player){
                        return csoldier;
                    }
                    else{
                        // take step
                        csquare = {csquare.first+steps[i].first, csquare.second+steps[i].second};
                    }
                }
                
            }
        }

    }
    // if no enemy soldiers found return nullptr
    return nullptr;
}

void Board::move(uint player_number, std::pair<int,int> source, MoveDIR direction){
    
}

bool Board::has_soldiers(uint player_number) const{
    return false;
}