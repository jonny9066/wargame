#include "Paramedic.hpp"
#include "Commander.hpp"
#pragma once
class ParamedicCommander : public Paramedic, public Commander{
    private:
        static const int initialHealth = PARAMEDICC_HEALTH;
    public:
        ParamedicCommander(int player):Paramedic(player, PARAMEDICC_HEALTH, 0),Commander(typeid(Paramedic)){}
        virtual void action(WarGame::Board* board, std::pair<int,int> loc);
};
