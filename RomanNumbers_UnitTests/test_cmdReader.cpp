#include "gmock/gmock.h"
#include "../RomanNumbers/cmdReader.h"

class FakeReadCMDEvents
{
public:
	MOCK_METHOD(void, onFile, (const std::filesystem::path&));
	MOCK_METHOD(void, onText, (const std::string&));
};

TEST(TestCmdReader, ReadCMD_fnumberstxt_CallonFile)
{
	::testing::StrictMock<FakeReadCMDEvents> fint{};
	EXPECT_CALL(fint, onFile(std::filesystem::path("numbers.txt")));
	std::vector<std::string> args
	{
		"-f",
		"numbers.txt"
	};

	ReadCMD(args, std::bind(&FakeReadCMDEvents::onFile, &fint, std::placeholders::_1), std::bind(&FakeReadCMDEvents::onText, &fint, std::placeholders::_1));
}

TEST(TestCmdReader, ReadCMD_IX_CallonText)
{
	::testing::StrictMock<FakeReadCMDEvents> fint{};
	EXPECT_CALL(fint, onText("IX"));
	std::vector<std::string> args
	{
		"IX"
	};

	ReadCMD(args, std::bind(&FakeReadCMDEvents::onFile, &fint, std::placeholders::_1), std::bind(&FakeReadCMDEvents::onText, &fint, std::placeholders::_1));
}