// Corresponding Header
#include "sdl_utils/Renderer.h"

// C system includes

// C++ system includes
#include <iostream>

// Third party includes
#include <SDL_render.h>

// Own includes
#include "sdl_utils/Texture.h"

int32_t Renderer::init(SDL_Window *window){

	constexpr auto unspecifiedDriverId = -1;
	_sdlRenderer = SDL_CreateRenderer(window, unspecifiedDriverId, SDL_RENDERER_ACCELERATED);
	if(_sdlRenderer == nullptr){
		std::cerr << "SDL_CreateRenderer() failed. Reason: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	if(EXIT_SUCCESS != SDL_SetRenderDrawColor(_sdlRenderer, 0,100,100, SDL_ALPHA_OPAQUE)){
		std::cerr << "SDL_SetRenderDrawColor() failed. Reason: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	Texture::setRenderer(_sdlRenderer);

	return EXIT_SUCCESS;
}

void Renderer::deinit(){
	if(_sdlRenderer){
		SDL_DestroyRenderer(_sdlRenderer);
		_sdlRenderer = nullptr;
	}
}

void Renderer::clearScreen(){
	if(EXIT_SUCCESS != SDL_RenderClear(_sdlRenderer)){
		std::cerr << "SDL_RenderClear() failed. Reason: " << SDL_GetError() << std::endl;
	}
}

void Renderer::finishFrame(){
	SDL_RenderPresent(_sdlRenderer);
}

void Renderer::renderTexture(SDL_Texture *texture, const DrawParams& drawParams) const {
	if(WidgetType::IMAGE == drawParams.widgetType){
		drawImage(drawParams, texture);
	} else if(WidgetType::TEXT == drawParams.widgetType){
		drawText(drawParams, texture);
	} else
		std::cerr << "Error, received unsupported WidgetType: " << static_cast<int32_t>(drawParams.widgetType)
				  << " for rsrcId: " << drawParams.rsrcId << std::endl;
}

void Renderer::setWidgetBlendMode(SDL_Texture *texture, BlendMode blendMode){
	  if (EXIT_SUCCESS != Texture::setBlendModeTexture(texture, blendMode)) {
	    std::cerr << "Error in Texture::setBlendModeTexture() failed" << std::endl;
	  }
}

void Renderer::setWidgetOpacity(SDL_Texture *texture, int32_t opacity){
	if(EXIT_SUCCESS != Texture::setAlphaTexture(texture, opacity)){
	    std::cerr << "Error in Texture::setAlphaTexture() failed" << std::endl;
	}
}

void Renderer::drawImage(const DrawParams &drawParams, SDL_Texture *texture) const {
	if(FULL_OPACITY == drawParams.opacity){
		drawTextureInternal(drawParams, texture);
	} else {
		if(EXIT_SUCCESS != Texture::setAlphaTexture(texture, drawParams.opacity)){
			std::cerr << "Texture::setAlphaTexture() failed for file: " << drawParams.rsrcId << std::endl;
		}

		drawTextureInternal(drawParams, texture);

		if(EXIT_SUCCESS != Texture::setAlphaTexture(texture, FULL_OPACITY)){
			std::cerr << "Texture::setAlphaTexture() failed for file: " << drawParams.rsrcId << std::endl;
		}
	}
}

void Renderer::drawText(const DrawParams &drawParams, SDL_Texture *texture) const {
	drawTextureInternal(drawParams, texture);
}

void Renderer::drawTextureInternal(const DrawParams &drawParams, SDL_Texture *texture) const {
	const SDL_Rect destRect = { .x = drawParams.pos._x, .y = drawParams.pos._y,
								.w = drawParams.width, .h = drawParams.height };

	const SDL_Rect* sourceRect = reinterpret_cast<const SDL_Rect*>(&drawParams.frameRect);
	const SDL_Point* center = reinterpret_cast<const SDL_Point*>(&drawParams.rotationCenter);


	const int32_t err = SDL_RenderCopyEx(_sdlRenderer, texture, sourceRect, &destRect,
			drawParams.rotationAngle, center, static_cast<SDL_RendererFlip>(drawParams.flipType));

	if(EXIT_SUCCESS != err){
			std::cerr << "SDL_RenderCopyEx() failed for file: " << drawParams.textId
					  << " Reason: " << SDL_GetError() << std::endl;
		}
}






