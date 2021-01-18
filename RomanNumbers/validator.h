#pragma once
#include <string>
#include <functional>

void ValidateArabic(const int number, std::function<void(const int)> onValidArabic, std::function<void(std::string)> onError);
void ValidateRoman(const std::string& numberString, std::function<void(const std::string&)> onValidRoman, std::function<void(const std::string&)> onError);