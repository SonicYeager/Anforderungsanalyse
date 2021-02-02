#include "TimesConversion.h"
#include <sstream>
#include <iomanip>

namespace Wecker
{
	namespace Times
	{
		using Days = std::chrono::duration<int, std::ratio_multiply<std::chrono::hours::period, std::ratio<24>>::type>;
		std::string ToString(std::chrono::system_clock::duration timeOfDay)
		{
			std::chrono::hours h = std::chrono::duration_cast<std::chrono::hours>(timeOfDay);
			timeOfDay -= h;
			std::chrono::minutes m = std::chrono::duration_cast<std::chrono::minutes>(timeOfDay);
			timeOfDay -= m;
			std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(timeOfDay);
			std::stringstream out;
			out << std::setfill('0') << std::setw(2) << h.count() << ':' << std::setw(2) << m.count() << ':' << std::setw(2) << s.count();
			return out.str();
		}

		template<typename T>
		T FromString(const std::string& s)
		{
			std::stringstream in(s);
			int hours = 0;
			in >> hours;
			in.ignore();
			int minutes = 0;
			in >> minutes;
			int seconds = 0;
			in.ignore();
			in >> seconds;
			return T{std::chrono::hours(hours), std::chrono::minutes(minutes), std::chrono::seconds(seconds)};
		}

		std::string SpanToString(const TimeSpan& s)
		{
			return ToString(s.span);
		}
		std::string DateToString(const DateTime& d)
		{
			std::chrono::system_clock::duration tp = d.m_stamp.time_since_epoch();
			Days days = std::chrono::duration_cast<Days>(tp);
			tp -= days;
			return ToString(tp);
		}
		TimeSpan SpanFromString(const std::string& s)
		{
			return FromString<TimeSpan>(s);
		}
		DateTime DateFromString(const std::string& s)
		{
			return FromString<DateTime>(s);
		}

		DateTime NextDate(const DateTime& from, const DateTime& timeOfDay)
		{
			DateTime result;
			Days days = std::chrono::duration_cast<Days>(from.m_stamp.time_since_epoch());
			auto timeOfDayStamp = from.m_stamp - days;
			if(timeOfDay.m_stamp < timeOfDayStamp)
				days += Days(1);
			result.m_stamp = days + timeOfDay.m_stamp;
			return result;
		}

		DateTime Now()
		{
			DateTime result;
			result.m_stamp = std::chrono::system_clock::now();
			return result;
		}
	} // namespace Times
} // namespace Wecker
