#include "stdafx.hpp"
#include "task.hpp"

namespace omega {
	namespace task {
		void taskCreate(const intercept::types::side& side_, const std::vector<std::string>& names_,
			const std::vector<std::string>& descriptions_, const vector3& pos_, const int state_,
			const int priority_, bool const share_, const std::string& type_) {
			const std::vector<game_value> args = {
				static_cast<game_value>(side_),
				names_,
				descriptions_,
				pos_,
				state_,
				priority_,
				share_,
				type_
			};

			__SQF(
				_this call BIS_fnc_taskCreate;
			).capture(args);
		}

		void taskDelete(const std::string& name_, const side& side_) {
			const std::vector<game_value> args = {
				name_,
				static_cast<game_value>(side_),
			};

			__SQF(
				_this call BIS_fnc_deleteTask;
			).capture(args);
		}

		void taskSetState(const std::string& name_, const std::string& state_) {
			const std::vector<game_value> args = {
				name_,
				state_,
			};

			__SQF(
				_this call BIS_fnc_taskSetState;
			).capture(args);
		}
	}
}
