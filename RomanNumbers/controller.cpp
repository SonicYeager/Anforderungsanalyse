#include "controller.h"
#include "Interactor.h"
#include "console.h"

void Convert(const std::vector<std::string>& args)
{
	auto onRes = [](const std::string& res) { PrintResult(res); };
	auto onErr = [](const std::string& err) { PrintError(err); };
	HandleArgs(args, onRes, onErr);
}
