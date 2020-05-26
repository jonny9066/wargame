#include "Soldier.hpp"
#include "Settings.hpp"
#pragma once
namespace WarGame{
    class Paramedic : public Soldier{
        protected:
            Paramedic(int player, int h, int d):Soldier(player, h, d){}
            
        public:
            Paramedic(int player):Soldier(player, PARAMEDIC_HEALTH, 0){}
            virtual void action(Board board);
    };
}