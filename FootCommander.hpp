#include "FootSoldier.hpp"
#pragma once

namespace WarGame{
    class FootCommander : public FootSoldier{
        private:
            static const int initialHealth = FOOTC_HEALTH;
        public:
            FootCommander(int player):FootSoldier(player, FOOTC_HEALTH, FOOTC_DAMAGE){}
            virtual void action(Board board);
            //virtual bool isCommander(){return true;}
    };
}