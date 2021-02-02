#pragma once
#include "Times.h"
#include <string>

namespace Wecker
{
	namespace Times
	{
		std::string SpanToString(const TimeSpan&);
		std::string DateToString(const DateTime&);
		DateTime NextDate(const DateTime& from, const DateTime& timeOfDay);
		TimeSpan SpanFromString(const std::string& s);
		DateTime DateFromString(const std::string& s);
		DateTime Now();
	} // namespace Times
} // namespace Wecker
