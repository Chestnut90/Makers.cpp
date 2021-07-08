#include "pch.h"
#include "ROI.h"

#pragma region getters

//@ get left
long Makers::Computables::ROI::left() const
{
	return left_;
}

//@ get top
long Makers::Computables::ROI::top() const
{
	return top_;
}

//@ get right
long Makers::Computables::ROI::right() const
{
	return right_;
}

//@ get bottom
long Makers::Computables::ROI::bottom() const
{
	return bottom_;
}

#pragma endregion

//@ set roi
void Makers::Computables::ROI::set_roi(
	long _left,
	long _top,
	long _right,
	long _bottom)
{
	left_ = _left;
	top_ = _top;
	right_ = _right;
	bottom_ = _bottom;
}

//@ constructor with 0
Makers::Computables::ROI::ROI()
{
	instance_type_ = eInstanceType::ROI;
	set_roi(0, 0, 0, 0);
}

//@ constructor
Makers::Computables::ROI::ROI(
	long _left, 
	long _top, 
	long _right, 
	long _bottom) :
	ROI()
{
	set_roi(_left, _top, _right, _bottom);
}

//@ destructor
Makers::Computables::ROI::~ROI()
{
}

//@ Can attach input into
bool Makers::Computables::ROI::CanAttachInto(IComputable * _computable)
{
	// only can be attached roi
	return instance_type() == _computable->instance_type();
}

//@ to string
std::string Makers::Computables::ROI::ToString()
{
	return "<class ROI> " +
		std::to_string(left_) + ", " +
		std::to_string(top_) + ", " +
		std::to_string(right_) + ", " +
		std::to_string(bottom_);
}
