#pragma once
#include <chrono>
#include <ostream>

namespace Wecker
{
	using namespace std::literals::chrono_literals;
	class TimeSpan
	{
	public:
		TimeSpan() = default;
		TimeSpan(std::chrono::hours hour);
		TimeSpan(std::chrono::hours hour, std::chrono::minutes minutes);
		TimeSpan(std::chrono::hours hour, std::chrono::minutes minutes, std::chrono::seconds seconds);
		TimeSpan(std::chrono::seconds seconds);

		std::chrono::seconds span;
	};

	bool operator==(const TimeSpan& left, const TimeSpan& right);
	bool operator<(const TimeSpan& left, const TimeSpan& right);
	std::ostream& operator<<(std::ostream& out, const TimeSpan& dur);

	class DateTime
	{
	public:
		DateTime() = default;
		DateTime(std::chrono::hours hour);
		DateTime(std::chrono::hours hour, std::chrono::minutes minutes);
		DateTime(std::chrono::hours hour, std::chrono::seconds seconds);
		DateTime(std::chrono::hours hour, std::chrono::minutes minutes, std::chrono::seconds seconds);
		DateTime(std::chrono::minutes minutes, std::chrono::seconds seconds);
		DateTime(std::chrono::seconds seconds);

		std::chrono::system_clock::time_point m_stamp;
	};

	bool operator==(const DateTime& left, const DateTime& right);
	DateTime operator+(const DateTime& left, const TimeSpan& right);
	TimeSpan operator-(const DateTime& left, const DateTime& right);
	std::ostream& operator<<(std::ostream& out, const DateTime& date);

	//Impl
	inline TimeSpan::TimeSpan(std::chrono::hours hour)
		: span(hour)
	{}
	inline TimeSpan::TimeSpan(std::chrono::hours hour, std::chrono::minutes minutes)
		: span(hour + minutes)
	{}
	inline TimeSpan::TimeSpan(std::chrono::hours hour, std::chrono::minutes minutes, std::chrono::seconds seconds)
		: span(hour + minutes + seconds)
	{}
	inline TimeSpan::TimeSpan(std::chrono::seconds seconds)
		: span(seconds)
	{}
	inline bool operator==(const TimeSpan& left, const TimeSpan& right)
	{
		return left.span == right.span;
	}
	inline bool operator<(const TimeSpan& left, const TimeSpan& right)
	{
		return left.span < right.span;
	}
	inline std::ostream& operator<<(std::ostream& out, const TimeSpan& dur)
	{
		out << dur.span.count() << 's';
		return out;
	}

	inline DateTime::DateTime(std::chrono::hours hour)
		: m_stamp(hour)
	{}
	inline DateTime::DateTime(std::chrono::hours hour, std::chrono::minutes minutes)
		: m_stamp(hour + minutes)
	{}
	inline DateTime::DateTime(std::chrono::hours hour, std::chrono::seconds seconds)
		: m_stamp(hour + seconds)
	{}
	inline DateTime::DateTime(std::chrono::minutes minutes, std::chrono::seconds seconds)
		: m_stamp(minutes + seconds)
	{}
	inline DateTime::DateTime(std::chrono::seconds seconds)
		: m_stamp(seconds)
	{}
	inline DateTime::DateTime(std::chrono::hours hour, std::chrono::minutes minutes, std::chrono::seconds seconds)
		: m_stamp(hour + minutes + seconds)
	{}
	inline bool operator==(const DateTime& left, const DateTime& right)
	{
		return left.m_stamp == right.m_stamp;
	}
	inline DateTime operator+(const DateTime& left, const TimeSpan& right)
	{
		DateTime d;
		d.m_stamp = left.m_stamp + right.span;
		return d;
	}
	inline TimeSpan operator-(const DateTime& left, const DateTime& right)
	{
		TimeSpan result;
		// Round to next second
		result.span = std::chrono::duration_cast<std::chrono::seconds>(left.m_stamp - right.m_stamp + 500ms);
		return result;
	}
	inline std::ostream& operator<<(std::ostream& out, const DateTime& date)
	{
		auto dur = date.m_stamp.time_since_epoch();
		auto hr = std::chrono::duration_cast<std::chrono::hours>(dur);
		auto min = std::chrono::duration_cast<std::chrono::minutes>(dur - hr);
		auto sec = std::chrono::duration_cast<std::chrono::seconds>(dur - hr - min);
		out << hr.count() << "h " << min.count() << "min " << sec.count() << "s";
		return out;
	}

} // namespace Wecker
