// Corresponding Header
#include "manager_utils/drawing/Text.h"

// C system includes

// C++ system includes

// Third party includes

// Own includes
#include "manager_utils/managers/RsrcMgr.h"


Text::~Text(){
	if(_isCreated && !_isDestroyed){
		destroy();
	}
}

void Text::create(const char *text, int32_t fontId,	const Color& color, const Point &pos){
	if(_isCreated){
		std::cerr << "Error! Text with fontId: " << fontId
				  << " was already created. Will not create it twice!!!" << std::endl;
		return;
	}

	gRsrcMgr->createText(text, color , fontId, _drawParams.rsrcId, _drawParams.width, _drawParams.height);
	_drawParams.frameRect._x = 0;
	_drawParams.frameRect._y = 0;
	_drawParams.frameRect._w = _drawParams.width;
	_drawParams.frameRect._h = _drawParams.height;

	_drawParams.pos = pos;
	_drawParams.widgetType = WidgetType::TEXT;

	_textContent = text;
	_color = color;
	_fontId = fontId;

	_isCreated = true;
	_isDestroyed = false;

}

void Text::destroy(){
	if(!_isCreated){
		std::cerr << "Error! Image was already destroyed!!!" << std::endl;
		return;
	}
	_isCreated = false;
	_isDestroyed = true;

	if(gRsrcMgr){
		gRsrcMgr->unloadText(_drawParams.textId);
	}

	Widget::reset();
}

void Text::setText(const std::string& text){
	if(text == _textContent){
		return;
	}
	_textContent = text;
	gRsrcMgr->createText(_textContent, _color , _fontId, _drawParams.rsrcId, _drawParams.width, _drawParams.height);

	_drawParams.frameRect._w = _drawParams.width;
	_drawParams.frameRect._h = _drawParams.height;
}

void Text::setColor(const Color& color){
	if(color == _color){
		return;
	}

	_color = color;
	gRsrcMgr->createText(_textContent, _color , _fontId, _drawParams.rsrcId, _drawParams.width, _drawParams.height);

}

std::string Text::getTextContent() const{
	return _textContent;
}
