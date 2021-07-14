#pragma once
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"
#include "Board.hpp"

namespace pandemic{

/** Virologist
 * Can treat disease in every city she holds its card, even if its not her current city
 **/

    class Virologist: public Player {

        public:
            Virologist(Board& b, City c): Player(b, c, "Virologist") {}
            Player& treat(City c) override;
    };

}