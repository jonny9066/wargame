#include "Settings.hpp"
#pragma once

namespace WarGame{
    // forward declaration
    class Board;
    class Soldier{
        public:  
            //enum Type {Foot, Sniper, Paramedic};
        protected:
            int damage;
            int player;
            int health;
            //Type st;
            Soldier(int player, int h, int d): player(player), health(h){}
        public: 
            int getHealth(){return health;};
            int getOwner(){return player;};
            
            // applies effect to health
            void receiveEffect(int effect){health += effect;};
            //Type getType(){return st;};
            //virtual bool isCommander() = 0;
            virtual void action(Board board) = 0;
            //Gives what difference the soldier's attack will inflict
            int effectOnHealth() const{return -damage;}
    };
}

