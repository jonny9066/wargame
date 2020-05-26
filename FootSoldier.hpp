#include "Soldier.hpp"
#include "Settings.hpp"
#pragma once

namespace WarGame{
    class FootSoldier : public Soldier{
        private:
            static const int initialHealth = FOOT_HEALTH;
        protected:
            FootSoldier(int player, int h, int d):Soldier(player, h, d){}
            
        public:
            FootSoldier(int player):Soldier(player, FOOT_HEALTH, FOOT_DAMAGE){}

            virtual void action(Board board);
            //virtual bool isCommander(){return false;}
    };
}
