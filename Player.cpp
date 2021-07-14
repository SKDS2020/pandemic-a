#include "Player.hpp"
#include<string>  
using namespace std;
using namespace pandemic;



/**drive
 * Moving from the current city to a connected city
 **/
Player& Player::drive(City destination){
    if(current_city == destination){ // If the destination city is the current city
        throw invalid_argument{"The player is already in " + stringCity(destination)};
    }
    if(!Board::is_connected(current_city, destination)){ //If the cities are not connected
        throw invalid_argument{stringCity(current_city) + " and the destination city: " + stringCity(destination) + " are not connected -maybe he wants to fly?"};
    }
    current_city = destination;
    arrived_new_city(); //XXX
    return *this;
}

/**fly_direct
* Moving from the current city to a un_connected city
*If the player has a card of his *destination* city
**/
Player& Player::fly_direct(City destination){
    if(current_city == destination){ // If the destination city is the current city
        throw invalid_argument{"The player is already in " + stringCity(destination)};
    }
    if(cards.count(destination)==0){ 
        throw invalid_argument{"The player does not have the city card: " + stringCity(destination)};
    }
    current_city = destination;
    cards.erase(destination); // Remove the used card
    arrived_new_city();
    return *this;
}

/**fly_charter
* Moving from the current city to an un_connected city
* If the player has a card of his *current* city
**/
Player& Player::fly_charter(City destination){
    if(current_city == destination){// If the destination city is the current city
        throw invalid_argument{"The player is already in " + stringCity(destination)};
    }
    if(cards.count(current_city)<1){
        throw invalid_argument{"The player does not have the city card: " + stringCity(current_city)};
    }
    current_city = destination;
    cards.erase(current_city);// Remove the used card
    
    arrived_new_city();
    return *this;
}


/**fly_shuttle
* Moving from the current city (If it has research station) to any other city that has a research station
**/
Player& Player::fly_shuttle(City destination){
    if(current_city == destination){// If the destination city is the current city
        throw invalid_argument{"The player is already in " + stringCity(destination)};
    }
    if(!board.is_research_station(current_city)){ // if the current city hasn't research station
        throw invalid_argument{"Becouse the current city: " + stringCity(current_city) + " hasn't research station, the player can't use fly-shuttle"};
    }
    if(!board.is_research_station(destination)){ // if the destination city hasn't research station)
        throw invalid_argument{"Becouse the destination city: " + stringCity(destination) + " hasn't research station, the player can't use fly-shuttle"};
    }
    current_city = destination;
    arrived_new_city();
    return *this;
}


/**build
* Construction of a research station in the current city
* the player need to throw the card of his current city
* if the current city has research station -he can keep the card
**/
Player& Player::build(){
    if(board.is_research_station(current_city)){ // if the current city has research station
        return *this;
    }
    if(cards.count(current_city)==0){ 
        throw invalid_argument{"The player does not have the city card: " + stringCity(current_city)+"so he can't build a research station"};
    }
    board.build_research_station(current_city);
    cards.erase(current_city);
    return *this;
}
/**discover_cure
* Discovering a cure for a disease with a certain color
* The player should be in a city with a Research Station, discard MINIMUN_CARDS_TO_DISCOVER_CURE cards with the color of the disease
* The color of the current city dosent matter
* Each disease has one cure
* If a cure for the disease has already been discovered- the player can keep the card
**/
Player& Player::discover_cure(Color color){
    if(board.is_cured(color)){ // if the diseas has been cured
            return *this;
    }
    if(!board.is_research_station(current_city)){ // if the current city has research station
        throw invalid_argument{"Its impossible to discover a cure in the city: "+stringCity(current_city)+" Because there is no research station there"};
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

/**treat
* Lowering one disease cube from the current city. Reducing the level of the disease by 1.
* If a cure for the disease has already been discovered in the color of the city, then the action of "cure the disease" removes all the disease cubes from the city that are in it) Reducing the level of the disease to 0.
**/
Player& Player::treat(City c){
    if (current_city != c) { //if the city the player wants to treat its not his current city
        throw invalid_argument{"The player can not treat the city " + stringCity(c)+" becouse his current city is: " + stringCity(current_city)};
    }
    if (board[c] == 0) { //if there are no disease cubes in that city
        throw invalid_argument{"The city " + stringCity(c)+" dosent need treatment, there are no disease cubes " };
    }
    if (board.is_cured(c)) { //If a cure for the disease has already been discovered
        board[c] = 0;
    }
    else {
        board[c]--;
    }
    return *this;
}


/**take_card
* take city-card - it will inset the cardsw set another card
* if the player takes card he already has it will not effect him
**/
Player& Player::take_card(City c){
    cards.insert(c);
    return *this;
}



