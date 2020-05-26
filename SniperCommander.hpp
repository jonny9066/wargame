#include "Sniper.hpp"
#pragma once
namespace WarGame{
    class SniperCommander : public Sniper{
        private:
            static const int initialHealth = SNIPERC_HEALTH;
        public:
            SniperCommander(int player):Sniper(player, SNIPERC_HEALTH, SNIPERC_DAMAGE){}
            virtual void action(Board board);
    };
}