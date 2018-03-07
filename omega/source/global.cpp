#include "stdafx.hpp"
#include "global.hpp"

namespace omega {
	EngineLock::EngineLock() = default;

	EngineLock::EngineLock(const bool locked_) {
		locked = false;

		if (locked_) {
			while (!locked) {
				lock();
				break;
			}
		}
	}

	EngineLock::~EngineLock() {
		unlock();
	}

	void EngineLock::lock() {
		if (!locked) {
			client::host::functions.invoker_lock();
			locked = true;
		}
	}

	void EngineLock::unlock() {
		if (locked) {
			client::host::functions.invoker_unlock();
			locked = false;
		}
	}
}