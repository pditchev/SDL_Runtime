#ifndef SDL_UTILS_SDLLOADER_H_
#define SDL_UTILS_SDLLOADER_H_

// C system includes

// C++ system includes
#include <cstdint>

// Third party includes

// Own includes

// Forward Declarations

class SDLLoader {
public:
	SDLLoader() = delete;
	virtual ~SDLLoader() = default;

	static int32_t init();

	static void deinit();
};

#endif /* SDL_UTILS_SDLLOADER_H_ */
