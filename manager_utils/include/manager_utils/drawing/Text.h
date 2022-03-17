#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_DRAWING_TEXT_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_DRAWING_TEXT_H_
//C system headers

//C++ system headers
#include <string>

//Other libraries headers

//Own components headers
#include "manager_utils/drawing/Widget.h"
#include "utils/drawing/Color.h"

//Forward declaration

class Text : public Widget {
public:
	~Text();

	void create(const char *text, int32_t fontId,
				const Color& color, const Point &pos = Point::ZERO);

	void destroy();

	void setText(const std::string& text);

	void setColor(const Color& color);

	std::string getTextContent() const;

private:
	std::string _textContent;
	Color _color = Colors::BLACK;
	int32_t _fontId = INVALID_RSRC_ID;
};

#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_DRAWING_TEXT_H_ */
