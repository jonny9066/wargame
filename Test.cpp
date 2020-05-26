#include "doctest.h"
#include "Board.hpp"
#include "FootSoldier.hpp"
#include "FootCommander.hpp"
#include "Sniper.hpp"
#include "SniperCommander.hpp"
#include "Paramedic.hpp"
#include "ParamedicCommander.hpp"

using namespace WarGame;

TEST_CASE("Test board creation"){
	Board b = Board(4,4);
    CHECK(b[{0,0}] == nullptr);
    CHECK(b[{0,1}] == nullptr);
    CHECK(b[{1,0}] == nullptr);
    CHECK(b[{1,1}] == nullptr);
}

TEST_CASE("Test board out of bounds"){
	Board b = Board(4,4);
    CHECK_THROWS( (b[{-1,0}]) );
    CHECK_THROWS( (b[{0,5}]) );
    CHECK_THROWS( (b[{4,4}]) );
    CHECK_THROWS( (b[{1,-1}]) );
}

TEST_CASE("Test board addittion"){
	Board b = Board(4,4);
    Soldier* s1 = new FootSoldier(1);
    Soldier* s2 = new FootSoldier(1);
    Soldier* s3 = new FootSoldier(2);
    Soldier* s4 = new FootSoldier(2);

    b[{0,0}] = s1;
    b[{0,3}] = s2;
    b[{0,2}] = s3;
    b[{1,1}] = s4;

    CHECK(b[{0,0}] == s1);
    CHECK(b[{0,3}] == s2);
    CHECK(b[{0,2}] == s3);
    CHECK(b[{1,1}] == s4);
    
}

TEST_CASE("Test addittion in occupied spot"){
	Board b = Board(4,4);
    Soldier* s1 = new FootSoldier(1);
    Soldier* s2 = new FootSoldier(1);
    Soldier* s3 = new FootSoldier(2);
    Soldier* s4 = new FootSoldier(2);

    b[{0,0}] = s1;
    CHECK_THROWS( (b[{0,0}] = s2));
    CHECK_THROWS( (b[{0,0}] = s3));
    b[{2,3}] = s3;
    CHECK_THROWS( (b[{0,0}] = s4));
    
}

TEST_CASE("Test adding same soldier in several places"){
	Board b = Board(4,4);
    Soldier* s1 = new FootSoldier(1);
    Soldier* s2 = new FootSoldier(2);

    b[{0,0}] = s1;
    CHECK_THROWS( (b[{2,2}] = s1));
    b[{0,1}] = s2;
    CHECK_THROWS( (b[{2,3}] = s2));
}
TEST_CASE("Test moving"){
	Board b = Board(4,4);
    Soldier* s1 = new FootSoldier(1);
    Soldier* s2 = new FootSoldier(1);
    Soldier* s3 = new FootSoldier(2);
    Soldier* s4 = new FootSoldier(2);

    b[{0,0}] = s1;
    b[{0,3}] = s2;
    b[{2,2}] = s3;
    b[{1,1}] = s4;

    b.move(1, {0,0}, Board::MoveDIR::Up);
    b.move(1, {0,3}, Board::MoveDIR::Right);
    b.move(2, {2,2}, Board::MoveDIR::Down);
    b.move(2, {3,3}, Board::MoveDIR::Right);

    CHECK(b[{0,1}] == s1);
    CHECK(b[{1,3}] == s2);
    CHECK(b[{2,1}] == s3);
    CHECK(b[{2,3}] == s4);
}

TEST_CASE("Test moving to occupied spot"){
	Board b = Board(4,4);
    Soldier* s1 = new FootSoldier(1);
    Soldier* s2 = new FootSoldier(1);
    Soldier* s3 = new FootSoldier(2);
    Soldier* s4 = new FootSoldier(2);

    b[{0,0}] = s1;
    b[{0,1}] = s2;
    b[{0,2}] = s3;
    b[{1,2}] = s4;

    CHECK_THROWS( b.move(1, {0,0}, Board::MoveDIR::Up) );
    CHECK_THROWS( b.move(2, {1,2}, Board::MoveDIR::Down) );
}

TEST_CASE("Test move outside board"){
	Board b = Board(4,4);
    Soldier* s1 = new FootSoldier(1);
    Soldier* s2 = new FootSoldier(1);
    Soldier* s3 = new FootSoldier(2);

    b[{0,0}] = s1;
    b[{1,3}] = s2;
    b[{3,3}] = s3;

    CHECK_THROWS( b.move(1, {0,0}, Board::MoveDIR::Down) );
    CHECK_THROWS( b.move(1, {1,3}, Board::MoveDIR::Up) );
    CHECK_THROWS( b.move(2, {3,3}, Board::MoveDIR::Right) );
}

TEST_CASE("Test try to move enemy soldier"){
	Board b = Board(4,4);
    Soldier* s1 = new FootSoldier(1);
    Soldier* s2 = new FootSoldier(2);

    b[{0,0}] = s1;
    b[{1,3}] = s2;

    CHECK_THROWS( b.move(2, {0,0}, Board::MoveDIR::Up) );
    CHECK_THROWS( b.move(1, {1,3}, Board::MoveDIR::Down) );
}

TEST_CASE("Test foot soldier shooting"){
	Board b = Board(4,4);
    Soldier* s1 = new FootSoldier(1);
    Soldier* s2 = new FootSoldier(2);

    b[{1,1}] = s1;
    b[{1,3}] = s2;

    b.move(1, {1,1}, Board::MoveDIR::Up);
    
    CHECK( s2->getHealth() == 90 );
}

TEST_CASE("Test foot soldier not hurting himself"){
	Board b = Board(4,4);
    Soldier* s1 = new FootSoldier(1);
    Soldier* s2 = new FootSoldier(2);

    b[{1,1}] = s1;
    b[{1,3}] = s2;

    b.move(1, {1,1}, Board::MoveDIR::Up);
    
    CHECK( s1->getHealth() == 100 );
}

TEST_CASE("Test no friendly fire"){
	Board b = Board(4,4);
    Soldier* s1 = new FootSoldier(1);
    Soldier* s2 = new FootSoldier(2);
    Soldier* s3 = new FootSoldier(2);

    b[{0,0}] = s1;
    b[{1,3}] = s2;
    b[{2,2}] = s3;

    b.move(2, {1,3}, Board::MoveDIR::Right);
    CHECK( (s3->getHealth() == 100) );
}

TEST_CASE("Test foot soldier shoots closest"){
	Board b = Board(4,4);
    Soldier* s1 = new FootSoldier(1);
    Soldier* s2 = new FootSoldier(2);
    Soldier* s3 = new FootSoldier(2);

    b[{1,1}] = s1;
    b[{1,3}] = s2;
    b[{3,3}] = s3;

    b.move(1, {1,1}, Board::MoveDIR::Down);
    CHECK( s2->getHealth() == 90);
    CHECK( s3->getHealth() == 100);
}
TEST_CASE("Test foot commander makes all foot soldiers shoot"){
	Board b = Board(4,4);
    Soldier* s1 = new FootCommander(1);
    Soldier* s2 = new FootSoldier(1);
    Soldier* s3 = new FootSoldier(1);
    Soldier* s4 = new FootSoldier(2);

    b[{1,1}] = s1;
    b[{1,3}] = s2;
    b[{3,3}] = s3;
    b[{3,2}] = s4;

    b.move(1, {1,1}, Board::MoveDIR::Down);
    CHECK( s4->getHealth() == 60);
}

TEST_CASE("Test foot commander makes only foot soldiers shoot"){
	Board b = Board(4,4);
    Soldier* s1 = new FootCommander(1);
    Soldier* s2 = new FootSoldier(1);
    Soldier* s3 = new Sniper(1);
    Soldier* s4 = new FootCommander(1);
    Soldier* s5 = new SniperCommander(1);
    Soldier* s6 = new FootSoldier(2);

    b[{1,1}] = s1;
    b[{1,3}] = s2;
    b[{3,3}] = s3;
    b[{3,2}] = s4;

    b.move(1, {1,1}, Board::MoveDIR::Down);
    CHECK( s4->getHealth() == 70);
}

TEST_CASE("Test sniper shoots soldier with highest health"){
	Board b = Board(10,10);
    Soldier* s1 = new FootSoldier(2);
    Soldier* s2 = new FootSoldier(2);
    Soldier* s3 = new FootSoldier(2);
    Soldier* s4 = new ParamedicCommander(2);
    Soldier* sniper = new Sniper(1);
    b[{6,6}] = s1;
    b[{4,8}] = s2;
    b[{5,4}] = s3;
    b[{7,4}] = s4;
    b[{1,2}] = sniper;

    // move sniper
    b.move(1, {1,2}, Board::MoveDIR::Down);
    // mustv'e shot paramedic commander whose initial health was 200
    CHECK( s4->getHealth() == 150);
}
TEST_CASE("Paramedic heals"){
	Board b = Board(4,4);
    Soldier* s1 = new FootSoldier(1);
    Soldier* s2 = new Paramedic(1);
    Soldier* s3 = new FootSoldier(2);

    b[{1,1}] = s1;
    b[{1,3}] = s2;
    b[{0,0}] = s3;

    b.move(2, {0,0}, Board::MoveDIR::Right);
    CHECK( s1->getHealth() == 90);
    b.move(1, {1,3}, Board::MoveDIR::Down);
    CHECK( s1->getHealth() == 100);
}

TEST_CASE("Paramedic does not heal himself"){
	Board b = Board(4,4);
    Soldier* s1 = new FootSoldier(1);
    Soldier* s2 = new Paramedic(2);

    b[{1,1}] = s1;
    b[{1,3}] = s2;

    b.move(1, {1,1}, Board::MoveDIR::Right);
    CHECK( s2->getHealth() == 90);
    b.move(2, {1,3}, Board::MoveDIR::Down);
    CHECK( s2->getHealth() == 90);
}
TEST_CASE("Paramedic does not do damage"){
	Board b = Board(4,4);
    Soldier* s1 = new FootSoldier(1);
    Soldier* s2 = new Paramedic(2);

    b[{1,1}] = s1;
    b[{1,3}] = s2;

    b.move(2, {1,3}, Board::MoveDIR::Right);
    CHECK( s1->getHealth() == 100);
}
TEST_CASE("Paramedic does not heal enemies"){
	Board b = Board(4,4);
    Soldier* s1 = new FootSoldier(1);
    Soldier* s2 = new Paramedic(1);
    Soldier* s3 = new FootSoldier(2);


    b[{1,1}] = s1;
    b[{0,3}] = s2;
    b[{2,3}] = s3;

    b.move(1, {1,1}, Board::MoveDIR::Right);
    CHECK( s3->getHealth() == 90);
    b.move(1, {0,3}, Board::MoveDIR::Right);
    CHECK( s3->getHealth() == 90);
}

TEST_CASE("Paramedic commander makes other paramedics heal"){
	Board b = Board(4,4);
    Soldier* s1 = new FootSoldier(1);
    Soldier* s2 = new Paramedic(1);
    Soldier* s3 = new ParamedicCommander(1);
    Soldier* s4 = new FootSoldier(2);


    b[{0,0}] = s1;
    b[{0,1}] = s2;
    b[{3,3}] = s3;
    b[{2,0}] = s4;

    b.move(2, {2,0}, Board::MoveDIR::Left);
    CHECK( s1->getHealth() == 90);
    b.move(1, {3,3}, Board::MoveDIR::Down);
    CHECK( s1->getHealth() == 100);
}



