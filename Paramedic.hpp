#include "Soldier.hpp"
#pragma once
namespace WarGame{
    class Paramedic : public Soldier{
        private:
            static const int initialHealth = PARAMEDIC_HEALTH;
        protected:
            Paramedic(int player, int h, int d):Soldier(player, h, d){}
            
        public:
            Paramedic(int player):Soldier(player, PARAMEDIC_HEALTH, 0){}
            virtual void action(Board* board, std::pair<int,int> loc);
    };
}