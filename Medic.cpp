#include "Medic.hpp"

using namespace std;
using namespace pandemic;

/** Medic - Paramedic
 * when he teat disease he is removing akk of the disease cubes from the current city
 * If a cure for the disease has already been discovered in the color of the city, then he removes all the disease cubes from every city he goes to) Reducing the level of the disease to 0.
 **/


/**Override treat
* remove all the disease cube from the current city. Reducing the level of the disease to 0.
* If a cure for the disease has already been discovered in the color of the city, then he will remove all the disease cubes from the city he gose to) -Reducing the level of the disease to 0  without the action of "cure the disease".
**/
Player& Medic::treat(City c) {
    if (current_city != c) { //if the city the player wants to treat its not his current city
        throw invalid_argument{"The player can not treat the city " + stringCity(c)+" becouse his current city is: " + stringCity(current_city)};
    }
    if (board[c] == 0) { //if there are no disease cubes in that city
        throw invalid_argument{"The city " + stringCity(c)+" dosent need treatment, there are no disease cubes " };
    }

    board[c] = 0;
    return *this;
}


/**arrived_new_city
* relevant only if the player is medic
* If a cure for the disease int city has already been discovered, it removes all the disease cubes- Reducing the level of the disease to 0.
**/
void Medic::arrived_new_city() {
    if(board.is_cured(current_city)) {
        board[current_city] = 0;
    }
}