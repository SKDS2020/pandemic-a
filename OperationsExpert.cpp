#include "OperationsExpert.hpp"

using namespace std;
using namespace pandemic;

/** OperationsExpert
 * Can build (research station) in every Current city without throwing card
 **/


/**Override build
* Construction of a research station in the current city
**/
Player& OperationsExpert::build(){
    if(board.is_research_station(current_city)){ // if the current city has research station
        return *this;
    }
    board.build_research_station(current_city);
    return *this;
}