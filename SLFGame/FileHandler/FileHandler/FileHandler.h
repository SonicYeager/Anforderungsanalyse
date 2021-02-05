#pragma once
#include <fstream>
#include <vector>
#include <string>

using Filename = std::string;
using Path = std::string;
using Line = std::string;
using State = std::string;
using LoadedFile = std::vector<Line>;
using Seperator = std::string;

class FileHandler
{
public:
	void SetFolder(const Path& path);
	void LoadFile(const Filename& filename);
	void SaveFile(const Filename& filename);
	Line GetLineState(const Line& line);
	void ChangeLineState(const Line& line, State state);
	void InverseLineState(const Line& line);
	void ChangeSeperator(const Seperator& seperator);
	std::vector<Line> ReturnAllLines();
private:
	LoadedFile _file = {};
	int GetLineIndex(const Line& line);

	Path _path = "D://";
	Seperator _seperator = ":";
	bool _unsavedChanges = false;
};

