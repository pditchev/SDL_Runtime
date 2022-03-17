// Corresponding Header
#include "manager_utils/drawing/Widget.h"

// C system includes

// C++ system includes
#include <cstdlib>
#include <iostream>

// Third party includes

// Own includes
#include "manager_utils/managers/DrawMgr.h"


void Widget::draw() const {
	if(_isVisible){
		gDrawMgr->addDrawCmd(_drawParams);
	}
}

void Widget::reset() {
	  _isCreated = false;
	  _isDestroyed = true;
	  _isVisible = true;
	  _isAlphaModulationEnabled = false;

	  _drawParams.reset();
}

//void Widget::setFlipType(WidgetFlip flipType){
//	_drawParams.flipType = flipType;
//}


void Widget::setWidth(int32_t width){
	_drawParams.width = width;
}

void Widget::setHeight(int32_t height){
	_drawParams.height = height;
}

int32_t Widget::getWidth() const {
	return _drawParams.width;
}

int32_t Widget::getHeight() const {
	return _drawParams.height;
}

int32_t Widget::getX() const{
	return _drawParams.pos._x;
}

int32_t Widget::getY() const {
	return _drawParams.pos._y;
}

void Widget::setPosition(const Point& pos) {
	_drawParams.pos = pos;
}

void Widget::setPosition(int32_t x, int32_t y) {
	_drawParams.pos._x = x;
	_drawParams.pos._y = y;
}

void Widget::setOpacity(int32_t opacity) {
	if(!_isAlphaModulationEnabled){
		std::cerr << "alpha modulation was not enabled for rsrcId: "
				  << _drawParams.rsrcId << " . Will not change opacity!!"<< std::endl;
		return;
	}
	_drawParams.opacity = opacity;
	gDrawMgr->setWidgetOpacity(_drawParams, opacity);
}

Point Widget::getPosition() const {
	return _drawParams.pos;
}

int32_t Widget::getOpacity() const {
	return _drawParams.opacity;
}

void Widget::setRotation(double angle){
	_drawParams.rotationAngle = angle;
}

double Widget::getRotation() const{
	return _drawParams.rotationAngle;
}

void Widget::rotateRight(double delta){
	_drawParams.rotationAngle += delta;
	while(_drawParams.rotationAngle > FULL_ROTATION){
		_drawParams.rotationAngle -= FULL_ROTATION;
	}
}

void Widget::rotateLeft(double delta){
	_drawParams.rotationAngle -= delta;
	while(_drawParams.rotationAngle < 0){
		_drawParams.rotationAngle += FULL_ROTATION;
	}
}

void Widget::setRotationCenter(const Point& rotCenter){
	_drawParams.rotationCenter = rotCenter;
}


void Widget::activateAlphaModulation() {
	if(_isAlphaModulationEnabled){
		std::cerr << "alpha modulation was already enabled for rsrcId: " << _drawParams.rsrcId << std::endl;
		return;
	}
	_isAlphaModulationEnabled = true;
	gDrawMgr->setWidgetBlendMode(_drawParams, BlendMode::BLEND);
}

void Widget::deactivateAlphaModulation() {
	if(!_isAlphaModulationEnabled){
		std::cerr << "alpha modulation was not enabled for rsrcId: " << _drawParams.rsrcId << std::endl;
		return;
	}
	_isAlphaModulationEnabled = false;
	gDrawMgr->setWidgetBlendMode(_drawParams, BlendMode::NONE);
}

void Widget::show() {
	_isVisible = true;
}

void Widget::hide() {
	_isVisible = false;
}

void Widget::changeVisibility(){
	_isVisible = !_isVisible;
}


void Widget::moveRight(int32_t delta) {
	_drawParams.pos._x += delta;
}

void Widget::moveLeft(int32_t delta) {
	_drawParams.pos._x -= delta;
}

void Widget::moveUp(int32_t delta) {
	_drawParams.pos._y -= delta;
}

void Widget::moveDown(int32_t delta) {
	_drawParams.pos._y += delta;
}

bool Widget::containsPoint(const Point& pos) const {
	const Rectangle bound(_drawParams.pos._x, _drawParams.pos._y,
						  _drawParams.width, _drawParams.height);
	return bound.isPointInside(pos);
}

bool Widget::isVisible() const {
	return _isVisible;
}

bool Widget::isCreated() const {
	return _isCreated;
}





