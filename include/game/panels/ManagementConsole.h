#ifndef INCLUDE_GAME_PANELS_MANAGEMENTCONSOLE_H_
#define INCLUDE_GAME_PANELS_MANAGEMENTCONSOLE_H_
//C system headers

//C++ system headers
#include <functional>

//Other libraries headers

//Own components headers
#include "manager_utils/drawing/Text.h"
#include "manager_utils/time/TimerClient.h"
#include "game/defines/ChessDefines.h"

//Forward declaration
struct InputEvent;

class ManagementConsole : public TimerClient {
public:
	int32_t init(int32_t fontId, int32_t timerCapTimerId);
	void draw() const;
	void onTimeout(int32_t timerId) final;
	void startTimerCap();
	void onCheck(const Defines::PlayerId &player);
	void onCheckMate(const Defines::PlayerId &winner);
	void onRemoveCheck();

	std::function<void()> finish;
	std::function<void()> clearMoveTiles;

private:
	enum ManagementConsoleInternal{
		gameTime = 60
	};
	Text remainingTime;

	Text announcement1;
	Text announcement2;


	bool _isActive = true;

	int32_t _timerCapTimerId;
	int32_t _fontId;
};

#endif /* INCLUDE_GAME_PANELS_MANAGEMENTCONSOLE_H_ */
