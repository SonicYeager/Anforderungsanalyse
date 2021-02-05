#include "FileHandler.h"

void FileHandler::SetFolder(const Path& path)
{
	_path = path;
}

void FileHandler::LoadFile(const Filename& filename)
{
	std::ifstream file;
	file.open(_path + filename);
	Line line;
	while (file)
	{
		std::getline(file, line);
		_file.push_back(line);
	}
	file.close();
}

void FileHandler::SaveFile(const Filename& filename)
{
	if (_unsavedChanges)
	{
		std::ofstream file;
		file.open(_path + filename);
		for (Line line : _file)
		{
			file << line << std::endl;
		}
		_unsavedChanges = false;
		file.close();
	}
}

Line FileHandler::GetLineState(const Line& line)
{
	Line result = "";
	int idx = GetLineIndex(line);

	if (idx != -1)
		for (int i = line.size() + 1; i < _file[idx].size(); i++)
			result += _file[idx][i];

	return result;
}

void FileHandler::ChangeLineState(const Line& line, State state)
{
	int idx = GetLineIndex(line);

	if (idx != -1)
	{
		_file[idx] = line + _seperator + state;
		_unsavedChanges = true;
	}
}

void FileHandler::InverseLineState(const Line& line)
{
	int idx = GetLineIndex(line);

	if (idx != -1)
	{
		if (_file[idx].back() == '0')
			_file[idx].back() = '1';
		else if (_file[idx].back() == '1')
			_file[idx].back() = '0';
		_unsavedChanges = true;
	}
}

void FileHandler::ChangeSeperator(const Seperator& seperator)
{
	_seperator = seperator;
}

std::vector<Line> FileHandler::ReturnAllLines()
{
	return _file;
}

int FileHandler::GetLineIndex(const Line& line)
{
	int wordFoundAt = 0;
	int index = -1;
	for (int i = 0; i < _file.size(); i++)
	{
		wordFoundAt = _file[i].rfind(line + _seperator, 0);
		if (wordFoundAt == 0)
			index = i;
	}
	return index;
}
