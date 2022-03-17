#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_TIME_TIMERCLIENT_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_TIME_TIMERCLIENT_H_
//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers

//Own components headers
#include "manager_utils/time/TimerData.h"

//Forward declaration

class TimerClient{
public:
	virtual ~TimerClient() = default;
	virtual void onTimeout(int32_t timerId) = 0;
	void startTimer(int64_t interval, int32_t timerId, TimerType timerType);
	void stopTimer(int32_t timerId);
	bool isActiveTimerId(int32_t timerId) const;
};

#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_TIME_TIMERCLIENT_H_ */
