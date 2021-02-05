#include "FileHandler.h"
#include <iostream>

int main()
{
	FileHandler fh;

	fh.SetFolder("D://test/");
	fh.ChangeSeperator("=");
	fh.LoadFile("test.txt");
	fh.ChangeLineState("Buch", "Faust");
	fh.InverseLineState("vorhanden");
	std::cout << fh.GetLineState("Buch");
	fh.SaveFile("test.txt");
	system("pause");
}