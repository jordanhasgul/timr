#pragma once
#include <chrono>
#include <ratio>
#include <iostream>

namespace timr
{
	using nanoseconds  = std::ratio<1, 1000000000>;
	using microseconds = std::ratio<1, 1000000>;
	using milliseconds = std::ratio<1, 1000>;
	using seconds	   = std::ratio<1, 1>;

	constexpr inline const char* units(nanoseconds)   noexcept { return "nanoseconds";  }
	constexpr inline const char* units(microseconds)  noexcept { return "microseconds"; }
	constexpr inline const char* units(milliseconds)  noexcept { return "milliseconds"; }
	constexpr inline const char* units(seconds)	  noexcept { return "seconds";      }

	template<typename unit = seconds>
	class Timer
	{
	private:
		const std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<double, unit>> TIME_ZERO = std::chrono::steady_clock::now();
		const std::chrono::duration<double, unit> DURATION_ZERO = std::chrono::duration<double, unit>::zero();

		std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<double, unit>> m_start;
		std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<double, unit>> m_end;
		std::chrono::duration<double, unit> m_timeElapsed;
		bool m_paused;

	public:
		Timer();
		~Timer();

		void pause();
		void resume();
		void reset();

	};

	template<typename unit>
	inline Timer<unit>::Timer()
		: m_start(TIME_ZERO), m_end(TIME_ZERO), m_timeElapsed(DURATION_ZERO), m_paused(false)
	{
	}
	template<typename unit>
	inline Timer<unit>::~Timer()
	{
		m_end = std::chrono::steady_clock::now();
		m_timeElapsed += m_end - m_start;

		std::clog << m_timeElapsed.count() << units(decltype(unit()) {}) << std::endl;
	}

	template<typename unit>
	inline void Timer<unit>::pause()
	{
		if (!m_paused)
		{
			m_end = std::chrono::steady_clock::now();
			m_timeElapsed += m_end - m_start;
			m_paused = true;
		}
	}
	template<typename unit>
	inline void Timer<unit>::resume()
	{
		if (m_paused)
		{
			m_start = std::chrono::steady_clock::now();
			m_paused = false;
		}
	}
	template<typename unit>
	inline void Timer<unit>::reset()
	{
		m_start = std::chrono::steady_clock::now();
		m_timeElapsed = DURATION_ZERO;
	}
}
