#include "doctest.h"
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"

#include "Researcher.hpp"
#include "Scientist.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "OperationsExpert.hpp"
#include "Dispatcher.hpp"
#include "Medic.hpp"
#include "Virologist.hpp"

#include <iostream>

#include <stdexcept>
#include "Color.hpp"
#include <map>
#include <set>
#include <iostream>
#include "GameSettings.hpp"
#include <sstream>
using namespace std;
using namespace pandemic;



// static map<City, set<City>> connections;
//         map<City, int> diseas_cubes;
//         set<Color> cured_colors; //set of diseases that have been cured
//         set<City> research_stations;


// std::map<City, std::set<City>> Board::connections {
//     { Algiers, {Madrid, Paris, Istanbul, Cairo } },
//     { Atlanta, {Chicago, Miami, Washington } },
//     { Baghdad, {Tehran, Istanbul, Cairo, Riyadh, Karachi } },
//     { Bangkok, {Kolkata, Chennai, Jakarta, HoChiMinhCity, HongKong } },
//     { Beijing, {Shanghai, Seoul } },
//     { Bogota, {MexicoCity, Lima, Miami, SaoPaulo, BuenosAires } },
//     { BuenosAires, {Bogota, SaoPaulo } },
//     { Cairo, {Algiers, Istanbul, Baghdad, Khartoum, Riyadh } },
//     { Chennai, {Mumbai, Delhi, Kolkata, Bangkok, Jakarta } },
//     { Chicago, {SanFrancisco, LosAngeles, MexicoCity, Atlanta, Montreal } },
//     { Delhi, {Tehran, Karachi, Mumbai, Chennai, Kolkata } },
//     { Essen, {London, Paris, Milan, StPetersburg } },
//     { HoChiMinhCity, {Jakarta, Bangkok, HongKong, Manila } },
//     { HongKong, {Bangkok, Kolkata, HoChiMinhCity, Shanghai, Manila, Taipei } },
//     { Istanbul, {Milan, Algiers, StPetersburg, Cairo, Baghdad, Moscow } },
//     { Jakarta, {Chennai, Bangkok, HoChiMinhCity, Sydney } },
//     { Johannesburg, {Kinshasa, Khartoum } },
//     { Karachi, {Tehran, Baghdad, Riyadh, Mumbai, Delhi } },
//     { Khartoum, {Cairo, Lagos, Kinshasa, Johannesburg } },
//     { Kinshasa, {Lagos, Khartoum, Johannesburg } },
//     { Kolkata, {Delhi, Chennai, Bangkok, HongKong } },
//     { Lagos, {SaoPaulo, Khartoum, Kinshasa } },
//     { Lima, {MexicoCity, Bogota, Santiago } },
//     { London, {NewYork, Madrid, Essen, Paris } },
//     { LosAngeles, {SanFrancisco, Chicago, MexicoCity, Sydney } },
//     { Madrid, {London, NewYork, Paris, SaoPaulo, Algiers } },
//     { Manila, {Taipei, SanFrancisco, HoChiMinhCity, Sydney, HongKong } },
//     { MexicoCity, {LosAngeles, Chicago, Miami, Lima, Bogota } },
//     { Miami, {Atlanta, MexicoCity, Washington, Bogota } },
//     { Milan, {Essen, Paris, Istanbul } },
//     { Montreal, {Chicago, Washington, NewYork } },
//     { Moscow, {StPetersburg, Istanbul, Tehran } },
//     { Mumbai, {Karachi, Delhi, Chennai } },
//     { NewYork, {Montreal, Washington, London, Madrid } },
//     { Osaka, {Taipei, Tokyo } },
//     { Paris, {Algiers, Essen, Madrid, Milan, London } },
//     { Riyadh, {Baghdad, Cairo, Karachi } },
//     { SanFrancisco, {LosAngeles, Chicago, Tokyo, Manila } },
//     { Santiago, {Lima } },
//     { SaoPaulo, {Bogota, BuenosAires, Lagos, Madrid } },
//     { Seoul, {Beijing, Shanghai, Tokyo } },
//     { Shanghai, {Beijing, HongKong, Taipei, Seoul, Tokyo } },
//     { StPetersburg, {Essen, Istanbul, Moscow } },
//     { Sydney, {Jakarta, Manila, LosAngeles } },
//     { Taipei, {Shanghai, HongKong, Osaka, Manila } },
//     { Tehran, {Baghdad, Moscow, Karachi, Delhi } },
//     { Tokyo, {Seoul, Shanghai, Osaka, SanFrancisco } },
//     { Washington, {Atlanta, NewYork, Montreal, Miami } }
// };

    Board b;
    ////     { Lima, {MexicoCity, Bogota, Santiago } },

TEST_CASE("Medic"){
    Player medic (b, Lima, "Medic");
    SUBCASE("drive"){
            /**drive
             * Moving from the current city to a connected city
             **/
        SUBCASE("Same city"){
            CHECK_THROWS(medic.drive(Lima)); 
        } 
        SUBCASE("Neighboring city"){
            CHECK_NOTHROW(medic.drive(MexicoCity));   
         }
        SUBCASE("Not neighboring city"){
            CHECK_THROWS(medic.drive(Tehran));  
         }
    }
        SUBCASE("fly_direct"){
            /**fly_direct
             * Moving from the current city to a un_connected city
             * If the player has a card of his *destination* city
             **/
            SUBCASE("without any card"){
                SUBCASE("Same city"){
                    CHECK_THROWS(medic.fly_direct(Lima)); 
                } 
                SUBCASE("Neighboring city"){
                    CHECK_THROWS(medic.fly_direct(MexicoCity));   
                }
                SUBCASE("Not neighboring city"){
                    CHECK_THROWS(medic.fly_direct(Tehran));  
                }
            }
            SUBCASE("with different card, not current or destination city"){
                    medic.take_card(Miami);
                SUBCASE("Same city"){
                    CHECK_THROWS(medic.fly_direct(Lima)); 
                } 
                SUBCASE("Neighboring city"){
                    CHECK_THROWS(medic.fly_direct(MexicoCity));   
                }
                SUBCASE("Not neighboring city"){
                    CHECK_THROWS(medic.fly_direct(Tehran));  
                }
            }
            SUBCASE("with current city card, not destination city"){
                    medic.take_card(Lima);
                SUBCASE("Same city"){
                    CHECK_THROWS(medic.fly_direct(Lima)); // hes alrady here
                } 
                SUBCASE("Neighboring city"){
                    CHECK_THROWS(medic.fly_direct(MexicoCity));   
                }
                SUBCASE("Not neighboring city"){
                    CHECK_THROWS(medic.fly_direct(Tehran));  
                }
            }
            SUBCASE("with destination city card"){
                    medic.take_card(MexicoCity);
                    medic.take_card(Tehran);

                SUBCASE("Same city"){
                    CHECK_THROWS(medic.fly_direct(Lima)); // hes alrady here
                } 
                SUBCASE("Neighboring city"){
                    CHECK_NOTHROW(medic.fly_direct(MexicoCity));   
                }
                SUBCASE("Not neighboring city"){
                    CHECK_NOTHROW(medic.fly_direct(Tehran));  
                }
            }
            
    }
        SUBCASE("fly_charter"){
            /**fly_charter
             * Moving from the current city to a un_connected city
             * If the player has a card of his *current* city
             **/
            SUBCASE("without any card"){
                SUBCASE("Same city"){
                    CHECK_THROWS(medic.fly_charter(Lima)); 
                } 
                SUBCASE("Neighboring city"){
                    CHECK_THROWS(medic.fly_charter(MexicoCity));   
                }
                SUBCASE("Not neighboring city"){
                    CHECK_THROWS(medic.fly_charter(Tehran));  
                }
            }
            SUBCASE("with different card, not current or destination city"){
                    medic.take_card(Miami);
                SUBCASE("Same city"){
                    CHECK_THROWS(medic.fly_charter(Lima)); 
                } 
                SUBCASE("Neighboring city"){
                    CHECK_THROWS(medic.fly_charter(MexicoCity));   
                }
                SUBCASE("Not neighboring city"){
                    CHECK_THROWS(medic.fly_charter(Tehran));  
                }
            }
            SUBCASE("with current city card, not destination city"){
                    medic.take_card(Lima);
                SUBCASE("Same city"){
                    CHECK_THROWS(medic.fly_charter(Lima)); // hes alrady here
                } 
                SUBCASE("Neighboring city"){
                    CHECK_NOTHROW(medic.fly_charter(MexicoCity));   
                }
                SUBCASE("Not neighboring city"){
                    CHECK_NOTHROW(medic.fly_charter(Tehran));  
                }
            }
            SUBCASE("with destination city card"){
                    medic.take_card(MexicoCity);
                    medic.take_card(Tehran);

                SUBCASE("Same city"){
                    CHECK_THROWS(medic.fly_charter(Lima)); // hes alrady here
                } 
                SUBCASE("Neighboring city"){
                    CHECK_THROWS(medic.fly_charter(MexicoCity));   
                }
                SUBCASE("Not neighboring city"){
                    CHECK_THROWS(medic.fly_charter(Tehran));  
                }
            }
            
    }
}
