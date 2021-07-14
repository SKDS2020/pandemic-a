#include "Virologist.hpp"

using namespace std;
using namespace pandemic;

/** Virologist
 * Can treat disease in every city she holds its card, even if its not her current city
 **/


/**Override treat
* Lowering one disease cube from the current city or any city that the Virologist has his card. Reducing the level of the disease by 1.
* If a cure for the disease has already been discovered in the color of the city, then the action of "cure the disease" removes all the disease cubes from the city that are in it) Reducing the level of the disease to 0.
**/
Player& Virologist::treat(City c){

    if (board[c] == 0) { //if there are no disease cubes in that city
        throw invalid_argument{"The city " + stringCity(c)+" dosent need treatment, there are no disease cubes " };
    }
    if (current_city != c) { //if the Virologist wants to treat another city 
        if(cards.count(c)==0) {
             throw invalid_argument{"The Virologist can not treat the city " + stringCity(c)+" becouse he does not have the city card "};
        }
        cards.erase(c);
    }
    if (board.is_cured(c)) {
        board[c] = 0;
    }
    else {
        board[c]--;
    }
    return *this;
}