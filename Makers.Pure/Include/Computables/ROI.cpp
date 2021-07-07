#include "pch.h"
#include "ROI.h"

unsigned int Makers::Computables::ROI::left() const
{
	return ((unsigned int*)data_)[0];
}

unsigned int Makers::Computables::ROI::top() const
{
	return ((unsigned int*)data_)[1];
}

unsigned int Makers::Computables::ROI::right() const
{
	return ((unsigned int*)data_)[2];
}

unsigned int Makers::Computables::ROI::bottom() const
{
	return ((unsigned int*)data_)[3];
}

void Makers::Computables::ROI::set_left(unsigned int _left)
{
	((unsigned int*)data_)[0] = _left;
}

void Makers::Computables::ROI::set_top(unsigned int _top)
{
	((unsigned int*)data_)[1] = _top;
}

void Makers::Computables::ROI::set_right(unsigned int _right)
{
	((unsigned int*)data_)[2] = _right;
}

void Makers::Computables::ROI::set_bottom(unsigned int _bottom)
{
	((unsigned int*)data_)[3] = _bottom;
}

void Makers::Computables::ROI::set_roi(
	unsigned int _left,
	unsigned int _top,
	unsigned int _right,
	unsigned int _bottom)
{
	if (data_ == nullptr)
	{
		data_ = (void*)new unsigned int[4];
	}
	auto roi = (unsigned int*)data_;
	roi[0] = _left;
	roi[1] = _top;
	roi[2] = _right;
	roi[3] = _bottom;
}

Makers::Computables::ROI::ROI(
	unsigned int _left, 
	unsigned int _top, 
	unsigned int _right, 
	unsigned int _bottom)
{
	set_roi(_left, _top, _right, _bottom);
}

Makers::Computables::ROI::~ROI()
{
}

bool Makers::Computables::ROI::CanAttachable(IComputable * _computable)
{
	return false;
}

std::string Makers::Computables::ROI::ToString()
{
	auto roi = (unsigned int*)data_;
	return "ROI";
}
