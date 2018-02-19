#pragma once
#include "stdafx.hpp"
#include "spawning.hpp"

namespace omega {
    namespace mission {
        class Mission {
        protected:
            std::vector<std::unique_ptr<Mission>> subMissions;
            vector3 pos;
            task task;
            std::unique_ptr<spawning::Zone> zone;
        };

        class MainMission : Mission {
            MainMission();
        };

        class SideMission : Mission {
            enum missionTypes {
                cache,
                kill,
                rescue
            };
        };

        class PriorityMission : Mission {
            
        };
    }
}
