#pragma once
#include "stdafx.hpp"

namespace omega {
    namespace spawning {
        group spawnInfantry(vector3& pos_, int count_, std::vector<std::string>& pool_, side& side_, float skill_);
        object spawnUnit(std::string& class_, vector3& pos_, group& grp_, float skill_);
        object spawnVehicle(std::string& class_, vector3& pos_, bool(&crew_)[2], group& grp_, float skill_);

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

            Zone(vector3& pos_, vector3& size_, side& side_);

            void clean(); //TODO: implement

            void spawnInfantryGarrison(std::vector<std::string>& pool_, side& side_, float skill_);
            void spawnInfantryPatrol(int count_, std::vector<std::string>& pool_, side& side_, float skill_);
            void spawnVehicle(std::vector<std::string>& pool_, bool(&crew_)[2], float skill_);
        };
    }
}