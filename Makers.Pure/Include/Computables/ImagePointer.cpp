#include "pch.h"
#include <typeinfo>

#include "ImagePointer.h"

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
	if (array_pool_pointer_ == nullptr) return nullptr;
	return (_image_type*)array_pool_pointer_;
}

//@ set buffer
template<typename _image_type>
void Makers::Computables::ImagePointer<_image_type>::set_buffer(
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
	instance_type_ = eInstanceType::ImagePointer;	// set instance type
	_SetDataType();									// set data type
	array_pool_pointer_ = nullptr;					// init nullptr
}

//@ destructor
template<typename _image_type>
ImagePointer<_image_type>::~ImagePointer()
{
	// not release memory -> memory pool hold it
	array_pool_pointer_ = nullptr;
}

//@ set data type
template<typename _image_type>
void Makers::Computables::ImagePointer<_image_type>::_SetDataType()
{
	if (typeid(unsigned char) == typeid(_image_type))	// check byte
	{
		data_type_ = eDataType::Byte;
		return;
	}
	if (typeid(float) == typeid(_image_type))			// check float
	{
		data_type_ = eDataType::Float;
		return;
	}
	if (typeid(double) == typeid(_image_type))			// check double
	{
		data_type_ = eDataType::Double;
		return;
	}
}

//@ Can attach input to this
template<typename _image_type>
bool Makers::Computables::ImagePointer<_image_type>::CanAttachInto(IComputable * _computable)
{
	// can not connect into
	return false;
}

//@ to string
template<typename _image_type>
std::string ImagePointer<_image_type>::ToString()
{
	return "<class ImagePointer<" + DataType() + ">> " + std::to_string(width_) + ", " + std::to_string(height_);
}
