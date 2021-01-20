#pragma once
#include <string>
#include <functional>

void HandleArgs(const std::vector<std::string>&, std::function<void(const std::string&)>, std::function<void(const std::string&)>);