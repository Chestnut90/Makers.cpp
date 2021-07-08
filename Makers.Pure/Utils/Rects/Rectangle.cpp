#include "pch.h"
#include "Rectangle.h"

long Utils::Rects::Rectangle::left() const
{
	return left_;
}

long Utils::Rects::Rectangle::top() const
{
	return top_;
}

long Utils::Rects::Rectangle::right() const
{
	return right_;
}

long Utils::Rects::Rectangle::bottom() const
{
	return bottom_;
}

void Utils::Rects::Rectangle::set_left(long _left)
{
	left_ = _left;
}

void Utils::Rects::Rectangle::set_top(long _top)
{
	top_ = _top;
}

void Utils::Rects::Rectangle::set_right(long _right)
{
	right_ = _right;
}

void Utils::Rects::Rectangle::set_bottom(long _bottom)
{
	bottom_ = _bottom;
}

Utils::Rects::Rectangle::Rectangle()
{
	left_ = top_ = right_ = bottom_ = 0;
}

Utils::Rects::Rectangle::Rectangle(long _left, long _top, long _right, long _bottom)
{
	left_ = _left;
	top_ = _top;
	right_ = _right;
	bottom_ = _bottom;
}

Utils::Rects::Rectangle::~Rectangle()
{
}

long Utils::Rects::Rectangle::Width()
{
	return right_ - left_;
}

long Utils::Rects::Rectangle::Height()
{
	return top_ - bottom_;
}
