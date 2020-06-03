#include "Sniper.hpp"
#include "Commander.hpp"
#pragma once

class SniperCommander : public Sniper, public Commander{
    private:
        static const int initialHealth = SNIPERC_HEALTH;
    public:
        SniperCommander(int player):Sniper(player, SNIPERC_HEALTH, SNIPERC_DAMAGE), Commander(typeid(Sniper)){}
        virtual void action(WarGame::Board* board, std::pair<int,int> loc);
};
