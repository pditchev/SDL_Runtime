#ifndef SDL_UTILS_MONITORWINDOW_H_
#define SDL_UTILS_MONITORWINDOW_H_
// C system includes

// C++ system includes
#include <cstdint>
#include <string>

// Third party includes

// Own includes
#include "utils/drawing/Rectangle.h"
#include "sdl_utils/config/MonitorWindowCfg.h"

// Forward Declarations
struct SDL_Window;
struct SDL_Surface;

class MonitorWindow {
public:
	MonitorWindow();
	~MonitorWindow();

	MonitorWindow(const MonitorWindow& other) = delete;
	MonitorWindow(MonitorWindow&& other) = delete;

	MonitorWindow& operator=(const MonitorWindow& other) = delete;
	MonitorWindow& operator=(MonitorWindow&& other) = delete;

	int32_t init(const MonitorWindowCfg& cfg);

	void deinit();

//	SDL_Surface* getWindowSurface();

	SDL_Window* getWindow();

	void updateWindowSurface();

private:
	SDL_Window* _window = nullptr;
	Rectangle _rectangle = Rectangle::UNDEFINED;
};

#endif /* SDL_UTILS_MONITORWINDOW_H_ */
