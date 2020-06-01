#include "Soldier.hpp"
#pragma once
namespace WarGame{
    class Commander {
        protected:
            const std::type_info& ti;
            //void command(Board* board, int player);
            Commander(const std::type_info& typinf):ti(typinf){}
    };
} 