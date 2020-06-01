#include "Settings.hpp"

#include <string>
#include <typeinfo>
#pragma once

namespace WarGame{
    // forward declaration
    class Board;
    class Soldier{
        private:
            const int initialHealth;
        protected:
            int damage;
            int player;
            int health;
            enum Type {FS, FC};
            Soldier(int player, int h, int d): player(player), health(h), initialHealth(h), damage(d){}
        public: 
            // to avoid undefined behavior
            virtual ~Soldier(){}
            int getHealth()const{return health;}
            int getOwner()const{return player;}
            int getDamage() const{return damage;}


            // reduces 'damage' points from health
            void receiveDamage(int damage){health -= damage;}
            // restores health to full
            void restoreHealth(){health = initialHealth;}
            virtual void action(Board* board, std::pair<int,int> loc) = 0;
            //Gives what difference the soldier's attack will inflict
    };
}

