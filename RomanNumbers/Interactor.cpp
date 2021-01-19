#include "Interactor.h"
#include "converter.h"
#include "validator.h"
#include "determineNumeric.h"
#include "cmdReader.h"
#include "fileReader.h"

void ConvertNumber(const std::string& args, std::function<void(const std::string&)> onRes, std::function<void(const std::string&)> onErr)
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
	auto onValidAra = [onArabConverted, onErr](int num) {ValidateArabic(num, onArabConverted, onErr); };
	auto onValidRom = [onRomConverted, onErr](const std::string& num) {ValidateRoman(num, onRomConverted, onErr); };
	DetermineNumericSystem(args, onValidAra, onValidRom);
}
void HandleArgs(const std::vector<std::string>& args, std::function<void(const std::string&)> onRes, std::function<void(const std::string&)> onErr)
{
	auto onTextFound = [onRes,onErr](const std::string& text)
	{
		ConvertNumber(text, onRes, onErr);
	};

	auto onFile = [onTextFound](const std::filesystem::path& path)
	{
		StreamFileData(path, onTextFound);
	};

	auto onText = [onRes, onErr](const std::string& text)
	{
		ConvertNumber(text, onRes, onErr);
	};
	ReadCMD(args, onFile, onText);
}