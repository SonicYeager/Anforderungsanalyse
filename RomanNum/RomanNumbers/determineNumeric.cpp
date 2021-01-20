#include "determineNumeric.h"

void DetermineNumericSystem(const std::string& cmdArgs, std::function<void(int)> onInt, std::function<void(std::string)> onString)
{
	if (cmdArgs[0] >= 65 && cmdArgs[0] <= 90)
		onString(cmdArgs);
	else
		onInt(std::stoi(cmdArgs));
}
