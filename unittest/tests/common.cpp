#include "stdafx.hpp"
#include "CppUnitTest.h"
#include "common.hpp"
#include "../source/common.cpp"
#include "../source/global.cpp"
#include "../source/wrapper.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittest {
	TEST_CLASS(CommonTest) {
	public:
		TEST_METHOD(distance) {
			auto pos1 = vector3(0, 0, 0);
			auto pos2 = vector3(0, 0, 0);
			auto pos3 = vector3(0, 0, 0);

			//Test 0 distance
			pos1 = vector3(0, 0, 0);
			pos2 = vector3(0, 0, 0);
			Assert::AreEqual(omega::common::distance(pos1, pos2), 0.0f, 0.01f);

			//Test z has no influence
			pos1 = vector3(123, 456, 0);
			pos2 = vector3(123, 456, 86);
			pos3 = vector3(0, 0, 0);
			Assert::AreEqual(omega::common::distance(pos1, pos3), omega::common::distance(pos2, pos3), 0.01f);

			//Test both positive
			pos1 = vector3(10, 5, 0);
			pos2 = vector3(12, 8, 0);
			Assert::AreEqual(omega::common::distance(pos1, pos2), 3.605551f, 0.01f);
		}

	};
}