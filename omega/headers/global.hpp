#pragma once
#include "stdafx.hpp"

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
}

