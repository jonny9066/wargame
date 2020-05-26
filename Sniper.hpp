#include "Soldier.hpp"
#pragma once

namespace WarGame{
    class Sniper : public Soldier{
        protected:
            Sniper(int player, int h, int d):Soldier(player, h, d){}
            
        public:
            Sniper(int player):Soldier(player, SNIPER_HEALTH, SNIPER_DAMAGE){}
            void action(Board board);
            //virtual bool isCommander(){return false;}
    };
}