#pragma once
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"
#include "Board.hpp"

namespace pandemic{
/** Dispatcher
 * Can use fly-direct to every city if his current city has research station
 **/
    class Dispatcher: public Player {

        public:
            Dispatcher(Board& b, City c): Player(b, c, "Dispatcher") {}
            Player& fly_direct(City destination) override;
    };

}