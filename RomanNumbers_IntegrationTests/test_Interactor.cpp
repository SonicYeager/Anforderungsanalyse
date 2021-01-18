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

	HandleArgs("XLII", std::bind(&FakeConsole::PrintResult, &fcon, std::placeholders::_1), std::bind(&FakeConsole::PrintError, &fcon, std::placeholders::_1));
}