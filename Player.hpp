#pragma once
#include "City.hpp"
#include "Board.hpp"
#include <set>
using namespace std;
namespace pandemic {


    class Player {


        protected:
            Board& board;
            string player_role;
            City current_city;
            set<City> cards;
              
        public:

            Player(Board& b, City c, std::string r = "Player"): board(b), current_city(c), player_role(r){}
            
            /**drive
             * Moving from the current city to a connected city
             **/
            Player& drive(City destination);

            /**fly_direct
             * Moving from the current city to a un_connected city
             * If the player has a card of his *destination* city
             **/
            virtual Player& fly_direct(City destination);

            /**fly_charter
             * Moving from the current city to a un_connected city
             * If the player has a card of his *current* city
             **/
            Player& fly_charter(City destination);

            /**fly_shuttle
             * Moving from the current city (If it has research station) to any other city that has a research station
             **/
            Player& fly_shuttle(City destination);

            /**build
             * Construction of a research station in the current city
             * the player need to throw the card of his current city
             * if the current city has research station -he can keep the card
             **/
            virtual Player& build();

            /**discover_cure
             * Discovering a cure for a disease with a certain color
             * The player should be in a city with a Research Station, discard 5 cards with the color of the disease
             * The color of the current city dosent matter
             * Each disease has one cure
             * If a cure for the disease has already been discovered- the player can keep the card
             **/
            virtual Player& discover_cure(Color color);


            /**treat
             * Lowering one disease cube from the current city. Reducing the level of the disease by 1.
             * If a cure for the disease has already been discovered in the color of the city, then the action of "cure the disease" removes all the disease cubes from the city that are in it) Reducing the level of the disease to 0.
             **/
            virtual Player& treat(City c);



            /**role
             * Returns the role of the player
             **/
            string role(){return player_role;}

            /**take_card
             * take city-card - it will inset the cardsw set another card
             * if the player takes card he already has it will not effect him
             **/
            Player& take_card(City c);
            
            //---------------------------Additional Functions---------------------------
            
            set<City> get_cards(){return cards;}

            /**arrived_new_city
            * relevant only if the player is medic
            * If a cure for the disease int city has already been discovered, it removes all the disease cubes- Reducing the level of the disease to 0.
            **/
            virtual void arrived_new_city(){}; //relevant only if the player is medic
    };

}
