#include "console.h"
#include <stdio.h>
#include <iostream>

void PrintResult(const std::string& res)
{
	std::cout << res;
}

void PrintError(const std::string& msg)
{
	std::string red{"\x1B[31m"};
	std::string std{"\033[0m" };
	printf("%s%s%s\n", red.c_str(), msg.c_str(), std.c_str()); //alternative with windows.h (dont really like both)
}