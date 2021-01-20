#pragma once
#include <string>
#include <vector>
#include <functional>
#include <filesystem>

void ReadCMD(const std::vector<std::string>&, std::function<void(std::filesystem::path)>, std::function<void(std::string)>);