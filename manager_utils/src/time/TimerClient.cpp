// Corresponding Header
#include "manager_utils/time/TimerClient.h"

// C system includes

// C++ system includes

// Third party includes

// Own includes
#include "manager_utils/managers/TimerMgr.h"

//TimerClient::~TimerClient() = default;
void TimerClient::startTimer(int64_t interval, int32_t timerId, TimerType timerType){
	constexpr auto minTimerInterval = 20;
	if(interval < minTimerInterval){
		std::cerr << "Error! Timer with id: " << timerId << " requested interval: " << interval
				  <<" , which is lower than the minimum one: " << minTimerInterval << std::endl;
		return;
	}

	const TimerData data(interval, interval, this, timerType);
	gTimerMgr->startTimer(timerId, data);
}

void TimerClient::stopTimer(int32_t timerId){
	gTimerMgr->stopTimer(timerId);
}

bool TimerClient::isActiveTimerId(int32_t timerId) const{
	return gTimerMgr->isActiveTimerId(timerId);
}
