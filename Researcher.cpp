#include "Researcher.hpp"
#include<string>  

using namespace std;
using namespace pandemic;

/** Researcher
 * Can discover cure in current city that hasnt a research station
 **/


/** Override discover_cure
* Discovering a cure for a disease with a certain color
* The color of the current city dosent matter
* Each disease has one cure
* If a cure for the disease has already been discovered- the player can keep the card
**/
Player& Researcher::discover_cure(Color color){
    if(board.is_cured(color)){ // if the diseas has been cured
            return *this;
    }
    int count_cards_with_the_color=0;
    for(const auto& key : cards){
        if(Board::color_by_city(key) == color) {
            count_cards_with_the_color++;
        }
    }
    if(count_cards_with_the_color < MINIMUN_CARDS_TO_DISCOVER_CURE){
        throw invalid_argument{"At least "+ to_string(MINIMUN_CARDS_TO_DISCOVER_CURE) +" cards with the color " + stringColor(color) + "are needed to discover the cure, player has "+to_string(count_cards_with_the_color)};
    }
   
    count_cards_with_the_color = 1;
    for(auto it = cards.begin(); it != cards.end(); count_cards_with_the_color++){
        if(count_cards_with_the_color == MINIMUN_CARDS_TO_DISCOVER_CURE) { break; }
        if(Board::color_by_city(*it) == color) {
            it = cards.erase(it);
        }
        else {
            ++it;
        }
    }
    board.add_to_cured(color);
    return *this;
}
