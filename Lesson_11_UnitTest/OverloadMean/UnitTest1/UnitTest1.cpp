#include "pch.h"
#include "CppUnitTest.h"
#include "../OverloadMean/OverMean.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		// Перегруженный метод Mean
		TEST_METHOD(Mean)
		{
			ExtArray<int> v1{ 4, 2, 7, 2, 5, 5, 0, 5, 5 };
			try
			{

				v1.mean(3, 5);
				Assert::AreEqual(4.0, v1.mean(3,5));
				Logger::WriteMessage(L"=== Norma  ===");

			}
			catch (const std::invalid_argument& e)
			{
				
				Logger::WriteMessage(L"=== invalid_argument  ===");
				std::string message(e.what());
				Assert::IsTrue(message.find("Start") != std::string::npos, L"Not Start word");
				
			}
			catch (const std::range_error& e)
			{

				Logger::WriteMessage(L"=== range_error  ===");
				std::string message(e.what());
				Assert::IsTrue(message.find("End") != std::string::npos, L"Not Tnd word");

			}
		};
		
	};
}
