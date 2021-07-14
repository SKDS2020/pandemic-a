#include "Board.hpp"
#include<string>  
/* include main classes */
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"

#include <iostream>
#include <map>
#include <set>
#include <sstream>

#include "GameSettings.hpp"

using namespace std;
using namespace pandemic;

/**operator[]
* Allows to update the number of disease cubes in input city (disease level)
**/
int& Board::operator[](City c) {
    return diseas_cubes[c];
}

/**output operator <<
* Displays the status of the board
* we will use auto& to move in map
* for (auto& [key,value] : the map)
**/
std::ostream& pandemic::operator<<(std::ostream& out, const Board& b) {
	
    out << RED << "________________________________________________________"  << endl;
    out << BOLDBLACK << "\t\t\t"<< "Board Status"  << endl;

    
    out << endl << BOLDBLACK << "City" << "\t\t"<< "Disease color" << "\t"<< "Cubes - level" << endl;
        for(const auto& i: b.diseas_cubes) {
            out << BLUE << stringCity(i.first) << " \t\t" << stringColor(Board::color_by_city(i.first)) << "\t\t"<< i.second << endl;
    }
    out << endl<< BOLDBLACK << "Cured Diseases:" << " \t";
    for(const auto& i: b.cured_colors) {
        out << BLUE << stringColor(i)<< " \t" ;
    }
        
    out << endl << endl<< BOLDBLACK << "Cities with Research-Station:" " \t";

    for(const auto& i: b.research_stations) {
        out<< BLUE << stringCity(i) << " \t";
    }
    out << endl << RED << "________________________________________________________"  << RESET << endl;

    return out;
}


/**is_clean
* Returns true if the board is clean - there are no disease cubes in any city
**/
bool Board::is_clean() {
    bool flag = true;
    for(auto& pair: diseas_cubes) {
        if(pair.second > 0) {
            flag = false;
        }
    }
    return flag;
}


/**remove_cures
* deletes all the cures- only for tests
**/
void Board::remove_cures() {
    cured_colors.clear();
}

/**remove_stations
* deletes all the research stations- only for tests
**/
void Board::remove_stations() {
    research_stations.clear();
}

//---------------------------Additional Functions---------------------------

/**is_connected
* Check if two cities are connected
* */
bool Board::is_connected(City &c1, City &c2) {
        bool flag = false;
	if (connections.at(c1).count(c2)== 1)
    {
        flag =true;
    }
    return flag;
}

/** color_by_city
 *  return the color of the required city
 **/
Color Board::color_by_city(City c) {
    return city_color_map.at(c);
}


/**add_to_cured
* add the color (diseas) to the cured set
**/
void Board::add_to_cured(Color c) {
    cured_colors.insert(c);
}

/**is_research_station
* check if there is a research station in the input city
**/
bool Board::is_research_station(City c) {
    bool flag = false;
    if (research_stations.count(c)>0){
        flag = true;
    }
    return flag;
}

/**build_research_station
* build research station in the input city
**/
void Board::build_research_station(City c) {
    research_stations.insert(c);
}

/**is_cured
 * Check if *city* has been cured
**/
bool Board::is_cured(City c) {
    return (cured_colors.count(color_by_city(c))>0);
}

/**is_cured
 * Check if *diseas* has been cured
**/
bool Board::is_cured(Color color) {
    return (cured_colors.count(color)>0);
}



/**map container
* Representation of the connections between the cities
* https://www.freecodecamp.org/news/c-plus-plus-map-explained-with-examples/
* thanks to Oria halperin
* */
std::map<City, std::set<City>> Board::connections {
    { Algiers, {Madrid, Paris, Istanbul, Cairo } },
    { Atlanta, {Chicago, Miami, Washington } },
    { Baghdad, {Tehran, Istanbul, Cairo, Riyadh, Karachi } },
    { Bangkok, {Kolkata, Chennai, Jakarta, HoChiMinhCity, HongKong } },
    { Beijing, {Shanghai, Seoul } },
    { Bogota, {MexicoCity, Lima, Miami, SaoPaulo, BuenosAires } },
    { BuenosAires, {Bogota, SaoPaulo } },
    { Cairo, {Algiers, Istanbul, Baghdad, Khartoum, Riyadh } },
    { Chennai, {Mumbai, Delhi, Kolkata, Bangkok, Jakarta } },
    { Chicago, {SanFrancisco, LosAngeles, MexicoCity, Atlanta, Montreal } },
    { Delhi, {Tehran, Karachi, Mumbai, Chennai, Kolkata } },
    { Essen, {London, Paris, Milan, StPetersburg } },
    { HoChiMinhCity, {Jakarta, Bangkok, HongKong, Manila } },
    { HongKong, {Bangkok, Kolkata, HoChiMinhCity, Shanghai, Manila, Taipei } },
    { Istanbul, {Milan, Algiers, StPetersburg, Cairo, Baghdad, Moscow } },
    { Jakarta, {Chennai, Bangkok, HoChiMinhCity, Sydney } },
    { Johannesburg, {Kinshasa, Khartoum } },
    { Karachi, {Tehran, Baghdad, Riyadh, Mumbai, Delhi } },
    { Khartoum, {Cairo, Lagos, Kinshasa, Johannesburg } },
    { Kinshasa, {Lagos, Khartoum, Johannesburg } },
    { Kolkata, {Delhi, Chennai, Bangkok, HongKong } },
    { Lagos, {SaoPaulo, Khartoum, Kinshasa } },
    { Lima, {MexicoCity, Bogota, Santiago } },
    { London, {NewYork, Madrid, Essen, Paris } },
    { LosAngeles, {SanFrancisco, Chicago, MexicoCity, Sydney } },
    { Madrid, {London, NewYork, Paris, SaoPaulo, Algiers } },
    { Manila, {Taipei, SanFrancisco, HoChiMinhCity, Sydney, HongKong } },
    { MexicoCity, {LosAngeles, Chicago, Miami, Lima, Bogota } },
    { Miami, {Atlanta, MexicoCity, Washington, Bogota } },
    { Milan, {Essen, Paris, Istanbul } },
    { Montreal, {Chicago, Washington, NewYork } },
    { Moscow, {StPetersburg, Istanbul, Tehran } },
    { Mumbai, {Karachi, Delhi, Chennai } },
    { NewYork, {Montreal, Washington, London, Madrid } },
    { Osaka, {Taipei, Tokyo } },
    { Paris, {Algiers, Essen, Madrid, Milan, London } },
    { Riyadh, {Baghdad, Cairo, Karachi } },
    { SanFrancisco, {LosAngeles, Chicago, Tokyo, Manila } },
    { Santiago, {Lima } },
    { SaoPaulo, {Bogota, BuenosAires, Lagos, Madrid } },
    { Seoul, {Beijing, Shanghai, Tokyo } },
    { Shanghai, {Beijing, HongKong, Taipei, Seoul, Tokyo } },
    { StPetersburg, {Essen, Istanbul, Moscow } },
    { Sydney, {Jakarta, Manila, LosAngeles } },
    { Taipei, {Shanghai, HongKong, Osaka, Manila } },
    { Tehran, {Baghdad, Moscow, Karachi, Delhi } },
    { Tokyo, {Seoul, Shanghai, Osaka, SanFrancisco } },
    { Washington, {Atlanta, NewYork, Montreal, Miami } }
};

