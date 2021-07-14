#pragma once
#include "City.hpp"
#include "Player.hpp"
#include "Board.hpp"

namespace pandemic{

/** OperationsExpert
 * Can build (research station) in every Current city without throwing card
 **/
    class OperationsExpert: public Player {

        public:
            OperationsExpert(Board& b, City c): Player(b, c, "OperationsExpert") {}
            Player& build() override;
    };

}