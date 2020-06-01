#include "Board.hpp"
#include <iostream>
using namespace WarGame;


// helper functions

std::pair<int,int> Board::moveToCoordinate(std::pair<int,int> loc, MoveDIR move) const{
    if(move == MoveDIR::Up){
        return {loc.first+1, loc.second};
    }
    else if(move == MoveDIR::Down){
        return {loc.first-1, loc.second};
    }
    else if(move == MoveDIR::Left){
        return {loc.first, loc.second-1};
    }
    else{ //(move == MoveDIR::Right)
        return {loc.first, loc.second+1};
    }
}

int Board::getDistance(std::pair<int,int> s1, std::pair<int,int> s2) const{
    return (std::abs(s1.first-s2.first) + std::abs(s1.second-s2.second));
}


bool Board::insideBoard(std::pair<int,int> location) const{
    // check negativity
    if(location.first<0 || location.second<0){
        return false;
    }
    // check if outside
    std::pair<int,int> size = getBoardSize();
    //std::cout<<location.first<<","<<location.second<<std::endl;
    if(location.first >= size.first || location.second >= size.second){
        return false;
    }
    else{
        return true;
    }

}

// functions used by game

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


void Board::move(uint player_number, std::pair<int,int> source, MoveDIR direction){
    // check if inside board and if no soldier in destination
    std::pair<int,int> dest = moveToCoordinate(source, direction);
    if(!insideBoard(dest)){
        throw std::invalid_argument("You cannot move outside board!");
    }
    if(!insideBoard(source)){
        throw std::invalid_argument("The square you are trying to move to is outside the board!");
    }
    else if((*this)[dest] != nullptr){
        throw std::invalid_argument("The square you are trying to move to is occupied!");
    }
    else if((*this)[source] == nullptr){
        throw std::invalid_argument("You have no soldier in the given coordinate!");
    }
    else if((*this)[source]->getOwner()!=player_number){
        throw std::invalid_argument("You cannot move an enemy soldier!");
    }

    else{
        Soldier* s = (*this)[source]; 
        (*this)[source] = nullptr;
        (*this)[dest] = s;
        // takes board and location of soldier
        s->action(this, dest);
    }
}

bool Board::has_soldiers(uint player_number) const{
    std::pair<int,int> bSize = getBoardSize();
     for(int i = 0; i < bSize.first; i++){
        for(int j = 0; j < bSize.second; j++){
            if((*this)[{i,j}] != nullptr 
               &&  (*this)[{i,j}]->getOwner() == player_number){
                return true;
            }
        }
     }
    return false;
}

// functions used by soldiers

void Board::commandSubordinates(const std::type_info& type, int player){
    std::pair<int,int> bSize = getBoardSize();
    Soldier* s;
    // go over all board, activate only matching soldiers
     for(int i = 0; i < bSize.first; i++){
        for(int j = 0; j < bSize.second; j++){
            std::pair<int,int> currentSquare= {i, j};
            s = (*this)[currentSquare];
            //std::cout<<type.name()<<","<<typeid(s).name()<<std::endl;
            if(s != nullptr && s->getOwner() == player && typeid((*s)) == type){
                s->action(this, currentSquare);
            }
        }
     }
}


Soldier* Board::getClosestEnemySoldier(std::pair<int,int> location, int player) const{
    Soldier* closestEnemySoldier = nullptr;

    std::pair<int,int> bSize = getBoardSize();
    Soldier* s;
    double minDist = __DBL_MAX__;
    double dist;
    // go over whole board and save closest enemy sldier
    for(int i = 0; i < bSize.first; i++){
        for(int j = 0; j < bSize.second; j++){
            s = (*this)[{i,j}];
            if(s != nullptr && s->getOwner() != player){
                dist = getDistance({i,j}, location);
                if(dist<minDist){
                    minDist = dist;
                    closestEnemySoldier = s;
                }
            }
        }
    }
    // if no enemy soldiers found return nullptr
    return closestEnemySoldier;
}

Soldier* Board::getHighestHPEnemySoldier(std::pair<int,int> location, int player) const{
    Soldier* highestHPSoldier = nullptr;
    std::pair<int,int> bSize = getBoardSize();
    Soldier* s;
    double highestHP = -1;
    // go over whole board and save closest enemy sldier
    for(int i = 0; i < bSize.first; i++){
        for(int j = 0; j < bSize.second; j++){
            s = (*this)[{i,j}];
            if(s != nullptr && s->getOwner() != player){
                if(s->getHealth() >highestHP){
                    highestHP = s->getHealth();
                    highestHPSoldier = s;
                }
            }
        }
    }
    // if no enemy soldiers found return nullptr
    return highestHPSoldier;

}

std::vector<Soldier*> Board::getAdjacentFriendlys(std::pair<int,int> location, int player) const{
    std::vector<Soldier*> closefrnds = std::vector<Soldier*>();
    int x = location.first, y = location.second;
    // these are coordinates adjacent to 'location'
    std::pair<int,int> coords[8] = {{x+1,y+1}, {x+1,y}, {x+1,y-1}, {x,y-1},{x-1,y-1},{x-1,y},{x-1,y+1},{x,y+1}};
    for(int i=0; i<8; ++i){
        //is coordinate inside board and is friendly soldier
        if(insideBoard(coords[i]) && (*this)[coords[i]] != nullptr
            && (*this)[coords[i]]->getOwner() == player){
            closefrnds.push_back((*this)[coords[i]]);
        }
    }
    return closefrnds;
}

