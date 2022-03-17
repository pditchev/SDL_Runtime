#ifndef SDL_UTILS_INPUTEVENT_H_
#define SDL_UTILS_INPUTEVENT_H_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers

//Own components headers
#include "utils/input/EventDefines.h"
#include "utils/drawing/Point.h"

//Forward declaration


union SDL_Event;

class InputEvent {
public:
	int32_t init();
	void deinit();
	bool pollEvent();
	bool checkForExitRequest() const;

	Point pos = Point::UNDEFINED;

	int32_t key = Keyboard::KEY_UNKNOWN;
	uint8_t mouseButton = Mouse::UNKNOWN;
	TouchEvent type = TouchEvent::UNKNOWN;

private:
	void setEventTypeInternal();

	SDL_Event *_sdlEvent = nullptr;

};

#endif /* SDL_UTILS_INPUTEVENT_H_ */
