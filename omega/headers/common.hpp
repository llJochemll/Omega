#pragma once
#include "stdafx.hpp"
#include "client/sqf/common_helpers.hpp"
#include "client/pointers.hpp"

namespace omega {
    namespace common {
        float distance(vector3& pos1_, vector3& pos2_);
        vector3 findPos(vector3& centre_, vector3& radius_, int surfaceType_ = -1, float objects_ = -1.0f,
                        float maxGradient_ = -1.0f, int roads_ = -1);
        object nearestObject(vector3& pos1_, std::vector<object>& objects_, float maxDamage_ = 1.0f);
        int posRange(vector3& pos_, int distance_, std::vector<vector3>& positions_);
        int randomInt(int ceil_);
        vector3 randomPos(vector3& centre_, vector3& radius_);
        vector3 rotate(vector3& centre_, vector3& pos_, float degrees_);
    }
}
