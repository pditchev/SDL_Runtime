#ifndef UTILS_THREAD_THREADUTILS_H_
#define UTILS_THREAD_THREADUTILS_H_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers

//Own components headers

//Forward declaration

class Threading {
public:
	Threading() = delete;
	static void sleepFor(int64_t microseconds);
};

#endif /* UTILS_THREAD_THREADUTILS_H_ */
