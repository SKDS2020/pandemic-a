#include "GeneSplicer.hpp"
#include "City.hpp"
#include<string>  

using namespace std;
using namespace pandemic;

/** GeneSplicer
 * Can discover cure with any MINIMUN_CARDS_TO_DISCOVER_CURE- dosent matter their colors
 **/


/**Override discover_cure
* Discovering a cure for a disease with a certain color
* The player should be in a city with a Research Station, discard MINIMUN_CARDS_TO_DISCOVER_CURE cards with *ANY* color of disease
* The color of the current city dosent matter
* Each disease has one cure
* If a cure for the disease has already been discovered- the player can keep the card
**/
Player& GeneSplicer::discover_cure(Color color){
    if(board.is_cured(color)){ // if the diseas has been cured
            return *this;
    }
    if(!board.is_research_station(current_city)){ // if the current city has research station
        throw invalid_argument{"Its impossible to discover a cure in the city: "+stringCity(current_city)+" Because there is no research station there"};
    }

    if(cards.size() < MINIMUN_CARDS_TO_DISCOVER_CURE){
        throw invalid_argument{"At least "+ to_string(MINIMUN_CARDS_TO_DISCOVER_CURE) +" cards are needed to discover the cure, GeneSplicer has "+to_string(cards.size())};
    }
    int count_cards = 1;
    for(auto it = cards.begin(); it != cards.end(); count_cards++){
        if(count_cards == MINIMUN_CARDS_TO_DISCOVER_CURE) { break; }
        it = cards.erase(it);
    }
    board.add_to_cured(color);
    return *this;
}