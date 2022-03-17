#include "sdl_utils/Texture.h"

// C system includes

// C++ system includes
#include <iostream>

// Third party includes
#include "SDL_surface.h"
#include "SDL_image.h"
#include "SDL_render.h"
#include "SDL_ttf.h"

// Own includes
#include "utils/drawing/DrawParams.h"
#include "utils/drawing/Color.h"

static SDL_Renderer* gRenderer = nullptr;

int32_t Texture::createSurfaceFromFile(const std::string& filePath, SDL_Surface*& outSurface){
	outSurface = IMG_Load(filePath.c_str());
	if(nullptr == outSurface){
		std::cerr << "IMG_Load() failed. Reason: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void Texture::freeSurface(SDL_Surface*& outSurface){
	if(outSurface){
		SDL_FreeSurface(outSurface);
		outSurface = nullptr;
	}
}

int32_t Texture::createTextureFromFile(const std::string& filePath, SDL_Texture*& outTexture){
	SDL_Surface* surface = nullptr;
	if(EXIT_SUCCESS != createSurfaceFromFile(filePath, surface)){
		std::cerr << "createSurfaceFromFile() failed for file: " << filePath
				  << " Reason: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	if(EXIT_SUCCESS != createTextureFromSurface(surface, outTexture)){
		std::cerr << "createTextureFromSurface() failed for file: " << filePath
				  << " Reason: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int32_t Texture::createTextureFromSurface(SDL_Surface*& inOutSurface, SDL_Texture*& outTexture){

	outTexture = SDL_CreateTextureFromSurface(gRenderer, inOutSurface);
	if(nullptr == outTexture){
		std::cerr << "SDL_CreateTextureFromSurface() failed. Reason: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	freeSurface(inOutSurface);

	return EXIT_SUCCESS;
}

int32_t Texture::createTextureFromText(const std::string &text, const Color &color, TTF_Font *font,
										SDL_Texture*& outTexture,
										int32_t &outTextWidth,
										int32_t &outTextHeight){
	const SDL_Color* sdlColor = reinterpret_cast<const SDL_Color*>(&color.rgba);

	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), *sdlColor);
	if(nullptr == textSurface){
		std::cerr << "TTF_RenderText_Blended() failed for text: " << text
				  << ". Reason: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	outTextWidth = textSurface->w;
	outTextHeight = textSurface->h;

	if(EXIT_SUCCESS != createTextureFromSurface(textSurface, outTexture)){
		std::cerr << "createTextureFromSurface() failed for text: " << text
				  << ". Reason: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void Texture::freeTexture(SDL_Texture*& outTexture){
	if(outTexture){
		SDL_DestroyTexture(outTexture);
		outTexture = nullptr;
	}
}

void Texture::setRenderer(SDL_Renderer* r){
	gRenderer = r;
}

int32_t Texture::setBlendModeTexture(SDL_Texture *texture, BlendMode blendMode){
	if(EXIT_SUCCESS != SDL_SetTextureBlendMode(texture, static_cast<SDL_BlendMode>(blendMode))){
		std::cerr << "SDL_SetTextureBlendMode() failed. Reason: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int32_t Texture::setAlphaTexture(SDL_Texture *texture, int32_t alpha){
	if(ZERO_OPACITY > alpha || FULL_OPACITY < alpha){
		std::cerr << "Error! Invalid alpha value: " << alpha << " provided." << std::endl;
		return EXIT_FAILURE;
	}

	if(EXIT_SUCCESS != SDL_SetTextureAlphaMod(texture, static_cast<uint8_t>(alpha))){
		std::cerr << "SDL_SetTextureAlphaMod() failed. Reason: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}



