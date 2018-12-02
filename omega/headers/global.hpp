#pragma once
#include "stdafx.hpp"
#include "random"

namespace omega {
	class EngineLock {
	public:
		EngineLock();
		explicit EngineLock(const bool locked_);
		~EngineLock();
		void lock();
		void unlock();

	private:
		bool locked = false;
	};

	inline std::default_random_engine randomEngine;
}

