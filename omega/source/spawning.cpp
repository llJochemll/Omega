#include "stdafx.hpp"
#include "spawning.hpp"
#include "common.hpp"

namespace omega {
    namespace spawning {
        group spawnInfantry(vector3& pos_, const int count_, std::vector<std::string>& pool_, side& side_, const float skill_) {
            auto grp = sqf::create_group(side_);

            for (auto i = 0; i < count_; i++) {
                spawnUnit(pool_.at(common::randomInt(pool_.size() - 1)), pos_, grp, skill_);
            }

            return grp;
        }

        object spawnUnit(std::string& class_, vector3& pos_, group& grp_, const float skill_) {
            auto unit = sqf::create_unit(grp_, class_, pos_);
            sqf::set_skill(unit, skill_);

            return unit;
        }

        object spawnVehicle(std::string& class_, vector3& pos_, bool(& crew_)[2], group& grp_, const float skill_) {
            const auto veh = sqf::create_vehicle(class_, pos_);
            if (crew_[0]) { //TODO: implement passenger spawning
                sqf::create_vehicle_crew(veh);
                sqf::join_silent(sqf::crew(veh), grp_);
                for (const auto unit : sqf::crew(veh)) {
                    sqf::set_skill(unit, skill_);
                }
            }

            return veh;
        }

        Zone::Zone(vector3 & pos_, vector3 & size_, side& side_) {
            pos = pos_;
            size = size_;
            sd = side_;
        }

        void Zone::spawnInfantryGarrison(std::vector<std::string>& pool_, side& side_, const float skill_) {
            auto pos = common::findPos(pos, size, 0);
            const auto building = sqf::nearest_building(pos);
            auto grp = sqf::create_group(side_);

            for (auto i = 0; i < sqf::building_pos(building, -1).size(); ++i) {
                
                auto buildingPos = sqf::building_pos(building, round(i * common::randomInt(1) + 1)).at(0);
                const auto unit = spawnUnit(pool_.at(pool_.size() - 1), buildingPos, grp, skill_);
                sqf::do_stop(unit);
                units.push_back(unit);
            }

            groupsGarrison.push_back(grp);
        }

        void Zone::spawnInfantryPatrol(const int count_, std::vector<std::string>& pool_, side& side_, const float skill_) {
            auto pos = common::findPos(pos, size, 0, 0);
            const auto grp = spawnInfantry(pos, count_, pool_, side_, skill_);

            groupsPatrol.push_back(grp);
            for (const auto unit : sqf::units(grp)) {
                units.push_back(unit);
            }
        }

        void Zone::spawnVehicle(std::vector<std::string>& pool_, bool (&crew_)[2], const float skill_) {
            auto pos = common::findPos(pos, size, 0, 10.0f, -1.0f, true);
            auto grp = sqf::create_group(sd);
            const auto vehicle = spawning::spawnVehicle(pool_.at(common::randomInt(pool_.size() - 1)), pos, crew_, grp, skill_);

            groupsPatrol.push_back(grp);
            vehicles.push_back(vehicle);
            for (const auto unit : sqf::crew(vehicle)) {
                units.push_back(unit);
            }
        }
    }   
}
