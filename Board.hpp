#pragma once
#include "City.hpp"
#include "Color.hpp"
#include <map>
#include <set>
#include <iostream>
#include "GameSettings.hpp"
using namespace std;

namespace pandemic {

    const int MINIMUN_CARDS_TO_DISCOVER_CURE = 5; //section 6
    const int MINIMUN_CARDS_TO_DISCOVER_CURE_FOR_SCIENTIST = 4; //section 3
    class Board {

        static map<City, set<City>> connections;
        map<City, int> diseas_cubes;
        set<Color> cured_colors; //set of diseases that have been cured
        set<City> research_stations;

        public:
            /**Board()
             * Empty Constructor
             **/
            Board() {}

            /**operator[]
             * Allows to update the number of disease cubes in input city (disease level)
             **/
            int& operator[](City c);

            /**output operator <<
             * Displays the status of the board
             **/
            friend std::ostream& operator<<(std::ostream& out, const Board& b);

            /**is_clean
             * Returns true if the board is clean - there are no disease cubes in any city
             **/
            bool is_clean();

            /**remove_cures
             * deletes all the cures- only for tests
             **/
            void remove_cures();

            /**remove_stations
             * deletes all the research stations- only for tests
             **/
            void remove_stations();


//---------------------------Additional Functions---------------------------

            /**is_connected
             * Check if two cities are connected
             **/
            static bool is_connected(City& c1, City& c2);
            

            /**color_by_city
            * return the color of the input city
            **/
            static Color color_by_city(City c);


            /**add_to_cured
            * add the color (diseas) to the cured set
            **/
            void add_to_cured(Color c);

            /**is_research_station
            * check if there is a research station in the input city
            **/
            bool is_research_station(City c);

            /**build_research_station
            * build research station in the input city
            **/
            void build_research_station(City c);

            /**is_cured
             * Check if *city* has been cured
             **/
            bool is_cured(City c);

            /**is_cured
             * Check if *diseas* has been cured
             **/
            bool is_cured(Color color);

          
    };
}
