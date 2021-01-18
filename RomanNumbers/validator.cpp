#include "validator.h"
#include <vector>

void ValidateArabic(const int number, std::function<void(const int)> onValidArabic, std::function<void(std::string)> onError)
{
	if (number >= 1 && number <= 3000)
		onValidArabic(number);
	else
		onError("Invalid arabic number " + std::to_string(number) + "; must be in range 1..3000");
}

void ValidateRoman(const std::string& numberString, std::function<void(const std::string&)> onValidRoman, std::function<void(const std::string&)> onError)
{
	std::vector<char> romanDigits = { 'I', 'V', 'X', 'L', 'C', 'D', 'M' };
	bool errorFound = false;
	for (const auto& nbr : numberString)
		for (const auto& digit : romanDigits)
			if (nbr != digit)
			{
				errorFound = true;
				onError("Invalid roman digit found in \"" + numberString + "\"");
				break;
			}
	if (!errorFound)
		onValidRoman(numberString);
}
