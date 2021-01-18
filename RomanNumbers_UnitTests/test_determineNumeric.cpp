#include "gmock/gmock.h"
#include "../RomanNumbers/determineNumeric.h"

using namespace testing;

class FakeDetermineNumeric
{
public:
	MOCK_METHOD(void, onInt, (int));
	MOCK_METHOD(void, onString, (std::string));
};

class TestDetermineNumericSystem : public Test
{
public:
	void DetermineNumericSystemUT(const std::string& str)
	{
		DetermineNumericSystem(str, [this](const int nr) {fake.onInt(nr); }, [this](const std::string& text) {fake.onString(text); });
	}
	testing::StrictMock<FakeDetermineNumeric> fake;
};
TEST_F(TestDetermineNumericSystem, DetermineNumericSystem_onInt)
{
	EXPECT_CALL(fake, onInt(6));
	DetermineNumericSystemUT("6");
	//DetermineNumericSystem("6");
	//int expected = 6;
}

TEST_F(TestDetermineNumericSystem, DetermineNumericSystem_onString)
{
	EXPECT_CALL(fake, onString("VI"));
	DetermineNumericSystemUT("VI");
}