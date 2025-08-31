#include "pch.h"
#include "CppUnitTest.h"
#include "../checkSum/CheckSum.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(checkSum)
		{
			ExtArray<int> v1{1,1,0,1 };
			try
			{
				v1.checkSum();
				Logger::WriteMessage(L"===������� ������� � �����===");
				Assert::AreEqual(3, v1.checkSum());
			}
			catch (const std::invalid_argument& e)
			{
				std::string message(e.what());
				Logger::WriteMessage(L"===���� ������ ���� ������===");
				Assert::IsTrue(message.find("Data") != std::string::npos, L"�� ������� logic_error");
			}
			catch (const std::logic_error& e)
			{
				std::string message(e.what());
				Logger::WriteMessage(L"===���� ������ int �������� �������� �������� �� 0 � 1===");
				//Assert::IsTrue(message.find("array") != std::string::npos, L"�� ������� Trow invalid_argument");
			}
		}
	};
}
