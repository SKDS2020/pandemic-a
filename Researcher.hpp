#pragma once
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"
#include "Board.hpp"

namespace pandemic{

/** Researcher
 * Can discover cure in current city that hasnt a research station
 **/
    class Researcher: public Player {

        public:
            Researcher(Board& b, City c): Player(b, c, "Researcher") {}
            Player& discover_cure(Color c) override;
    };

}