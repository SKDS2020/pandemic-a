#include "FieldDoctor.hpp"

using namespace std;
using namespace pandemic;

/** FieldDoctor
 * Can treat disease in every connected city to his current city without throw card
 **/


/**treat
* Lowering one disease cube from the current city or any connected city. Reducing the level of the disease by 1.
* If a cure for the disease has already been discovered in the color of the city, then the action of "cure the disease" removes all the disease cubes from the city that are in it) Reducing the level of the disease to 0.
**/
Player& FieldDoctor::treat(City c){
    if (current_city != c){// If the city he wants to treat its not his current city
        if (!(Board::is_connected(current_city, c))) {//If the cities are not connected
            throw std::invalid_argument{"the city the FieldDoctor wants to treat its not his current city and not connected to it" };
        }
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