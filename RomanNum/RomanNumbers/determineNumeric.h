#pragma once
#include <functional>
#include <vector>
#include <string>

void DetermineNumericSystem(const std::string& cmdArgs, std::function<void(int)> onInt, std::function<void(std::string)> onString);