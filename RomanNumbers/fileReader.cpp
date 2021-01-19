#include "fileReader.h"
#include <fstream>

void StreamFileData(const fs::path& path, std::function<void(std::string)> onTextFound)
{
	std::ifstream file;
	std::string txt;

	file.open(path);

	while (!file.eof())
	{
		std::getline(file, txt);
		onTextFound(txt);
	}
}
