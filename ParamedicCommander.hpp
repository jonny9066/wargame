#include "Paramedic.hpp"
#pragma once
namespace WarGame{
    class ParamedicCommander : public Paramedic{
        public:
            ParamedicCommander(int player):Paramedic(player, PARAMEDICC_HEALTH, 0){}
            virtual void action(Board board);
    };
}