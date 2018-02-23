#pragma once
#include "stdafx.hpp"

namespace omega {
    namespace wrapper {
        std::vector<object> nearestObjects(vector3& pos_, sqf_string_list_const_ref types_, float radius_, bool sort_,
            bool mode2D_);

        void reveal(std::variant<object, group> unit_, object &target_);
    }
}