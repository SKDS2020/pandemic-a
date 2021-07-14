#include "Scientist.hpp"
#include<string>  

using namespace std;
using namespace pandemic;


/** Scientist
 * Can discover cure with less cards
 **/



/** Override discover_cure
* Discovering a cure for a disease with a certain color
* The player should be in a city with a Research Station, discard MINIMUN_CARDS_TO_DISCOVER_CURE_FOR_SCIENTIST (or what will the user insert) cards with the color of the disease
* The color of the current city dosent matter
* Each disease has one cure
* If a cure for the disease has already been discovered- the player can keep the card
**/
Player& Scientist::discover_cure(Color color) {
    if(board.is_cured(color)){ // if the diseas has been cured
        return *this;
    }
    if(!board.is_research_station(current_city)){ // if the current city has research station
        throw invalid_argument{"Its impossible to discover a cure in the city: "+stringCity(current_city)+" Because there is no research station there"};
    }
    int count_cards_with_the_color = 0;
    for(const auto& key : cards){
        if(Board::color_by_city(key) == color) {
            count_cards_with_the_color++;
        }
    }
    if(count_cards_with_the_color < n){
        throw invalid_argument{"At least "+ to_string(n) +" cards with the color " + stringColor(color) + "are needed to discover the cure, Scientist has "+to_string(count_cards_with_the_color)};
    }
    count_cards_with_the_color = 1;
    for(auto it = cards.begin(); it != cards.end(); count_cards_with_the_color++){
        if(count_cards_with_the_color == n) { break; }
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