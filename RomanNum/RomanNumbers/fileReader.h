#pragma once
#include <functional>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;
void StreamFileData(const fs::path& path, std::function<void(std::string)> onTextFound);