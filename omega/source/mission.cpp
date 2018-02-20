#include "stdafx.hpp"
#include "common.hpp"
#include "mission.hpp"
#include "spawning.hpp"

namespace omega {
    namespace mission {
        namespace locations {
            std::vector<vector3> airfields;
            std::vector<vector3> capitals;
            std::vector<vector3> cities;
            std::vector<vector3> factories;
            std::vector<vector3> villages;

            std::vector<vector3> all() {
                std::vector<vector3> all;

                for (auto vec : { airfields, capitals, cities, factories, villages }) {
                    std::merge(all.begin(), all.end(), vec.begin(), vec.end(), std::back_inserter(all));
                }
                
                return all;
            }
        }

        MainMission::MainMission() : Mission() {
            auto pos = vector3(0, 0, 0);
            auto allLocations = locations::all();
            while (true) {
                pos = allLocations.at(common::randomInt(allLocations.size() - 1));
                auto players = sqf::near_entities(pos, sqf_string_list_const_ref({ "" }), 1000.0f);
                if (sqf::count_side(sqf::west(), players) == 0) {
                    break;
                }
            }

            //Create zone for main AO
            zone = std::make_unique<spawning::Zone>(pos, vector3(750, 750, 0), sqf::east());

            //Spawn normal units/vehicles
            zone->spawnCombined(sqf::east(), 15 + common::randomInt(5), 4 + common::randomInt(2), 2 + common::randomInt(3), 2 + common::randomInt(2), 1 + common::randomInt(2));

            //Spawn garrisoned infantry
            for (auto i = 0; i < 5 + common::randomInt(5); ++i) {
                zone->spawnInfantryGarrison(spawning::pools::opfor::units::regular, sqf::east(), 0.5f);
            }
        }
    }
}
