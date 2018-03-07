#pragma once
#include "stdafx.hpp"
#include "spawning.hpp"

namespace omega {
    namespace mission {
        class Mission {
        protected:
            inline static int globalMissionId = -1;
            int missionId = -1;
            marker mrk = "";
            std::vector<std::unique_ptr<Mission>> subMissions{};
            vector3 pos = vector3(0,0,0);
            std::vector<std::string> task{};
            std::unique_ptr<spawning::Zone> zone{};

            Mission();
        };

        class MainMission : Mission {
        public:
            MainMission();

            bool complete() const;
            void finish() const;
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

        namespace buildings {
            namespace civilian {

            }

            namespace military {
                extern std::vector<object> towersBig;
                extern std::vector<object> towersSmall;
                extern std::vector<object> housesBig;
                extern std::vector<object> housesSmall;

                std::vector<object> all();
            }

            void init();
        }

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
