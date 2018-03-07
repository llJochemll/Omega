#pragma once
#include "stdafx.hpp"

namespace omega {
    namespace wrapper {
        std::vector<object> nearestObjects(const vector3& pos_, const sqf_string_list_const_ref& types_, float radius_, bool sort_,
            bool mode2D_);

        void reveal(const std::variant<object, group>& unit_, const object &target_);
    }
}