#include "FootSoldier.hpp"
#pragma once

namespace WarGame{
    class FootCommander : public FootSoldier{
        public:
            FootCommander(int player):FootSoldier(player, FOOTC_HEALTH, FOOTC_DAMAGE){}
            virtual void action(Board board);
            //virtual bool isCommander(){return true;}
    };
}