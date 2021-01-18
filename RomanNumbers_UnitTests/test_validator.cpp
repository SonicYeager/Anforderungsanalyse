#include "gmock/gmock.h"
#include "../RomanNumbers/validator.h"

using namespace testing;

class FakeValidor
{
public:
	MOCK_METHOD(void, onValidArabic,(const int));
	MOCK_METHOD(void, onValidRoman, (const std::string&));
	MOCK_METHOD(void, onError, (std::string));
};

class TestValidator : public Test
{
public:
	void ValidateArabicUT(int nr)
	{
		ValidateArabic(nr, [this](const int nr) {fake.onValidArabic(nr); }, [this](std::string text) {fake.onError(text); });
	}
	void ValidateRomanUT(const std::string& str)
	{
		ValidateRoman(str, [this](const std::string& str) {fake.onValidRoman(str); }, [this](std::string text) {fake.onError(text); });
	}
	testing::StrictMock<FakeValidor> fake;
};


TEST_F(TestValidator, ValidateArabic_onValidArabic)
{
	EXPECT_CALL(fake, onValidArabic(6));
	ValidateArabicUT(6);
}

TEST_F(TestValidator, ValidateArabic_onError)
{
	EXPECT_CALL(fake, onError("Invalid arabic number 15121; must be in range 1..3000"));
	ValidateArabicUT(15121);
}

TEST_F(TestValidator, ValidateRoman_onValidRoman)
{
	EXPECT_CALL(fake, onValidRoman("X"));
	ValidateRomanUT("X");
}

TEST_F(TestValidator, ValidateRoman_onError)
{
	EXPECT_CALL(fake, onError("Invalid roman digit found in \"XLTII\""));
	ValidateRomanUT("XLTII");
}