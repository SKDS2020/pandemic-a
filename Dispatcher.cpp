#include "Dispatcher.hpp"

using namespace std;
using namespace pandemic;

/** Dispatcher
 * Can use fly-direct to every city if his current city has research station
 **/



/**Override fly_direct
* Moving from the current city to a un_connected city
**/
Player& Dispatcher::fly_direct(City destination){
    if(current_city == destination){
        throw invalid_argument{"The player is already in " + stringCity(destination)};
    }
    if(!board.is_research_station(current_city)) { // if the current city hasn't research station
        throw invalid_argument{"Becouse the current city: " + stringCity(current_city) + " hasn't research station, the OperationsExpert can't use fly-direct"};
    }
    current_city = destination;
    return *this;
}