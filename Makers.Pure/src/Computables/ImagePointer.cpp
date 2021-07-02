#include "pch.h"
#include <type_traits>
#include <iostream>
#include <typeinfo>

#include "../../Include/Computables/ImagePointer.h"

using namespace Makers::Computables;
#pragma region getters and setters

//@ width
template<typename _image_type>
long Makers::Computables::ImagePointer<_image_type>::width() const
{
	return width_;
}

//@ height
template<typename _image_type>
long Makers::Computables::ImagePointer<_image_type>::height() const
{
	return height_;
}

//@ image
template<typename _image_type>
_image_type * ImagePointer<_image_type>::image() const
{
	return (_image_type*)array_pool_pointer_;
}

template<typename _image_type>
void Makers::Computables::ImagePointer<_image_type>::set_point(
	void * _buffer, unsigned long _width, unsigned long _height)
{
	width_ = _width;
	height_ = _height;
	array_pool_pointer_ = _buffer;
}

#pragma endregion

//@ constructor
template<typename _image_type>
ImagePointer<_image_type>::ImagePointer() :
	IComputable()
{

}

//@ destructor
template<typename _image_type>
ImagePointer<_image_type>::~ImagePointer()
{
}

//@ TODO : 
template<typename _image_type>
std::string ImagePointer<_image_type>::ToString()
{
	return /*std::to_string(this) + " " +*/ std::to_string(width_) + " " + std::to_string(height_);
}
