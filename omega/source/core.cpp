#include "stdafx.hpp"
#include "common.hpp"
#include "core.hpp"
#include "global.hpp"
#include "mission.hpp"
#include "spawning.hpp"


namespace omega {
    namespace core {
        std::unique_ptr<mission::MainMission> mainMission;
        std::unique_ptr<mission::SideMission> sideMission;

        void missionInit() {
			randomEngine.seed(time(nullptr));
            mission::buildings::init();
            mission::locations::init();
            spawning::pools::init();

            //Create starting missions
            mainMission = std::make_unique<mission::MainMission>();
        }

        void missionLoop() {
            common::allPlayers = sqf::all_players();
            common::allUnits = sqf::all_units();
            common::allVehicles = sqf::vehicles();
            common::cleanGarbage();

            //respawn::vehicles();

            mainMission->update();
            if (mainMission->done) {
                mainMission->finish();
                mainMission = std::make_unique<mission::MainMission>();
            }
        }
    }
}
