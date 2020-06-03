#include "Soldier.hpp"
#pragma once


class Sniper : public WarGame::Soldier{
    private:
        static const int initialHealth = SNIPER_HEALTH;
    protected:
        Sniper(int player, int h, int d):Soldier(player, h, d){}
        
    public:
        Sniper(int player):Soldier(player, SNIPER_HEALTH, SNIPER_DAMAGE){}
        void action(WarGame::Board* board, std::pair<int,int> loc);
};
