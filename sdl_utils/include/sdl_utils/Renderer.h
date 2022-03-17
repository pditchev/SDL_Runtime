#ifndef SDL_UTILS_RENDERER_RENDERER_H_
#define SDL_UTILS_RENDERER_RENDERER_H_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers

//Own components headers

//Own includes
#include "utils/drawing/DrawParams.h"

//Forward declaration
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Window;

class Renderer {
public:
	Renderer() = default;

	Renderer(const Renderer& other) = delete;
	Renderer(Renderer&& other) = delete;
	Renderer& operator=(const Renderer& other) = delete;
	Renderer& operator=(Renderer&& other) = delete;

	int32_t init(SDL_Window *window);
	void deinit();
	void clearScreen();
	void finishFrame();
	void renderTexture(SDL_Texture *texture, const DrawParams& drawParams) const;
	void setWidgetBlendMode(SDL_Texture *texture, BlendMode blendMode);
	void setWidgetOpacity(SDL_Texture *texture, int32_t opacity);
private:
	SDL_Renderer* _sdlRenderer = nullptr;

	void drawImage(const DrawParams &drawParams, SDL_Texture *texture) const;
	void drawText(const DrawParams &drawParams, SDL_Texture *texture) const;

	void drawTextureInternal(const DrawParams &drawParams, SDL_Texture *texture) const;
};

#endif /* SDL_UTILS_RENDERER_RENDERER_H_ */
