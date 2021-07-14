#pragma once
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"
#include "Board.hpp"

namespace pandemic{

/** Medic - Paramedic
 * when he teat disease he is removing akk of the disease cubes from the current city
 * If a cure for the disease has already been discovered in the color of the city, then he removes all the disease cubes from every city he goes to) Reducing the level of the disease to 0.
 **/
    class Medic: public Player {

        public:
            Medic(Board& b, City c): Player(b, c, "Medic") {}
            Player& treat(City c) override;
            void arrived_new_city() override;
    };
    
}