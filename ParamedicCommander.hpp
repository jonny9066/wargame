#include "Paramedic.hpp"
#pragma once
namespace WarGame{
    class ParamedicCommander : public Paramedic{
        private:
            static const int initialHealth = PARAMEDICC_HEALTH;
        public:
            ParamedicCommander(int player):Paramedic(player, PARAMEDICC_HEALTH, 0){}
            virtual void action(Board board);
    };
}