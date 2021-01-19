#include "Interactor.h"
#include "converter.h"
#include "validator.h"
#include "determineNumeric.h"

void HandleArgs(const std::string& args, std::function<void(const std::string&)> onRes, std::function<void(const std::string&)> onErr)
{
	auto onArabConverted = [onRes](int num) 
	{
		auto converted = ConvertArabicNumber(num);
		onRes(converted);
	};
	auto onRomConverted = [onRes](const std::string& num)
	{
		auto converted = ConvertRomanNumber(num);
		onRes(converted);
	};
	auto onValidAra = [onArabConverted, onErr](int num) {ValidateArabic(num, onArabConverted, onErr);};
	auto onValidRom = [onRomConverted, onErr](const std::string& num) {ValidateRoman(num, onRomConverted, onErr);};

	DetermineNumericSystem(args, onValidAra, onValidRom);
}