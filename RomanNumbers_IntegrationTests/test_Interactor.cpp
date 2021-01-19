#include "../RomanNumbers/Interactor.h"
#include "../TestFramework/GoogleMock/gmock/gmock.h"

class FakeConsole
{
public:
	MOCK_METHOD(void, PrintResult, (const std::string&));
	MOCK_METHOD(void, PrintError, (const std::string&));
};

TEST(TestInteractor, HandleArgs_convertromanXLII_ExpectCall42)
{
	::testing::StrictMock<FakeConsole> fcon{};
	EXPECT_CALL(fcon, PrintResult("42"));

	HandleArgs({"XLII"}, std::bind(&FakeConsole::PrintResult, &fcon, std::placeholders::_1), std::bind(&FakeConsole::PrintError, &fcon, std::placeholders::_1));
}

TEST(TestInteractor, HandleArgs_convertroman2015_ExpectCallMMXV)
{
	::testing::StrictMock<FakeConsole> fcon{};
	EXPECT_CALL(fcon, PrintResult("MMXV"));

	HandleArgs({ "2015" }, std::bind(&FakeConsole::PrintResult, &fcon, std::placeholders::_1), std::bind(&FakeConsole::PrintError, &fcon, std::placeholders::_1));
}

TEST(TestInteractor, HandleArgs_convertromanXLTII_ExpectCallErrMsg)
{
	::testing::StrictMock<FakeConsole> fcon{};
	EXPECT_CALL(fcon, PrintError("Invalid roman digit found in \"XLTII\""));

	HandleArgs({ "XLTII" }, std::bind(&FakeConsole::PrintResult, &fcon, std::placeholders::_1), std::bind(&FakeConsole::PrintError, &fcon, std::placeholders::_1));
}

TEST(TestInteractor, HandleArgs_convertroman15212_ExpectCallErrMsg)
{
	::testing::StrictMock<FakeConsole> fcon{};
	EXPECT_CALL(fcon, PrintError("Invalid arabic number 15212; must be in range 1..3000"));

	HandleArgs({ "15212" }, std::bind(&FakeConsole::PrintResult, &fcon, std::placeholders::_1), std::bind(&FakeConsole::PrintError, &fcon, std::placeholders::_1));
}

TEST(TestInteractor, HandleArgs_fnumberstxt_ExpectCall42MMXV)
{
	::testing::StrictMock<FakeConsole> fcon{};
	EXPECT_CALL(fcon, PrintResult("42"));
	EXPECT_CALL(fcon, PrintResult("MMXV"));

	HandleArgs({ "-f", "numbersRes.txt" }, std::bind(&FakeConsole::PrintResult, &fcon, std::placeholders::_1), std::bind(&FakeConsole::PrintError, &fcon, std::placeholders::_1));
}

TEST(TestInteractor, HandleArgs_fnumberstxt_ExpectCallTwoErrMsg)
{
	::testing::StrictMock<FakeConsole> fcon{};
	EXPECT_CALL(fcon, PrintError("Invalid roman digit found in \"XLTII\""));
	EXPECT_CALL(fcon, PrintError("Invalid arabic number 15212; must be in range 1..3000"));

	HandleArgs({ "-f", "numbersErr.txt" }, std::bind(&FakeConsole::PrintResult, &fcon, std::placeholders::_1), std::bind(&FakeConsole::PrintError, &fcon, std::placeholders::_1));
}