﻿#pragma once
#include "stdafx.hpp"

namespace omega {
    namespace spawning {
        group spawnInfantry(const vector3& pos_, const int count_, const std::vector<std::string>& pool_, const side& side_, const float skill_);
        object spawnUnit(const std::string& class_, const vector3& pos_, const group& grp_, const float skill_);
        object spawnVehicle(const std::string& class_, const vector3& pos_, const bool(&crew_)[2], const group& grp_, const float skill_);

        class Zone {
        private:
            std::vector<group> groupsGarrison{};
            std::vector<group> groupsPatrol{};
            std::vector<object> units{};
            std::vector<object> vehicles{};

        public:
            vector3 pos{};
            side sd{};
            vector3 size{};

            Zone(const vector3& pos_, const vector3& size_, const side& side_);

            void clean(); //TODO: implement

            void spawnCombined(const side& side_, const int units_ = 0, const int cars_ = 0, const int apcs_ = 0,
                               const int ifvs_ = 0, const int tanks_ = 0, const int boats_ = 0);
            void spawnInfantryGarrison(const std::vector<std::string>& pool_, const side& side_, const float skill_);
            void spawnInfantryPatrol(const int count_, const std::vector<std::string>& pool_, const side& side_, float skill_);
            void spawnVehiclePatrol(const std::vector<std::string>& pool_, const bool(&crew_)[2], float skill_);
        };

        namespace pools {
            namespace  blufor {
                namespace  units {
                    extern std::vector<std::string> regular;
                    extern std::vector<std::string> specialForces;
                }
                namespace vehicles {
                    extern std::vector<std::string> apcs;
                    extern std::vector<std::string> boats;
                    extern std::vector<std::string> cars;
                    extern std::vector<std::string> ifvs;
                    extern std::vector<std::string> tanks;
                }
            }

            namespace opfor {
                namespace units {
                    extern std::vector<std::string> regular;
                    extern std::vector<std::string> specialForces;
                }
                namespace vehicles {
                    extern std::vector<std::string> apcs;
                    extern std::vector<std::string> boats;
                    extern std::vector<std::string> cars;
                    extern std::vector<std::string> ifvs;
                    extern std::vector<std::string> tanks;
                }
            }

            namespace greenfor {
                namespace units {
                    extern std::vector<std::string> regular;
                    extern std::vector<std::string> specialForces;
                }
                namespace vehicles {
                    extern std::vector<std::string> apcs;
                    extern std::vector<std::string> boats;
                    extern std::vector<std::string> cars;
                    extern std::vector<std::string> ifvs;
                    extern std::vector<std::string> tanks;
                }
            }
        }
    }
}