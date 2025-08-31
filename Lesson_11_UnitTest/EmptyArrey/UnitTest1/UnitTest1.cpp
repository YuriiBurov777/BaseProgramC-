#include "pch.h"
#include "CppUnitTest.h"
#include "../EmptyArrey/ExstenArrey.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Mean) {
			ExtArray<int> v1{ 0 };
			Assert::AreEqual(v1.mean(), 0.0);
		}
		TEST_METHOD(Median) {
			ExtArray<double> v2{ 0 };
			Assert::AreEqual(0.0, v2.median());
		}
		TEST_METHOD(Mode) {
			ExtArray<int> v1{ 0 };
			Assert::AreEqual(0, v1.mode().first );
			Assert::AreEqual(0, v1.mode().second);
		}
	};
}

