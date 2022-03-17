#ifndef UTILS_DRAWING_CONFIG_MONITORWINDOWCFG_H_
#define UTILS_DRAWING_CONFIG_MONITORWINDOWCFG_H_

// C system includes

// C++ system includes
#include <cstdint>
#include <string>

// Third party includes

// Own includes
#include "utils/drawing/Point.h"

// Forward Declarations

enum WindowFlags{
	WINDOW_SHOWN = 4,  //SDL_WINDOW_SHOWN
	WINDOW_FULLSCREEN_DESKTOP = 4097, // SDL_WINDOW_FULLSCREEN_DESKTOP
	WINDOW_BORDERLESS = 16 // SDL_WINDOW_BORDERLESS
};

struct MonitorWindowCfg{
	std::string windowName;
	Point windowPos = Point::UNDEFINED;
	int32_t windowHeight = 640;
	int32_t windowWidth = 480;
	WindowFlags windowFlags = WINDOW_SHOWN;
};



#endif /* UTILS_DRAWING_CONFIG_MONITORWINDOWCFG_H_ */
