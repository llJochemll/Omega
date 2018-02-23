#include "stdafx.hpp"
#include "core.hpp"
#include "spawning.hpp"
#include "mission.hpp"

namespace omega {
    namespace core {
        std::unique_ptr<mission::MainMission> mainMission;
        std::unique_ptr<mission::SideMission> sideMission;

        void missionInit() {
            mission::locations::init();
            spawning::pools::init();

            //Create starting missions
            mainMission = std::make_unique<mission::MainMission>();
        }

        void missionLoop() {
            if (mainMission == nullptr || mainMission->complete()) {
                mainMission = std::make_unique<mission::MainMission>();
            }
        }
    }
}
