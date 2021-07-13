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
	long left,
	long top,
	long right,
	long bottom)
{
	left_ = left;
	top_ = top;
	right_ = right;
	bottom_ = bottom;
}

//@ constructor with 0
Makers::Computables::ROI::ROI() :
	IComputable()
{
	instance_type_ = eInstanceType::ROI;
	set_roi(0, 0, 0, 0);
}

//@ constructor
Makers::Computables::ROI::ROI(
	long left, 
	long top, 
	long right, 
	long bottom) :
	ROI()
{
	set_roi(left, top, right, bottom);
}

//@ destructor
Makers::Computables::ROI::~ROI()
{
}

//@ Can attach input into
bool Makers::Computables::ROI::CanAttachInto(IComputable * computable)
{
	// only can be attached roi
	return instance_type() == computable->instance_type();
}

//@ to string
std::string Makers::Computables::ROI::ToString()
{
	return "<class ROI> (" +
		std::to_string(left_) + ", " +
		std::to_string(top_) + ", " +
		std::to_string(right_) + ", " +
		std::to_string(bottom_) + ")";
}
