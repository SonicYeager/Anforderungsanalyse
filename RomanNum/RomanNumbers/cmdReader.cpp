#include "cmdReader.h"

void ReadCMD(const std::vector<std::string>& args, std::function<void(std::filesystem::path)> onFile, std::function<void(std::string)> onText)
{
	if (args.size() == 1)
		onText(args[0]);
	else
		onFile(args[1]);
}