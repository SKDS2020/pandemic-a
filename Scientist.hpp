#pragma once
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"
#include "Board.hpp"

namespace pandemic {
/** Scientist
 * Can discover cure with less cards
 **/
    class Scientist: public Player {
        int n=MINIMUN_CARDS_TO_DISCOVER_CURE_FOR_SCIENTIST;//in this program the user choose it

        public:
            Scientist(Board& b, City c, int num): Player(b, c, "Scientist"), n(num) {}
            Player& discover_cure(Color color) override;
    };
    
}