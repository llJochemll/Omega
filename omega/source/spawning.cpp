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

        void Zone::spawnCombined(const side& side_, const int units_, const int cars_, const int apcs_, const int ifvs_,
                                 const int tanks_, const int boats_) {
            std::vector<std::string> poolUnits;
            std::vector<std::string> poolCars;
            std::vector<std::string> poolApcs;
            std::vector<std::string> poolIfvs;
            std::vector<std::string> poolTanks;
            std::vector<std::string> poolBoats;

            if (side_ == sqf::west()) {
                poolUnits = pools::blufor::units::regular;
                poolCars = pools::blufor::vehicles::cars;
                poolApcs = pools::blufor::vehicles::apcs;
                poolIfvs = pools::blufor::vehicles::ifvs;
                poolTanks = pools::blufor::vehicles::tanks;
                poolBoats = pools::blufor::vehicles::boats;
            } else if (side_ == sqf::independent()) {
                poolUnits = pools::greenfor::units::regular;
                poolCars = pools::greenfor::vehicles::cars;
                poolApcs = pools::greenfor::vehicles::apcs;
                poolIfvs = pools::greenfor::vehicles::ifvs;
                poolTanks = pools::greenfor::vehicles::tanks;
                poolBoats = pools::greenfor::vehicles::boats;
            } else if (side_ == sqf::east()) {
                poolUnits = pools::opfor::units::regular;
                poolCars = pools::opfor::vehicles::cars;
                poolApcs = pools::opfor::vehicles::apcs;
                poolIfvs = pools::opfor::vehicles::ifvs;
                poolTanks = pools::opfor::vehicles::tanks;
                poolBoats = pools::opfor::vehicles::boats;
            }
            
            //Spawn patrolling infantry
            for (auto i = 0; i < units_; ++i) {
                spawnInfantryPatrol(5, poolUnits, sqf::east(), 0.5f);
            }

            //Spawn vehicles: car
            for (auto i = 0; i < cars_; ++i) {
                spawnVehiclePatrol(poolCars, { true, false }, 0.5f);
            }

            //Spawn vehicles: apc
            for (auto i = 0; i < apcs_; ++i) {
                spawnVehiclePatrol(poolApcs, { true, false }, 0.5f);
            }

            //Spawn vehicles: ifv
            for (auto i = 0; i < ifvs_; ++i) {
                spawnVehiclePatrol(poolIfvs, { true, false }, 0.5f);
            }

            //Spawn vehicles: tank
            for (auto i = 0; i < tanks_; ++i) {
                spawnVehiclePatrol(poolTanks, { true, false }, 0.5f);
            }

            //Spawn vehicles: boat
            for (auto i = 0; i < boats_; ++i) {
                spawnVehiclePatrol(poolBoats, { true, false }, 0.5f);
            }
        }

        void Zone::spawnInfantryGarrison(const std::vector<std::string>& pool_, const side& side_, const float skill_) {
            auto building = sqf::nearest_building(common::findPos(pos, size, 0));
            while (!sqf::in_area(building, pos, size.x, size.y, size.z, false, 0)) {
                building = sqf::nearest_building(common::findPos(pos, size, 0));
            }

            const auto grp = sqf::create_group(side_);
            for (auto i = 0; i < sqf::building_pos(building, -1).size() / 2; ++i) {
                const auto unit = spawnUnit(pool_.at(common::randomInt(pool_.size() - 1)), sqf::building_pos(building, round(i * common::randomInt(1) + 1)).at(0), grp, skill_);
                sqf::do_stop(unit);
                units.push_back(unit);
            }

            groupsGarrison.push_back(grp);
        }

        void Zone::spawnInfantryPatrol(const int count_, const std::vector<std::string>& pool_, const side& side_, const float skill_) {
            const auto grp = spawnInfantry(common::findPos(pos, size, 1, 0, 0), count_, pool_, side_, skill_);

            groupsPatrol.push_back(grp);
            for (const auto unit : sqf::units(grp)) {
                units.push_back(unit);
            }
        }

        void Zone::spawnVehiclePatrol(const std::vector<std::string>& pool_, const bool (&crew_)[2], const float skill_) {
            const auto grp = sqf::create_group(sd);
            const auto vehicle = spawnVehicle(pool_.at(common::randomInt(pool_.size() - 1)), common::findPos(pos, size, 10, 0, 10, -1, true), crew_, grp, skill_);

            groupsPatrol.push_back(grp);
            vehicles.push_back(vehicle);
            for (const auto unit : sqf::crew(vehicle)) {
                units.push_back(unit);
            }
        }

        namespace pools {
            void init() {
                opfor::units::regular = {
                    "O_Soldier_A_F", 
                    "O_Soldier_AR_F", 
                    "O_medic_F", 
                    "O_Soldier_GL_F", 
                    "O_HeavyGunner_F",
                    "O_soldier_M_F", 
                    "O_Soldier_AA_F", 
                    "O_Soldier_AT_F", 
                    "O_Soldier_F", 
                    "O_Soldier_LAT_F",
                    "O_Sharpshooter_F", 
                    "O_Soldier_SL_F", 
                    "O_Soldier_TL_F"
                };
                opfor::units::special = {
                    "O_V_Soldier_hex_F", 
                    "O_V_Soldier_Medic_hex_F", 
                    "O_V_Soldier_TL_hex_F", 
                    "O_V_Soldier_JTAC_hex_F"
                };
                opfor::vehicles::apcs = {
                    "O_APC_Wheeled_02_rcws_F" 
                };
                opfor::vehicles::boats = {
                };
                opfor::vehicles::cars = {
                    "O_MRAP_02_F","O_MRAP_02_gmg_F","O_MRAP_02_hmg_F"
                };
                opfor::vehicles::ifvs = {
                    "O_APC_Tracked_02_cannon_F"
                };
                opfor::vehicles::tanks = {
                    "O_MBT_02_cannon_F"
                };
            }

            namespace  blufor {
                namespace  units {
                    std::vector<std::string> regular;
                    std::vector<std::string> special;
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
                    std::vector<std::string> special;
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
                    std::vector<std::string> special;
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
