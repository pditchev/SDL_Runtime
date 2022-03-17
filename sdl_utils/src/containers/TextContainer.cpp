// Corresponding Header
#include "sdl_utils/containers/TextContainer.h"

// C system includes

// C++ system includes
#include <iostream>
#include <algorithm>


// Third party includes
#include <SDL_ttf.h>

// Own includes
#include "utils/drawing/Color.h"
#include "sdl_utils/Texture.h"

int32_t TextContainer::init(const TextContainerCfg& cfg){
	TTF_Font * currFont = nullptr;
	for(const auto& [key, fontCfg] : cfg.fontConfigs){
		currFont = TTF_OpenFont(fontCfg.location.c_str(), fontCfg.fontSize );
		if(nullptr == currFont){
			std::cerr << "Error! TTF_OpenFont() failed for fontLocation: " << fontCfg.location
					  << ". Reason: " << SDL_GetError() << std::endl;
			return EXIT_FAILURE;
		}

		_fonts[key] = currFont;
	}

	return EXIT_SUCCESS;
}

void TextContainer::deinit(){
	for(const auto& [key, font] : _fonts){
		TTF_CloseFont(font);
	}
}

void TextContainer::createText(const std::string &text, const Color &color, int32_t fontId,
								int32_t &outTextId, int32_t &outTextWidth,
								int32_t &outTextHeight){

	auto it = _fonts.find(fontId);
	if(it == _fonts.end()){
		std::cerr << "Error! fontId: " << fontId
				  << " could not be found. Will not create text: " << text << std::endl;
		return;
	}
	TTF_Font* font = it->second;
	SDL_Texture* textTexture = nullptr;
	if(EXIT_SUCCESS != Texture::createTextureFromText(text, color, font, textTexture, outTextWidth, outTextHeight)){
		std::cerr << "Error, createTextureFromText() failed for text: " << text << std::endl;
		return;
	}

	occupyFreeSlotIndex(outTextId, textTexture);
}

void TextContainer::reloadText(const std::string &text, const Color &color, int32_t fontId,
								int32_t textId, int32_t &outTextWidth,
								int32_t &outTextHeight){

	auto it = _fonts.find(fontId);
	if(it == _fonts.end()){
		std::cerr << "Error! fontId: " << fontId
				  << " could not be found. Will not reload text: " << text << std::endl;
		return;
	}

	freeSlotIndex(textId);

	TTF_Font* font = it->second;
	SDL_Texture* textTexture = nullptr;
	if(EXIT_SUCCESS != Texture::createTextureFromText(text, color, font, textTexture, outTextWidth, outTextHeight)){
		std::cerr << "Error, createTextureFromText() failed for text: " << text << std::endl;
		return;
	}

	_textures[textId] = textTexture;
}

void TextContainer::unloadText(int32_t textId){
	if(0 > textId || textId >= static_cast<int32_t>(_textures.size())){
		std::cerr << "Error! Trying to unload non-existing textId: " << textId << std::endl;
		return;
	}

	freeSlotIndex(textId);
}

SDL_Texture* TextContainer::getTextTexture(int32_t textId) const{
	if(0 > textId || textId >= static_cast<int32_t>(_textures.size())){
		std::cerr << "Error! Trying to get non-existing textId: " << textId << std::endl;
		return nullptr;
	}
	return _textures[textId];
}

void TextContainer::occupyFreeSlotIndex(int32_t& outIdx, SDL_Texture* texture){
	auto it = std::find(_textures.begin(),_textures.end(), nullptr);
	outIdx = static_cast<int32_t>(it - _textures.begin());

	if(it != _textures.end()){
		_textures[outIdx] = texture;
	} else	{
		_textures.push_back(texture);
	}
}

void TextContainer::freeSlotIndex(int32_t index){
	Texture::freeTexture(_textures[index]);
}


