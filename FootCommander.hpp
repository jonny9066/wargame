#include "FootSoldier.hpp"
#include "Commander.hpp"
#pragma once


class FootCommander : public FootSoldier, public Commander{
    private:
        static const int initialHealth = FOOTC_HEALTH;
    public:
        FootCommander(int player):FootSoldier(player, FOOTC_HEALTH, FOOTC_DAMAGE), Commander(typeid(FootSoldier)){}
        virtual void action(WarGame::Board* board, std::pair<int,int> loc);
};
