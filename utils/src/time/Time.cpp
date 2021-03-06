// Corresponding Header
#include "utils/time/Time.h"

// C system includes

// C++ system includes

// Third party includes

// Own includes


#include <chrono>

/** @brief used to measure elapsed time since last invoke of this method
* NOTE: .getElapsed() method simply measures time between 2
* points of time.
* */
Time& Time::getElapsed() {
	_elapsedLastCall = _now;
	_now = std::chrono::steady_clock::now();
return *this;
}

int64_t Time::toSeconds() const {
	return std::chrono::duration_cast<std::chrono::seconds>(_now - _elapsedLastCall).count();
}

int64_t Time::toMilliseconds() const{
	return std::chrono::duration_cast<std::chrono::milliseconds>(_now - _elapsedLastCall).count();
}

int64_t Time::toMicroseconds() const{
	return std::chrono::duration_cast<std::chrono::microseconds>(_now - _elapsedLastCall).count();
}

int64_t Time::toNanoseconds() const{
	return std::chrono::duration_cast<std::chrono::nanoseconds>(_now - _elapsedLastCall).count();
}
