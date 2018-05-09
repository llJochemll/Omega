#pragma once
#include "stdafx.hpp"
#include "spawning.hpp"

namespace omega {
    namespace mission {
        class Mission {
        public:
            inline static int globalMissionId = -1;
            bool done = false;
            int missionId = -1;
            marker mrk = "";
            std::vector<std::unique_ptr<Mission>> subMissions{};
            vector3 pos = vector3(0,0,0);
            vector3 radius = vector3(0, 0, 0);
            std::vector<std::string> task{};
            std::unique_ptr<spawning::Zone> zone{};

            Mission();
            virtual ~Mission() = default;

            virtual void finish();
            virtual void update() = 0;
        };

        class MainMission : public Mission {
        public:
            MainMission();

            void finish() override;
            void update() override;
        };

        class PriorityMission : public Mission {
        public:
            explicit PriorityMission(Mission& mainMission_);
        };

        class RadarPriorityMission : public PriorityMission {
        public:
            object radar;

            explicit RadarPriorityMission(Mission& mainMission_);

            void finish() override;
            void update() override;
        };

        class RadioPriorityMission : public PriorityMission {
        public:
            object radio;

            explicit RadioPriorityMission(Mission& mainMission_);

            void finish() override;
            void update() override;
        };

        class SideMission : Mission {
            enum missionTypes {
                cache,
                kill,
                rescue
            };
        };

        namespace buildings {
            namespace civilian {

            }

            namespace military {
                extern std::vector<object> all;
                extern std::vector<object> towersBig;
                extern std::vector<object> towersSmall;
                extern std::vector<object> housesBig;
                extern std::vector<object> housesSmall;
            }

            void init();
        }

        namespace locations {
            extern std::vector<vector3> all;
            extern std::vector<vector3> airfields;
            extern std::vector<vector3> bases;
            extern std::vector<vector3> capitals;
            extern std::vector<vector3> cities;
            extern std::vector<vector3> factories;
            extern std::vector<vector3> villages;

            void init();
        }
    }
}
