#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_TIMERMGR_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_TIMERMGR_H_
//C system headers

//C++ system headers
#include <map>
#include <set>
#include <iostream>

//Other libraries headers

//Own components headers
#include "manager_utils/managers/MgrBase.h"
#include "manager_utils/time/TimerData.h"
#include "utils/time/Time.h"


//Forward declaration

class TimerMgr: public MgrBase {
public:
	int32_t init();
	void deinit() final;
	void process() final;
	void startTimer(int32_t timerId, const TimerData& data);
	void stopTimer(int32_t timerId);
//	void detachTimerClient(int32_t timerId);
	bool isActiveTimerId(int32_t timerId) const;
	void onInitEnd();
	size_t getActiveTimersCount() const;
private:
	void removeTimersInternal();
	void onTimerTimeout(int32_t timerId, TimerData& timer);

	Time _elapsedTime;
	std::map<int32_t, TimerData> _timerMap;
	std::set<int32_t> _removeTimerSet;
};

extern TimerMgr* gTimerMgr;

#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_TIMERMGR_H_ */
