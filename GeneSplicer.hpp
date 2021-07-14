#pragma once
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"
#include "Board.hpp"

namespace pandemic
{
 /** GeneSplicer
 * Can discover cure with any MINIMUN_CARDS_TO_DISCOVER_CURE- dosent matter their colors
 **/
    class GeneSplicer : public Player
    {
    public:
        GeneSplicer(Board &b, City c) : Player(b, c, "GeneSplicer") {}
        Player &discover_cure(Color c) override;
    };
}