#include "Soldier.hpp"
#pragma once
class Paramedic : public WarGame::Soldier{
    private:
        static const int initialHealth = PARAMEDIC_HEALTH;
    protected:
        Paramedic(int player, int h, int d):Soldier(player, h, d){}
        
    public:
        Paramedic(int player):Soldier(player, PARAMEDIC_HEALTH, 0){}
        virtual void action(WarGame::Board* board, std::pair<int,int> loc);
};
