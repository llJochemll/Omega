#include "stdafx.hpp"
#include "spawning.hpp"
#include "common.hpp"

namespace omega {
    namespace spawning {
        group spawnInfantry(const vector3& pos_, const int count_, const std::vector<std::string>& pool_, const side& side_, const float skill_) {
            auto grp = sqf::create_group(side_);

            for (auto i = 0; i < count_; i++) {
                spawnUnit(pool_.at(common::randomInt(pool_.size() - 1)), pos_, grp, skill_);
            }

            return grp;
        }

        object spawnUnit(const std::string& class_, const vector3& pos_, const group& grp_, const float skill_) {
            auto unit = sqf::create_unit(grp_, class_, pos_);
            sqf::set_skill(unit, skill_);

            return unit;
        }

        object spawnVehicle(const std::string& class_, const vector3& pos_, const bool(& crew_)[2], const group& grp_, const float skill_) {
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

        Zone::Zone(const vector3 & pos_, const vector3 & size_, const side& side_) {
            pos = pos_;
            size = size_;
            sd = side_;
        }

        void Zone::spawnInfantryGarrison(const std::vector<std::string>& pool_, const side& side_, const float skill_) {
            auto building = sqf::nearest_building(common::findPos(pos, size, 0));
            while (!sqf::in_area(building, pos, size.x, size.y, size.z, false, 0)) {
                building = sqf::nearest_building(common::findPos(pos, size, 0));
            }

            const auto grp = sqf::create_group(side_);
            for (auto i = 0; i < sqf::building_pos(building, -1).size(); ++i) {
                const auto unit = spawnUnit(pool_.at(pool_.size() - 1), sqf::building_pos(building, round(i * common::randomInt(1) + 1)).at(0), grp, skill_);
                sqf::do_stop(unit);
                units.push_back(unit);
            }

            groupsGarrison.push_back(grp);
        }

        void Zone::spawnInfantryPatrol(const int count_, const std::vector<std::string>& pool_, const side& side_, const float skill_) {
            const auto grp = spawnInfantry(common::findPos(pos, size, 0, 0), count_, pool_, side_, skill_);

            groupsPatrol.push_back(grp);
            for (const auto unit : sqf::units(grp)) {
                units.push_back(unit);
            }
        }

        void Zone::spawnVehiclePatrol(const std::vector<std::string>& pool_, const bool (&crew_)[2], const float skill_) {
            const auto grp = sqf::create_group(sd);
            const auto vehicle = spawnVehicle(pool_.at(common::randomInt(pool_.size() - 1)), common::findPos(pos, size, 0, 10.0f, -1.0f, true), crew_, grp, skill_);

            groupsPatrol.push_back(grp);
            vehicles.push_back(vehicle);
            for (const auto unit : sqf::crew(vehicle)) {
                units.push_back(unit);
            }
        }

        namespace pools {
            namespace  blufor {
                namespace  units {
                    std::vector<std::string> regular;
                    std::vector<std::string> specialForces;
                }
                namespace vehicles {
                    std::vector<std::string> apcs;
                    std::vector<std::string> boats;
                    std::vector<std::string> cars;
                    std::vector<std::string> ifvs;
                    std::vector<std::string> tanks;
                }
            }

            namespace greenfor {
                namespace units {
                    std::vector<std::string> regular;
                    std::vector<std::string> specialForces;
                }
                namespace vehicles {
                    std::vector<std::string> apcs;
                    std::vector<std::string> boats;
                    std::vector<std::string> cars;
                    std::vector<std::string> ifvs;
                    std::vector<std::string> tanks;
                }
            }

            namespace opfor {
                namespace units {
                    std::vector<std::string> regular;
                    std::vector<std::string> specialForces;
                }
                namespace vehicles {
                    std::vector<std::string> apcs;
                    std::vector<std::string> boats;
                    std::vector<std::string> cars;
                    std::vector<std::string> ifvs;
                    std::vector<std::string> tanks;
                }
            }
        }
    }
}
