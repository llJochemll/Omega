#include "stdafx.hpp"
#include "common.hpp"
#include "mission.hpp"
#include "spawning.hpp"

namespace omega {
    namespace mission {
        MainMission::MainMission() : Mission() {
            //Find suitable position
            auto pos = common::findPos(common::worldCentre(), common::worldSize(), 750, 0);

            //Create zone for main AO
            zone = std::make_unique<spawning::Zone>(pos, vector3(750, 750, 0), sqf::east());

            //Spawn patrolling infantry
            for (auto i = 0; i < 15 + common::randomInt(5); ++i) {
                zone->spawnInfantryPatrol(5, spawning::pools::opfor::units::regular, sqf::east(), 0.5f);
            }

            //Spawn garrisoned infantry
            for (auto i = 0; i < 5 + common::randomInt(5); ++i) {
                zone->spawnInfantryGarrison(spawning::pools::opfor::units::regular, sqf::east(), 0.5f);
            }

            //Spawn vehicles: apc
            for (auto i = 0; i < 2 + common::randomInt(3); ++i) {
                zone->spawnVehiclePatrol(spawning::pools::opfor::vehicles::apcs, { true, false }, 0.5f);
            }

            //Spawn vehicles: car
            for (auto i = 0; i < 4 + common::randomInt(2); ++i) {
                zone->spawnVehiclePatrol(spawning::pools::opfor::vehicles::cars, { true, false }, 0.5f);
            }

            //Spawn vehicles: ifv
            for (auto i = 0; i < 2 + common::randomInt(2); ++i) {
                zone->spawnVehiclePatrol(spawning::pools::opfor::vehicles::ifvs, { true, false }, 0.5f);
            }

            //Spawn vehicles: tank
            for (auto i = 0; i < 1 + common::randomInt(2); ++i) {
                zone->spawnVehiclePatrol(spawning::pools::opfor::vehicles::tanks, { true, false }, 0.5f);
            }
        }
    }
}
