#include "Soldier.hpp"
#pragma once
class Commander {
    protected:
        const std::type_info& ti;
        //void command(Board* board, int player);
        Commander(const std::type_info& typinf):ti(typinf){}
};
