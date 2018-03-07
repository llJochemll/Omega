#pragma once
#include "stdafx.hpp"
namespace omega {
	namespace task {
		void taskCreate(const side& side_, const std::vector<std::string>& names_, const std::vector<std::string>& descriptions_, const vector3& pos_, const int state_, const int priority_, const bool share_, const std::string& type_);
		void taskDelete(const std::string& name_, const side& side_);
		void taskSetState(const std::string& name_, const std::string& state_);
	}
}
