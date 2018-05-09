#include "stdafx.hpp"
#include "common.hpp"
#include "mission.hpp"
#include "spawning.hpp"
#include "wrapper.hpp"
#include "task.hpp"

namespace omega {
    namespace mission {
        Mission::Mission() {
            missionId = globalMissionId++;
        }

        void Mission::finish() {
            sqf::delete_marker(mrk);
            task::taskSetState("task_" + std::to_string(missionId), "SUCCEEDED");
            zone->clean();
        }

        MainMission::MainMission() : Mission() {
            while (true) {
                pos = locations::all.at(common::randomInt(locations::all.size() - 1));
                if (std::count_if(common::allPlayers.begin(), common::allPlayers.end(), [=](auto& player_) { return common::distance(sqf::get_pos_atl(player_), pos) < 2000; }) == 0) {
                    break;
                }
            }
            radius = vector3(750, 750, 0);

            //Create zone for main AO
            zone = std::make_unique<spawning::Zone>(pos, radius, sqf::east());

            //Spawn normal units/vehicles
            zone->spawnCombined(sqf::east(), 15 + common::randomInt(5), 4 + common::randomInt(2), 2 + common::randomInt(3), 2 + common::randomInt(2), 1 + common::randomInt(2));

            //Spawn garrisoned infantry
            for (auto i = 0; i < 10 + common::randomInt(5); ++i) {
                zone->spawnInfantryGarrison(spawning::pools::opfor::units::regular, sqf::east(), 0.5f);
            }

            //Spawn units in military buildings
            for (const auto building : buildings::military::all) {
                if (common::distance(sqf::get_pos(building), pos) <= 750) {
                    zone->spawnInfantryGarrison(spawning::pools::opfor::units::regular, sqf::east(), building, 0.5f);
                }
            }

            //Create marker
            mrk = sqf::create_marker("mrk_task_" + std::to_string(missionId), pos);
            sqf::set_marker_shape(mrk, "ELLIPSE");
            sqf::set_marker_brush(mrk, "Border");
            sqf::set_marker_color(mrk, "ColorOPFOR");
            sqf::set_marker_size(mrk, vector2(radius.x, radius.y));

            //Create task
            task::taskCreate(sqf::west(), std::vector<std::string>() = {"task_" + std::to_string(missionId)},
                             std::vector<std::string>() = {"Secure the area", "Secure area", "Secure area"}, pos, 1, 10,
                             true, "attack");

            //Random priority mission
            switch (common::randomInt(1)) {
            case 0:
                subMissions.push_back(std::make_unique<RadarPriorityMission>(*this));
                break;
            case 1:
                subMissions.push_back(std::make_unique<RadioPriorityMission>(*this));
                break;
            default: ;
            }
        }

        void MainMission::finish() {
            Mission::finish();
        }

        void MainMission::update() {
            done = std::count_if(zone->units.begin(), zone->units.end(), [=](auto& unit_) { return sqf::alive(unit_); }) == 0 && std::count_if(subMissions.begin(), subMissions.end(), [=](auto& mission_) { return !mission_->done; }) == 0;

            for (auto& mission : subMissions) {
                if (mission->done) return;

                mission->update();
                if (mission->done) {
                    mission->finish();
                }
            }
        }

        PriorityMission::PriorityMission(Mission& mainMission_) : Mission() {
            pos = common::findPos(mainMission_.pos, mainMission_.radius, 10, 0, 0, 0.975f);
            radius = vector3(200, 200, 0);

            //Spawn units
            zone = std::make_unique<spawning::Zone>(pos, radius, sqf::east());
            zone->spawnCombined(sqf::east(), 4, 1);
        }

        RadarPriorityMission::RadarPriorityMission(Mission & mainMission_): PriorityMission(mainMission_) {
            radar = sqf::create_vehicle("Land_Radar_Small_F", pos);

            //Create task
            task::taskCreate(sqf::west(), std::vector<std::string>() = { "task_" + std::to_string(missionId) },
                std::vector<std::string>() = { "Priority1", "Priority: destroy radar tower", "Priority3" }, pos, 1, 10, true, "attack");
        }

        void RadarPriorityMission::finish() {
            Mission::finish();
            common::garbage.push_back(radar);
        }

        void RadarPriorityMission::update() {
            done = radar.is_nil() || radar.is_null() || !sqf::alive(radar);
        }

        RadioPriorityMission::RadioPriorityMission(Mission & mainMission_) : PriorityMission(mainMission_) {
            radio = sqf::create_vehicle("Land_TTowerBig_1_F", pos);

            //Create task
            task::taskCreate(sqf::west(), std::vector<std::string>() = { "task_" + std::to_string(missionId) },
                std::vector<std::string>() = { "Priority1", "Priority: destroy radio tower", "Priority3" }, pos, 1, 10, true, "attack");
        }

        void RadioPriorityMission::finish() {
            Mission::finish();
            common::garbage.push_back(radio);
        }

        void RadioPriorityMission::update() {
            done = radio.is_nil() || radio.is_null() || !sqf::alive(radio);
        }

        namespace buildings {
            namespace civilian {
                
            }

            namespace military {
                std::vector<object> all;
                std::vector<object> towersBig;
                std::vector<object> towersSmall;
                std::vector<object> housesBig;
                std::vector<object> housesSmall;

                void init() {
                    for (auto vec : { towersBig, towersSmall, housesBig, housesSmall }) {
                        all.reserve(all.size() + vec.size());
                        all.insert(all.end(), vec.begin(), vec.end());
                    }
                }
            }
            
            void init() {
                military::towersBig = wrapper::nearestObjects(common::worldCentre(), sqf_string_list_const_ref({
                    "Land_Cargo_Tower_V1_F",
                    "Land_Cargo_Tower_V1_No1_F",
                    "Land_Cargo_Tower_V1_No2_F",
                    "Land_Cargo_Tower_V1_No3_F",
                    "Land_Cargo_Tower_V1_No4_F",
                    "Land_Cargo_Tower_V1_No5_F",
                    "Land_Cargo_Tower_V1_No6_F",
                    "Land_Cargo_Tower_V1_No7_F",
                    "Land_Cargo_Tower_V2_F",
                    "Land_Cargo_Tower_V3_F"
                }), common::worldSize().x, false, true);

                military::towersSmall = wrapper::nearestObjects(common::worldCentre(), sqf_string_list_const_ref({
                    "Land_Cargo_Patrol_V1_F",
                    "Land_Cargo_Patrol_V2_F",
                    "Land_Cargo_Patrol_V3_F"
                }), common::worldSize().x, false, true);

                military::housesBig = wrapper::nearestObjects(common::worldCentre(), sqf_string_list_const_ref({
                    "Land_Dome_Big_F",
                    "Land_Dome_Small_F",
                    "Land_BagBunker_Large_F",
                    "Land_BagBunker_Tower_F",
                    "Land_Cargo_HQ_V1_F",
                    "Land_Cargo_HQ_V2_F",
                    "Land_Cargo_HQ_V3_F"
                }), common::worldSize().x, false, true);

                military::housesSmall = wrapper::nearestObjects(common::worldCentre(), sqf_string_list_const_ref({
                    "Land_BagBunker_Small_F",
                    "Land_Cargo_House_V1_F",
                    "Land_Cargo_House_V2_F",
                    "Land_Cargo_House_V3_F",
                    "Land_HBarrierTower_F",
                    "Land_i_Barracks_V1_F",
                    "Land_i_Barracks_V2_F",
                    "Land_u_Barracks_V2_F",
                    "Land_MilOffices_V1_F"
                }), common::worldSize().x, false, true);

                military::init();
            }
        }

        namespace locations {
            std::vector<vector3> all;
            std::vector<vector3> airfields;
            std::vector<vector3> bases;
            std::vector<vector3> capitals;
            std::vector<vector3> cities;
            std::vector<vector3> factories;
            std::vector<vector3> villages;

            void init() {
                for (const auto tower : buildings::military::towersBig) {
                    const auto pos = sqf::get_pos(tower);
                    if (std::count_if(buildings::military::all.begin(), buildings::military::all.end(), [=](auto& building_) { return common::distance(sqf::get_pos_atl(building_), pos) < 300; }) == 0) {
                        bases.push_back(sqf::get_pos(tower));
                    }
                }

                for (const auto house : buildings::military::housesBig) {
                    const auto pos = sqf::get_pos(house);
                    if (std::count_if(buildings::military::all.begin(), buildings::military::all.end(), [=](auto& building_) { return common::distance(sqf::get_pos_atl(building_), pos) < 300; }) == 0) {
                        bases.push_back(sqf::get_pos(house));
                    }
                }

                for (const auto location : sqf::nearest_locations(common::worldCentre(), sqf_string_list_const_ref({ "NameCityCapital" }), common::worldSize().x)) {
                    capitals.push_back(sqf::get_pos(location));
                }

                for (const auto location : sqf::nearest_locations(common::worldCentre(), sqf_string_list_const_ref({ "NameCity" }), common::worldSize().x)) {
                    cities.push_back(sqf::get_pos(location));
                }

                for (const auto location : sqf::nearest_locations(common::worldCentre(), sqf_string_list_const_ref({ "NameVillage" }), common::worldSize().x)) {
                    villages.push_back(sqf::get_pos(location));
                }

                for (auto vec : { airfields, bases, capitals, cities, factories, villages }) {
                    all.reserve(all.size() + vec.size());
                    all.insert(all.end(), vec.begin(), vec.end());
                }
            }
        }
    }
}
