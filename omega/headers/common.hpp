#pragma once
#include "client/sqf/common_helpers.hpp"
#include "client/pointers.hpp"

namespace omega {
    namespace common {
        extern std::vector<group> allGroups;
        extern std::vector<object> allPlayers;
        extern std::vector<object> allUnits;
        extern std::vector<object> allVehicles;
        extern std::vector<object> garbage;

        void cleanGarbage();
        float distance(const vector3& pos1_, const vector3& pos2_);
        vector3 findPos(const vector3& centre_, const vector3& radius_, const int size_, const int surfaceType_ = -1,
                        const float objects_ = -1.0f, const float maxGradient_ = -1.0f, const int roads_ = -1);
        object nearestObject(const vector3& pos1_, const std::vector<object>& objects_, const float maxDamage_ = 1.0f);
        int posRange(const vector3& pos_, const int distance_, const std::vector<vector3>& positions_);
        int randomInt(const int ceil_);
        vector3 randomPos(const vector3& centre_, const vector3& radius_);
        vector3 rotate(const vector3& centre_, const vector3& pos_, const float degrees_);
        vector3 worldCentre();
        vector3 worldSize();
    }
}
