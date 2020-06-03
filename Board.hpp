/**
 * Header file for the board of the war game.
 * 
 * You can copy this file to a new file called Board.hpp, and extend it as you like. -already copied
 * 
 * @author Oz Levi 
 * @author Erel Segal-Halevi
 * @since  2020-05
 */

#include <string>
#include <vector>
#include <stdexcept>
#include "Soldier.hpp"

#pragma once


namespace WarGame {

class Board {
  private:
  //a matrix of Soldier pointers
    std::vector<std::vector<Soldier*>> board;
    //returs true if given location is inside board
    bool insideBoard(std::pair<int,int> location) const;

    std::pair<int,int> getBoardSize() const{
      return {board.capacity(),board.at(0).capacity()};}
    
    //gets number of moves required to get from s1 to s2
    int getDistance(std::pair<int,int> s1, std::pair<int,int> s2) const;

  public:
    enum MoveDIR { Up, Down, Right, Left };
  private:
    std::pair<int,int> moveToCoordinate(std::pair<int,int> loc, MoveDIR move) const;

  public:

    //constructs a vector of vectors with null pointers to Soldier
    Board(uint numRows, uint numCols) : 
      board(numRows, std::vector<Soldier*>(numCols, nullptr)) {}
    

    // operator for putting soldiers on the game-board during initialization.
    Soldier*& operator[](std::pair<int,int> location);

    // operator for getting soldier in given location
    Soldier* operator[](std::pair<int,int> location) const;
    // returns pointer to closest enemy soldier or null pointer in there are no enemies
    std::pair<int,int> getClosestEnemyLocation(std::pair<int,int> location, int player) const;
    std::pair<int,int> getHighestHPEnemyLocation(std::pair<int,int> location, int player) const;
    std::vector<Soldier*> getAdjacentFriendlys(std::pair<int,int> location, int player)const;
    //commands all soldiers of type ti to act (i.e. shoot or heal)
    void commandSubordinates(const std::type_info& ti, int player);



    // The function "move" tries to move the soldier of player "player"
    //     from the "source" location to the "target" location,
    //     and activates the special ability of the soldier.
    // If the move is illegal, it throws "std::invalid_argument". 
    // Illegal moves include:
    //  * There is no soldier in the source location (i.e., the soldier pointer is null);
    //  * The soldier in the source location belongs to the other player.
    //  * There is already another soldier (of this or the other player) in the target location.
    // IMPLEMENTATION HINT: Do not write "if" conditions that depend on the type of soldier!
    // Your code should be generic. All handling of different types of soldiers 
    //      must be handled by polymorphism.
    void move(uint player_number, std::pair<int,int> source, MoveDIR direction);

    // returns true iff the board contains one or more soldiers of the given player.
    bool has_soldiers(uint player_number) const;
};

}