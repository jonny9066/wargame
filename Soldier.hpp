#include "Settings.hpp"
#pragma once

namespace WarGame{
    // forward declaration
    class Board;
    class Soldier{
        private:
            static const int initialHealth;
        public:  
            //enum Type {Foot, Sniper, Paramedic};
        protected:
            int damage;
            int player;
            int health;
            //Type st;
            Soldier(int player, int h, int d): player(player), health(h){}
        public: 
            // to avoid undefined behavior
            virtual ~Soldier(){}
            int getHealth()const{return health;};
            int getOwner()const{return player;};
            int getDamage() const{return damage;}
            
            // reduces 'damage' points from health
            void receiveDamage(int damage){health -= damage;};
            // restores health to full
            void restoreHealth(){health = initialHealth;};
            //Type getType(){return st;};
            //virtual bool isCommander() = 0;
            virtual void action(Board board) = 0;
            //Gives what difference the soldier's attack will inflict
    };
}

