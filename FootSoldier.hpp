#include "Soldier.hpp"
#pragma once

class FootSoldier : public WarGame::Soldier{
    private:
        static const int initialHealth = FOOT_HEALTH;
    protected:
        FootSoldier(int player, int h, int d):Soldier(player, h, d){}
        
    public:
        FootSoldier(int player):Soldier(player, FOOT_HEALTH, FOOT_DAMAGE){}

        virtual void action(WarGame::Board* board, std::pair<int,int> loc);
        //virtual bool isCommander(){return false;}
};

