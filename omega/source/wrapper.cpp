#include "stdafx.hpp"
#include "wrapper.hpp"

namespace omega {
	namespace wrapper {
		std::vector<object> nearestObjects(vector3& pos_, sqf_string_list_const_ref types_, const float radius_, const bool sort_,
		                                    const bool mode2D_) {
			auto_array<game_value> types(types_.begin(), types_.end());

			const game_value params({
				pos_,
				std::move(types),
				radius_,
				sort_,
				mode2D_
				});

			return sqf::__helpers::__convert_to_objects_vector(
				host::functions.invoke_raw_unary(__sqf::unary__nearestobjects__array__ret__array, params));
		}

		void reveal(std::variant<object, group> unit_, const object &target_) {
			game_value param_left;
			switch (unit_.index()) {
			case 0: param_left = std::get<0>(unit_); break;
			case 1: param_left = std::get<1>(unit_); break;
			default:;
			}

			host::functions.invoke_raw_binary(__sqf::binary__reveal__object_group__object__ret__nothing, param_left, target_);
		}
	}
}