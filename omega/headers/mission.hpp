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
        public:
            MainMission();

            bool complete() const;
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

        namespace locations {
            extern std::vector<vector3> airfields;
            extern std::vector<vector3> bases;
            extern std::vector<vector3> capitals;
            extern std::vector<vector3> cities;
            extern std::vector<vector3> factories;
            extern std::vector<vector3> villages;

            std::vector<vector3> all();
            void init();
        }
    }
}
