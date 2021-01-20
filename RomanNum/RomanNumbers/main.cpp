#include "controller.h"
#include <iostream>
int main(int argc, char* argv[])
{
	Convert(std::vector<std::string>(argv+1, argv + argc));
	std::cin;
}